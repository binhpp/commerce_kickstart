<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 14/09/2015
 * Time: 13:19
 */

function alter_address_autocomplete_callback($string = "") {
    $matches = array();
    if($string) {
        $city = variable_get('alter_postal_address_widget', array());
        $results = explode("\r\n", $city);
        $key = array();
        foreach($results as $result) {
            if(strpos(mb_strtolower($result), mb_strtolower($string)) !== FALSE) {
                array_push($key, $result);
            }
        }
        if(!empty($key)) {
            foreach($key as $value) {
                $matches[$value] = check_plain($value);
            }
        }
    }
    drupal_json_output($matches);
}