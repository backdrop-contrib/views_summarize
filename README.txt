CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Extending
 * Maintainers


INTRODUCTION
------------

The Views Summarize module Enables an extra display style which displays
summaries of a column on the last row.

 * To submit bug reports and feature suggestions, or track changes:
   https://www.drupal.org/project/issues/views_summarize


REQUIREMENTS
------------

This module requires the following modules:

 * Views (https://www.drupal.org/project/views)


INSTALLATION
------------

 * Install as you would normally install a contributed Drupal module. Visit
   https://www.drupal.org/node/895232/ for further information.


CONFIGURATION
-------------

This module does not itself have configuration, but each Views display you
create that uses the  Summarized table display style does. Add and configure the
fields you want to display, then click the "settings" link for the Summarized
table format.

On the popup form will be six columns that relate to this module:
 * Summarize prefix: One or more characters to display before the summary, like
   a currency symbol
 * Summarize:
 * Summarize suffix: One or more characters to display after the summary, like a
   currency abbreviation
 * Summarize thousand: The character to use as a thousand separator
 * Summarize decimal: The character to use as a thousand separator
 * Summarize precision: The number of characters to place after the decimal
   separator

Also on that form, toward the bottom of the form, is the "Display the summary
row only" setting. Checking that box means that the data that is being
summarized will not be displayed.


EXTENDING
---------

It is possible to extend this module by specifying your own summaries.

1. Implement hook_views_summarize_handlers() to add your summary to the list of
   possible handlers.
2. Implement hook_theme() to specify the function to use to theme the summary.
3. Create your theme function to create the output.

Here is example code that could be placed in a .module file to add a summary
that totals the records and displays the total as hours and minutes:

<?php

/**
 * @file
 * Demonstrates adding a summery for Views Summarize to use.
 */

/**
 * Implements hook_views_summarize_handlers().
 */
function my_module_views_summarize_handlers() {
  return array(
    'my_module_views_summarize_hours_min' => t('Hours and Minutes'),
  );
}

/*
 * Implements hook_theme().
 */
function my_module_theme() {
  return array(
    'my_module_views_summarize_hours_min' => array(
      'variables' => array('data' => array()),
    ),
  );
}

/**
 * Themes data as hours and minutes.
 */
function theme_my_module_views_summarize_hours_min($variables) {
  $data = $variables['data'];
  return '<div class="label">' . format_interval(array_sum($data),2) . '</div>';
}


MAINTAINERS
-----------

Current maintainers:
 * Aidan Lister (aidanlis) - https://www.drupal.org/u/aidanlis
 * Jason Flatt (oadaeh) - https://www.drupal.org/u/oadaeh
