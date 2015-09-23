<?php

class mca_rest_views_handler_field  extends views_handler_field {

    /**
     * Base field to get value with field have prefix is table name
     * Handler use in case relationship have multi column with same a name
     * @param $values
     * @param null $field
     * @return string
     */
    function get_value($values, $field = NULL) {
        $field_name_full  = "$this->table.$this->field";
        if(isset( $values->$field_name_full)){
            $value = $values->$field_name_full;
            return "$value";
        }
        return parent::get_value($values,$field);
    }


}
