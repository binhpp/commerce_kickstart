<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 25/09/2015
 * Time: 15:36
 */
class topup_package_views_handler_filter_status extends views_handler_filter_in_operator {
    function get_value_options() {
        if (!isset($this->value_options)) {
            $this->value_title = t('Status');
            $this->value_options = array();
            foreach (topup_package_status_options() as $name => $title) {
                $this->value_options[$name] = $title;
            }
        }
    }
}