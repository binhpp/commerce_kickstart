<?php
/**
 * Created by PhpStorm.
 * User: sang
 * Date: 7/28/15
 * Time: 3:40 PM
 */
class mca_rest_views_handler_sort extends views_handler_sort {
  /**
   * Override parent::option_definition()
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['sort_field'] = array('default' => $this->real_field);
    return $options;
  }

  /**
   * Override parent::query()
   */
  function query() {
    $this->query->add_orderby($this->table_alias, $this->options['sort_field'], $this->options['order']);
  }
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['sort_field'] = array(
      '#type' => 'textfield',
      '#title' => t('The solr field to query'),
      '#default_value' => $this->options['sort_field'],
    );
  }
}

