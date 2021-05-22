<?php

/**
 * @file
 * Declares a Views plugin.
 */

/**
 * Implements hook_views_plugins().
 */
function views_summarize_views_plugins() {
  return array(
    'style' => array(
      'tablesummarized' => array(
        'title' => t('Summarized table'),
        'help' => t('Displays rows in a table with a summary row for any column.'),
        'handler' => 'views_summarize_plugin_style_tablesummarized',
        'parent' => 'table',
        'theme' => 'views_summarize_views_tablesummarized',
        'theme file' => 'views_summarize.theme.inc',
        'uses row plugin' => FALSE,
        'uses row class' => TRUE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-table',
      ),
    ),
  );
}
