<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 24/09/2015
 * Time: 17:27
 */

class icb_inventory_handler_field_edit_detail extends views_handler_field {
    function construct() {
        parent::construct();
        $this->additional_fields['id'] = 'id';
    }
    function query() {
        $this->ensure_my_table();
        $this->add_additional_fields();
    }

    function render($values) {
        $id = $this->get_value($values, 'id');
        return l('Edit', "icb-inventory/" . $id);
    }
}