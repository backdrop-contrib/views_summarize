<?php

/**
 * @file
 * Provides a views display that outputs summaries of the values in a table.
 */

/**
 * Displays a view as a table summary.
 */
function template_preprocess_views_summarize_views_tablesummarized(&$vars) {
  template_preprocess_views_view_table($vars);

  if (!count($vars['rows'])) {
    return;
  }

  $opts = &$vars['view']->style_plugin->options['info'];

  if (isset($vars['view']->style_plugin->options['summary_only'])) {
    $vars['summary_only'] = $vars['view']->style_plugin->options['summary_only'];
  }
  if (isset($vars['view']->style_plugin->options['summary_above'])) {
    $vars['summary_above'] = $vars['view']->style_plugin->options['summary_above'];
  }
  if (isset($vars['view']->style_plugin->options['summary_below'])) {
    $vars['summary_below'] = $vars['view']->style_plugin->options['summary_below'];
  }

  $data = array();
  foreach ($vars['rows'] as $row) {
    foreach ($row as $field => $value) {
      $data[$field]['values'][] = $value;
    }
  }

  $vars['summarized'] = array();
  foreach ($opts as $field => $settings) {
    if (isset($data[$field])) {
      // Get the display's field settings.
      $field_settings = array();
      if (!empty($vars['view']->field[$field]->options['settings'])) {
        $field_settings = $vars['view']->field[$field]->options['settings'];
      }

      // Get the field instance settings.
      $views_style_options = array();
      if (!empty($vars['view']->style_options['info'][$field])) {
        $views_style_options = $vars['view']->style_options['info'][$field];
      }

      $data[$field]['options'] = array(
        'field' => $field,
        'field_settings' => $field_settings,
        'views_style_options' => $views_style_options,
      );
      $vars['summarized'][$field] = theme($settings['summarize'], $data[$field]);
    }
  }
}

/**
 * Themes the form for the display style plugin.
 *
 * This is almost the same as theme_views_ui_style_plugin_table().
 */
function theme_views_summarize_plugin_style_tablesummarized($variables) {
  $form = $variables['form'];

  $output = backdrop_render($form['description_markup']);

  $header = array(
    t('Field'),
    t('Column'),
    t('Align'),
    t('Separator'),
    t('Summary prefix'),
    t('Summary'),
    t('Include empty values'),
    t('Summary suffix'),
    t('Summary thousands separator'),
    t('Summary decimal separator'),
    t('Summary precision'),
    array(
      'data' => t('Sortable'),
      'align' => 'center',
    ),
    array(
      'data' => t('Default order'),
      'align' => 'center',
    ),
    array(
      'data' => t('Default sort'),
      'align' => 'center',
    ),
    array(
      'data' => t('Hide empty column'),
      'align' => 'center',
    ),
  );
  $rows = array();
  foreach (element_children($form['columns']) as $id) {
    $row = array();
    $row[] = backdrop_render($form['info'][$id]['name']);
    $row[] = backdrop_render($form['columns'][$id]);
    $row[] = backdrop_render($form['info'][$id]['align']);
    $row[] = backdrop_render($form['info'][$id]['separator']);
    $row[] = backdrop_render($form['info'][$id]['prefix']);
    $row[] = backdrop_render($form['info'][$id]['summarize']);
    $row[] = backdrop_render($form['info'][$id]['include_empties']);
    $row[] = backdrop_render($form['info'][$id]['suffix']);
    $row[] = backdrop_render($form['info'][$id]['thousand']);
    $row[] = backdrop_render($form['info'][$id]['decimal']);
    $row[] = backdrop_render($form['info'][$id]['precision']);
    if (!empty($form['info'][$id]['sortable'])) {
      $row[] = array(
        'data' => backdrop_render($form['info'][$id]['sortable']),
        'align' => 'center',
      );
      $row[] = array(
        'data' => backdrop_render($form['info'][$id]['default_sort_order']),
        'align' => 'center',
      );
      $row[] = array(
        'data' => backdrop_render($form['default'][$id]),
        'align' => 'center',
      );
    }
    else {
      $row[] = '';
      $row[] = '';
      $row[] = '';
    }
    $row[] = array(
      'data' => backdrop_render($form['info'][$id]['empty_column']),
      'align' => 'center',
    );
    $rows[] = $row;
  }

  // Add the special 'None' row.
  $rows[] = array(t('None'), '', '', '', '', '', '', '', '', '', '', '', array(
    'align' => 'center',
    'data' => backdrop_render($form['default'][-1]),
  ), '');

  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= backdrop_render_children($form);
  return $output;
}

/**
 * Themes a no summary for the column.
 */
function theme_views_summarize_type_none($variables) {
  return '';
}

/**
 * Themes the count of values in the column.
 */
