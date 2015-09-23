<?php
/**
 * Created by PhpStorm.
 * User: sang
 * Date: 5/25/15
 * Time: 4:22 PM
 */

/**
 * This handler will extract value in object by key that have been configuration.
 * data_key has format multi level: field__field__field...
 * Class mca_data_export_handler_field_meta
 */
class mca_rest_views_handler_field_meta extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);

    if (!empty($this->definition['data_key']))
      $this->options['data_key'] = $this->definition['data_key'];

    if (!empty($this->definition['data_format']))
      $this->options['data_format'] = $this->definition['data_format'];
  }

  function get_value($values, $field = NULL) {
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;

    $data_key = $this->options['data_key'];
    $data_format = $this->options['data_format'];

    $sub_fields = explode('__', $data_key);
    $value = $values;
    foreach ($sub_fields as $part) {
      if (is_object($value) && isset($value->{$part})) {
        $value = $value->{$part};
      }
      elseif (is_array($value) && isset($value[$part])) {
        $value = $value[$part];
      }
      else {
        $value = '';
        break;
      }
    }
    if(!empty($value) && !empty($data_format)){
      $value = $this->_get_formatted_value($value,$data_format);
    }

    return $value;
  }
  function render($values) {
    $value = $this->get_value($values);
    if ((is_array($value) || is_object($value)) && !empty($value))
      $value = json_encode($value);
    return $this->sanitize_value($value);
  }

  function _get_formatted_value($value, $format){
    if(strpos($format,'number')===0){
      $fVal = str_replace("number|","",$format);
      $nVal = sprintf($fVal,$value);
      return $nVal;
    }

    if(strpos($format,'date')===0){
      $fVal = str_replace("date|","",$format);
      $nVal = $value->format($fVal);
      return $nVal;
    }

    if(strpos($format,'mapping')===0){
      $fVal = str_replace("mapping|","",$format);
      $data = json_decode($fVal);
      $nVal = $data[$value];
      return $nVal;
    }

    if(strpos($format,'dump')===0){
      //support for debug
      $nVal = print_r($value,true);
      return $nVal;
    }

    return $value;
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();
    // Add the field.
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();

    $data_key = $this->options['data_key'];
    $this->field_alias = $this->query->add_field(empty($this->table_alias)?$this->table:$this->table_alias, $data_key, NULL, $params);

    $this->add_additional_fields();
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['data_key'] = array('default' => FALSE, 'translatable' => FALSE);
    $options['data_format'] = array('default' => FALSE, 'translatable' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['data_key'] = array(
      '#type' => 'textfield',
      '#title' => 'Data Key',
      '#default_value' => $this->options['data_key'],
      '#description' => t('E.g: meta[__key1][__key2]'),
    );
    $form['data_format'] = array(
      '#type' => 'textfield',
      '#title' => 'Data Format',
      '#default_value' => $this->options['data_format'],
      '#description' => t('Either: number|[xyz], date|[xyz], mapping|[xzy]'),
    );
  }
}

