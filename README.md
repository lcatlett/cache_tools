# Cache Tools
A Drupal Drush utility tool to manage persistent storage of cache ojects due to the core default for bins being CACHE_PERMANENT. This allows for easily truncating these objects since they are set to never expire.

## Summary  

If you're using a database based cache backend and seeing tables like `cache_render` and `cache_config` grow exponentially, or discovery and data cache tables are causing issues with WSOD, deploying config updates, changes to views, updating plugins, or applying entity updates, this utility can be used to remove stale data and discovery objects.  

Note that 'purging' in this case doesn't mean deleting configuration values but rather scrubbing a datebase for deploying new code. 

It is recommended to use this utility alongside modules such as Slushi Cache which allow for customizing the cache lifetime of core persistent cache bins. This is particularly useful for managing large render cache tables once objects are expired. Since objects not yet expired will persist unless truncated, this Cache Tools utility can be used for either on-demand purging of persistent cached data not yet expired, or integrated into the deployment process to ensure stale cache objects are automatically removed when code and configuration updates are deployed. 

## Installation
Once added to your project codebase. Run `drush cc drush` to ensure the provided drush commands are available. Modifications to drushrc.php may be needed to discover the new commands.

## Usage

Run `drush cache-tools-purge` or `drush cache-nuke` to truncate cache object data not cleared by `drush cr`.  



