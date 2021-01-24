<?php

/**
 * Style plugin to render each item as a row in a table.
 *
 * @ingroup views_style_plugins
 */
class views_summarize_plugin_style_tablesummarized extends views_plugin_style_table {

  /**
   * Modify the options form to add options for this module.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['#theme'] = 'views_summarize_plugin_style_tablesummarized';
    $columns = $this->sanitize_columns($this->options['columns']);
    foreach ($columns as $field) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
      $id = 'edit-style-options-columns-' . $safe;
      $form['info'][$field]['prefix'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($this->options['info'][$field]['prefix']) ? $this->options['info'][$field]['prefix'] : '',
        '#size' => 6,
        '#dependency' => array($id => array($field)),
      );
      $form['info'][$field]['summarize'] = array(
        '#type' => 'select',
        '#options' => views_summarize_get_handlers(),
        '#default_value' => !empty($this->options['info'][$field]['summarize']) ? $this->options['info'][$field]['summarize'] : 'none',
        '#dependency' => array($id => array($field)),
      );
      $form['info'][$field]['suffix'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($this->options['info'][$field]['suffix']) ? $this->options['info'][$field]['suffix'] : '',
        '#size' => 6,
        '#dependency' => array($id => array($field)),
      );
      $form['info'][$field]['thousand'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($this->options['info'][$field]['thousand']) ? $this->options['info'][$field]['thousand'] : ',',
        '#size' => 6,
        '#dependency' => array($id => array($field)),
      );
      $form['info'][$field]['decimal'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($this->options['info'][$field]['decimal']) ? $this->options['info'][$field]['decimal'] : '.',
        '#size' => 6,
        '#dependency' => array($id => array($field)),
      );
      $form['info'][$field]['precision'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($this->options['info'][$field]['precision']) ? $this->options['info'][$field]['precision'] : '2',
        '#size' => 6,
        '#dependency' => array($id => array($field)),
      );
    }

    $form['summary_only'] = array(
      '#title' => t('Display the summary row only'),
      '#description' => t('If checked only the summary row will be displayed,'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['summary_only'],
    );
  }

  /**
   * Sets default options for this module.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['summary_only'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }

}
