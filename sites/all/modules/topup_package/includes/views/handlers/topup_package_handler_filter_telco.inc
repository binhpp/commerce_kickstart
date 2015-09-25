<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 25/09/2015
 * Time: 17:09
 */
class topup_package_handler_filter_telco extends views_handler_filter_in_operator {
    function get_value_options() {
        if (!isset($this->value_options)) {
            $this->value_title = t('Telco');
            $this->value_options = array();
            foreach (topup_package_get_telcos() as $name => $title) {
                $this->value_options[$name] = $title;
            }
        }
    }
}