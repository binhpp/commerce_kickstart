<?php
class views_handler_field_topup_package extends views_handler_field {
    function query() {
        $this->field_alias = $this->real_field;
    }
}