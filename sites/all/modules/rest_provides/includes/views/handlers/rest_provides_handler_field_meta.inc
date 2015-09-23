<?php
class rest_provides_handler_field_meta extends views_handler_field {
    function get_value($values, $field = NULL) {
        $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;
            $sub_fields = explode('.',$alias);
        $value = $values;
        foreach ($sub_fields as $part) {
            if (is_object($value) && isset($value->{$part})) {
                $value = $value->{$part};
            }
            elseif(is_array($value) && isset($value[$part])) {
                $value = $value[$part];
            }
            else {
                $value = '';
                break;
            }
        }
        return $value;
    }
}