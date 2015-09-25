<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 24/09/2015
 * Time: 17:30
 */
class icb_inventory_views_field_status extends views_handler_field {
    function render($values) {
        $value = $this->get_value($values);
        $options = icb_inventory_status_options();
        return $options[$value];
    }
}