function theme_views_summarize_type_count($variables) {
  $values = $variables['values'];
  $options = $variables['options'];

  $header = _views_summarize_get_header(t('Count'), $options);

  $values2 = array();
  if (!empty($values) && is_array($values)) {
    foreach ($values as $value) {
      if (empty($options['views_style_options']['include_empties'])) {
        if (isset($value) && $value != '') {
          $values2[] = strip_tags($value);
        }
      }
      else {
        $values2[] = strip_tags($value);
      }
    }
  }

  $result = count(array_filter($values2, '_views_summarize_array_filter'));

  $summary = _views_summarize_get_summary_output($result, $options);

  return theme('table', array(
    'header' => $header,
    'rows' => array(
      array(
        $summary,
      ),
    ),
  ));
}

/**
 * Checks whether the given value is set (i.e., not null) or not.
 *
 * @param int $value
 *   The value to check.
 */
function _views_summarize_array_filter($value) {
  return isset($value);
}

/**
 * Themes the number of unique values in the column.
 */
function theme_views_summarize_type_unique($variables) {
  $values = $variables['values'];
  $options = $variables['options'];

  $header = _views_summarize_get_header(t('Unique'), $options);

  $values2 = array();
  if (!empty($values) && is_array($values)) {
    foreach ($values as $value) {
      if (empty($options['views_style_options']['include_empties'])) {
        if (isset($value) && $value != '') {
          $values2[] = strip_tags($value);
        }
      }
      else {
        $values2[] = strip_tags($value);
      }
    }
  }

  $result = count(array_unique(array_filter($values2, '_views_summarize_array_filter')));

  $summary = _views_summarize_get_summary_output($result, $options);

  return theme('table', array(
    'header' => $header,
    'rows' => array(
      array(
        $summary,
      ),
    ),
  ));
}

/**
 * Themes the minimum and maximum values in the column.
 */
function theme_views_summarize_type_range($variables) {
  $values = $variables['values'];
  $options = $variables['options'];

  $header = _views_summarize_get_header(t('Range'), $options, TRUE, TRUE);

  $values2 = array();
  if (!empty($values) && is_array($values)) {
    foreach ($values as $value) {
      if (empty($options['views_style_options']['include_empties'])) {
        if (isset($value) && ($value != '' || is_numeric($value))) {
          $values2[] = floatval(_views_summarize_get_cleaned_value($value, $options));
        }
      }
      else {
        if (isset($value) && $value == '' && !is_numeric($value)) {
          $values2[] = '';
        }
        else {
          $values2[] = floatval(_views_summarize_get_cleaned_value($value, $options));
        }
      }
    }
  }

  $min = _views_summarize_get_formatted_summary(min($values2), $options);
  $max = _views_summarize_get_formatted_summary(max($values2), $options);

  $min = _views_summarize_get_summary_output($min, $options);
  $max = _views_summarize_get_summary_output($max, $options);

  return theme('table', array(
    'header' => $header,
    'rows' => array(
      array(
        t('Min'),
        $min,
      ),
      array(
        t('Max'),
        $max,
      ),
    ),
  ));
}

/**
 * Themes the total of the values in the column.
 */
function theme_views_summarize_type_total($variables) {
  $values = $variables['values'];
  $options = $variables['options'];

  $header = _views_summarize_get_header(t('Total'), $options, FALSE);

  $total = 0;
  if (!empty($values) && is_array($values)) {
    foreach ($values as $value) {
      $total += floatval(_views_summarize_get_cleaned_value($value, $options));
    }
  }

  $result = _views_summarize_get_formatted_summary($total, $options);

  $summary = _views_summarize_get_summary_output($result, $options);

  return theme('table', array(
    'header' => $header,
    'rows' => array(
      array(
        $summary,
      ),
    ),
  ));
}

/**
 * Themes the average of the values in the column.
 */
function theme_views_summarize_type_average($variables) {
  $values = $variables['values'];
  $options = $variables['options'];

  $header = _views_summarize_get_header(t('Average'), $options);

  $total = 0;
  $count = 0;
  if (!empty($values) && is_array($values)) {
    foreach ($values as $value) {
      if (empty($options['views_style_options']['include_empties'])) {
        if (isset($value) && $value != '') {
          $total += floatval(_views_summarize_get_cleaned_value($value, $options));
          $count++;
        }
      }
      else {
        $total += floatval(_views_summarize_get_cleaned_value($value, $options));
        $count++;
      }
    }
  }

  if ($total != 0 && $count != 0) {
    $result = _views_summarize_get_formatted_summary($total / $count, $options);
  }
  else {
    $result = 0;
  }

  $summary = _views_summarize_get_summary_output($result, $options);

  return theme('table', array(
    'header' => $header,
    'rows' => array(
      array(
        $summary,
      ),
    ),
  ));
}

/**
 * Themes a spread table for the values in the column.
 */
