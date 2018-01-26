<?php
namespace Drupal\cache_tools\Commands;

use Drush\Commands\DrushCommands;

/**
 * Provides commands to purge persistent cache objects.
 */
class CacheToolsCommands extends DrushCommands {

  /**
   * Purges data from persistent cache tables.
   *
   * @command cache:purge
   * @aliases cache-nuke,cache-tools-purge
   */
  public function toolsPurge() {
    $this->output()->writeln(dt('Preparing to truncate persistent cache tables... '));

    // Clear all caches to purge expired objects first.
    drupal_flush_all_caches();
    $this->logger()->info(dt('Cleared caches.'));

    // Trigger a rebuild of router paths to discover changes.
    \Drupal::service("router.builder")->rebuild();

    // Persistent cache bin stores to truncate.
    $bins = [
      'bootstrap',
      'config',
      'data',
      'default',
      'discovery',
      'dynamic_page_cache',
      'entity',
      'menu',
      'migrate',
      'render',
      'rest',
      'toolbar',
    ];
    foreach ($bins as $bin) {
      if (\Drupal::hasService("cache.$bin")) {
        \Drupal::cache($bin)->deleteAll();
      }
    }
  }

}
