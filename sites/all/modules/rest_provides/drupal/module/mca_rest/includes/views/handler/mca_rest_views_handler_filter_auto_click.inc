<?php
class mca_rest_views_handler_filter_auto_click extends views_handler_filter_in_operator {

    function get_value_options() {
        if (!isset($this->value_options)) {
            $this->value_options = array();
            $this->value_options[0] = 'Off';
            $this->value_options[1] = '1 minute';
            $this->value_options[5] = '5 minute';
            $this->value_options[10] = '10 minute';
            $this->value_options[15] = '15 minute';
        }
    }
    function value_form(&$form, &$form_state) {
        parent::value_form($form,$form_state);
        $isAuto = $form_state['input']['auto_filter'];
        $elem_id = $this->options['element_click_id'];
        $interval = ($isAuto=='All')?$this->options['element_click_interval']:($isAuto * 60);
        if(!empty($elem_id) && !empty($interval) && $interval > 0){
            $form['auto_click_script'] = array(
                '#type' => "item",
                '#element_click_id' => $elem_id,
                '#element_click_interval' => $interval,
                '#after_build' => array('_mca_rest_views_handler_filter_auto_click_after_build'),
            );
        }
    }

    function option_definition() {
        $options = parent::option_definition();
        $options['element_click_id'] = array('default' => false, 'translatable' => TRUE);
        $options['element_click_interval'] = array('default' => false, 'translatable' => TRUE);
        return $options;
    }

    function operator_form(&$form, &$form_state) {
        parent::operator_form($form,$form_state);
        $form['element_click_id'] = array(
            '#type' => 'textfield',
            '#title' => 'Clickable Element Id',
            '#default_value' => $this->options['element_click_id'],
        );
        $form['element_click_interval'] = array(
            '#type' => 'textfield',
            '#title' => 'Click Interval',
            '#description' => 'Interval in second to perform click on element when select "-Any-" option',
            '#default_value' => $this->options['element_click_interval'],
        );
    }
}

function _mca_rest_views_handler_filter_auto_click_after_build($element, &$form_state){
    $elemClickId = empty($element['#element_click_id'])?'':$element['#element_click_id'];
    if(empty($elemClickId)){
        return;
    }
    $interval = empty($element['#element_click_interval'])?'':$element['#element_click_interval'];
    if(empty($interval) || $interval==false){
        $interval = 5*60*1000;  //5 minus
    }else{
        $interval = $interval * 1000;
    }
    $script = "
                jQuery(document).ready(function() {
                    setTimeout(function(){jQuery('$elemClickId').click();},$interval);
                });
              ";
    drupal_add_js($script,array('type'=>'inline'));
}