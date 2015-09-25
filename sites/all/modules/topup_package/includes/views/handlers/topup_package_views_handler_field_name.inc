<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 25/09/2015
 * Time: 15:05
 */
class topup_package_views_handler_field_name extends views_handler_field {
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
        return l($values->name, "topup_package/" . $id);
    }
}