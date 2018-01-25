<?php

use Drupal\Core\Database\Database;
use Drupal\field\Entity\FieldConfig;

/**
 * Implements hook_drush_command().
 */
function m2cm_drush_command() {
  return [
    'm2cm-migrate' => [
      'description' => 'Migration and update fixes.',
    ],
  ];
}

/**
 * Prepare site for migration to Content Moderation.
 */
function drush_m2cm_migrate() {

  // Purge all cache objects.
  $bins = [

    'bootstrap',
    'container',
    'data',
    'default',
    'discovery',
    'discovery_migration',
    'dynamic_page_cache',
    'entity',
    'menu',
    'migrate',
    'rest',
    'toolbar',
  ];

  foreach ($bins as $bin) {
    if (\Drupal::hasService("cache.$bin")) {
      \Drupal::cache($bin)->deleteAll();
    }
  }

  drush_print('Flush static caches before making config changes.');

  drupal_flush_all_caches();

  drush_print('Delete scheduled update fields...');

  $fields = [
    'field.field.scheduled_update.multiple_node_embargo.field_moderation_state_1',
    'field.storage.scheduled_update.field_moderation_state',
    'field.field.scheduled_update.node_embargo.field_moderation_state',

  ];

  foreach ($fields as $field) {
    if ($config = FieldConfig::load($field)) {
      $config->delete();
    }
  }

  drush_print('Delete scheduled update config.');

  $types = [
    'scheduled_updates.scheduled_update_type.node_embargo',
    'scheduled_updates.scheduled_update_type.multiple_node_embargo',
  ];

  // Delete each config using configFactory.
  foreach ($types as $config) {
    \Drupal::configFactory()->getEditable($config)->delete();
  }

  drupal_flush_all_caches();

  drush_print('Deleting stale translation queue items.');

  $queue = "content_translation_workflow";

  $con = Database::getConnection();
  $query = $con->select('queue', 't')
    ->fields('t', ['name']);
  $query->condition('name', "%" . $query->escapeLike($queue) . "%", 'LIKE');
  $query->execute()->fetchAll();

  drush_print('Uninstall scheduled updates...');

  // Avoid migration errors due to references to stale
  // service container during scheduled update uninstall.
  $module_installer = \Drupal::service('module_installer');
  $module_installer->uninstall(['scheduled_updates']);

  if (\Drupal::hasContainer()) {
    $module_installer = reload_services($module_installer);
  }

  drush_print('Migration and CM update fixes complete.');

}

/**
 * Utility function for updating service container.
 */
function reload_services($service) {
  return \Drupal::service($service->_serviceId);
}
