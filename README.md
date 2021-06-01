Path Redirect Import
=====================

Bulk import redirects (for Redirect module) from a CSV file.

CSV structure:
```
'old url', 'new_url', 'redirect_code' = 301, 'language' = ''
```
Required fields are the `Old URL` and the `New URL`. The `Redirect code` and
`Language` fields are optional.

The drush command `path-redirect-import` is also provided.


Requirements
------------

This module requires that the following modules are also enabled:

 * Redirect (in Backdrop core)


Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- Visit the import page under Administration > Configuration > URL Handling >
  URL Redirects > Import (admin/config/urls/redirect/import).

- Visit the export page under Administration > Configuration > URL Handling >
  URL Redirects > Export (admin/config/urls/redirect/export).


Documentation
-------------

Additional documentation is located in the Wiki:
https://github.com/backdrop-contrib/path_redirect_import/wiki/Documentation.

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/path_redirect_import/issues.

Current Maintainers
-------------------

- [Jen Lampton](https://github.com/jenlampton).
- Seeking additional maintainers.

Credits
-------

- Ported to Backdrop CMS by [Jen Lampton](https://github.com/jenlampton).
- Drupal 7 module is maintained and supported by [plopesc](http://drupal.org/user/282415).
- Drupal 6 original module was maintained and supported by [AG Prime](http://www.ag-prime.com).

License
-------

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.