function theme_views_summarize_type_spread($variables) {
  $values = $variables['values'];
  $options = $variables['options'];

  $header = _views_summarize_get_header(t('Spread'), $options, TRUE, TRUE);

  $hist = array();
  $rows = array();
  if (!empty($values) && is_array($values)) {
    foreach ($values as $value) {
      if (empty($options['views_style_options']['include_empties'])) {
        if (isset($value) && $value != '') {
          if (!isset($hist[$value])) {
            $hist[$value] = 0;
          }
          $hist[$value]++;
        }
      }
      else {
        if (!isset($hist[$value])) {
          $hist[$value] = 0;
        }
        $hist[$value]++;
      }
    }

    foreach ($hist as $value => $count) {
      if (empty($options['views_style_options']['include_empties'])) {
        if (isset($value) && ($value != '' || is_numeric($value))) {
          $value = strip_tags($value);
          $rows[$value] = array($value, $count);
        }
      }
      else {
        if (isset($value) && $value == '' && !is_numeric($value)) {
          $empty_string = t('(empty)');
          $rows[$empty_string] = array($empty_string, $count);
        }
        else {
          $value = strip_tags($value);
          $rows[$value] = array($value, $count);
        }
      }
    }

    if (version_compare(phpversion(), '5.4.0', '>=')) {
      ksort($rows, SORT_NATURAL);
    }
    else {
      ksort($rows);
    }
  }

  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
  ));
}

/**
 * Gets the record's value after stripping invalid characters.
 *
 * @param string $label
 *   The value from which to strip invalid characters.
 * @param array $options
 *   The options element of the variables array that is passed into the summary
 *   theme function.
 * @param bool $check_empties
 *   Specify TRUE if the summary might include or exclude empty values.
 * @param bool $colspan
 *   Specify TRUE to add colspan with a value of 2.
 *
 * @return array
 *   The value with invalid characters removed.
 */
function _views_summarize_get_header($label, array $options, $check_empties = TRUE, $colspan = FALSE) {
  if ($check_empties) {
    if (empty($options['views_style_options']['include_empties'])) {
      $label = $label . ' ' . t('(excluding empty values)');
    }
    else {
      $label = $label . ' ' . t('(including empty values)');
    }
  }

  $header = array(array('data' => $label));

  if ($colspan) {
    $header[0]['colspan'] = 2;
  }

  return $header;
}

/**
 * Gets the record's value after stripping invalid characters.
 *
 * @param string $value
 *   The value from which to strip invalid characters.
 * @param array $options
 *   The options element of the variables array that is passed into the summary
 *   theme function.
 *
 * @return array
 *   The value with invalid characters removed.
 */
function _views_summarize_get_cleaned_value($value, array $options) {
  $value = preg_replace('/[^0-9\.\,\-]/', '', strip_tags($value));

  if (!empty($options['field_settings']['thousand_separator'])) {
    $value = str_replace($options['field_settings']['thousand_separator'], '', $value);
  }
  if (!empty($options['field_settings']['decimal_separator'])) {
    $value = str_replace($options['field_settings']['decimal_separator'], '.', $value);
  }

  return $value;
}

/**
 * Gets the summary's formatted result.
 *
 * @param string $total
 *   The summary to format.
 * @param array $options
 *   The options element of the variables array that is passed into the summary
 *   theme function.
 *
 * @return array
 *   The format settings in an associative array.
 */
function _views_summarize_get_formatted_summary($total, array $options) {
  $format_settings = array(
    'precision' => 0,
    'decimal_separator' => NULL,
    'thousand_separator' => NULL,
  );

  if (!empty($options['views_style_options']['precision'])) {
    $format_settings['precision'] = (int) $options['views_style_options']['precision'];
  }
  if (!empty($options['views_style_options']['decimal'])) {
    $format_settings['decimal_separator'] = $options['views_style_options']['decimal'];
  }
  if (!empty($options['views_style_options']['thousand'])) {
    $format_settings['thousand_separator'] = $options['views_style_options']['thousand'];
  }

  $summary = '';
  if (is_numeric($total)) {
    $summary = number_format(
      $total,
      $format_settings['precision'],
      $format_settings['decimal_separator'],
      $format_settings['thousand_separator']
    );
  }

  return $summary;
}

/**
 * Gets the prefix and suffix for a summary's output, if they exist.
 *
 * @param string $result
 *   The calculated summary.
 * @param array $options
 *   The options element of the variables array that is passed into the summary
 *   theme function.
 *
 * @return array
 *   The prefix and suffix in an associative array.
 */
function _views_summarize_get_summary_output($result, array $options) {
  $prefix_suffix = array(
    'prefix' => '',
    'suffix' => '',
  );

  if (!empty($options['views_style_options']['prefix'])) {
    $prefix_suffix['prefix'] = $options['views_style_options']['prefix'];
  }
  if (!empty($options['views_style_options']['suffix'])) {
    $prefix_suffix['suffix'] = $options['views_style_options']['suffix'];
  }

  return $prefix_suffix['prefix'] . $result . $prefix_suffix['suffix'];
}
