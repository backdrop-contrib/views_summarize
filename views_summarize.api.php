<?php

/**
 * @file
 * Hooks provided by the Views summarize module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Declares a summary for use by the Views summarize module.
 *
 * In addition to implementing this hook, a module needs to implement
 * hook_theme() and create the theme function. See the README.txt file for an
 * example.
 *
 * @return array
 *   An associative array, with the key being the machine name of the summary
 *   (which is usually also used as the machine name of the theme to call to get
 *   the summary), and the value being the title of the summary.
 */
function hook_views_summarize_handlers() {
  return array(
    'my_module_views_summarize_hours_min' => t('Hours and Minutes'),
  );
}

/**
 * @} End of "addtogroup hooks".
 */
