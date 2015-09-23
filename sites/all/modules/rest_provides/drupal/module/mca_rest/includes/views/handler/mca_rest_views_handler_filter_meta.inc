<?php
/**
 * Created by PhpStorm.
 * User: sang
 * Date: 5/25/15
 * Time: 4:29 PM
 */

/**
 * This handler get filter field that have been configuration in options to send to query plugin instead of real_field
 *
 * Class mca_data_export_handler_filter_meta
 */
class mca_rest_views_handler_filter_meta extends views_handler_filter_string {

  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();
    $field = (empty($this->table_alias)?'':("$this->table_alias.")) . (empty($this->options['filter_key'])?$this->real_field:$this->options['filter_key']);

    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($field);
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['filter_key'] = array('default' => FALSE, 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['filter_key'] = array(
      '#type' => 'textfield',
      '#title' => 'Filter Key',
      '#default_value' => $this->options['filter_key'],
    );
  }
}

