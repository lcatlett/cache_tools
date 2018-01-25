# Cache Tools
Various Drupal 8 Drush utilities for low level cache management to resolve common challenges in deploying, updating, and installing Drupal applications. 



## Installation
Once added to your project codebase, run `drush cc drush` to ensure the provided drush commands are available. Modifications to drushrc.php may be needed to discover the new commands. These can also be added to any /drush directory discoverable by $PATH. 


## cache_tools.drush.inc  

persistent storage of cache ojects due to the core default for bins being CACHE_PERMANENT. This allows for easily truncating these objects since they are set to never expire.

persistent storage of cache ojects due to the core default for bins being CACHE_PERMANENT. This allows for easily truncating these objects since they are set to never expire.. If you're using a database based cache backend and seeing issues like WSOD after a code iupdate, missing configuration, changes to views, updating plugins, or applying entity updates, this utility can be used to remove stale data and discovery objects.  

Note that 'purging' in this case doesn't mean deleting configuration values but rather scrubbing a datebase for deploying new code. 

It is recommended to use this utility alongside modules such as Slushi Cache which allow for customizing the cache lifetime of core persistent cache bins. These are particularly useful for managing large render cache tables once objects are expired. Since objects not yet expired will persist unless truncated, this Cache Tools utility can be used for either on-demand purging of persistent cached data not yet expired, or integrated into the deployment process to ensure stale cache objects are automatically removed when code and configuration updates are deployed. 


### Usage

Run `drush cache-tools-purge` or `drush cache-nuke` to truncate cache object data not cleared by `drush cr`.  


## m2cm.drush.inc

Prepare sites using translation revisioning in content editing and migration for migrating to core Content Moderation. May also fix issues with unpublished translated content, missing views arguments causing WSOD, and errors due to caluculating translated entity references.  


### Usage

Run `drush m2cm-migrate` or `drush cache-nuke` to truncate cache object data not cleared by `drush cr`.    






