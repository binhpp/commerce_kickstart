<?php

class subscription_rest_package_name_handler_field extends views_handler_field {
  function query() {
    $this->field_alias = $this->real_field;
  }
}