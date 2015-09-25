<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 25/09/2015
 * Time: 17:42
 */
class topup_package_views_handler_field_edit extends views_handler_field {
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
        return l('Edit', "topup_package/" . $id ."/edit");
    }
}