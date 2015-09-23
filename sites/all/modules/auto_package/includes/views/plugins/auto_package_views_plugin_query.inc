<?php
/**
 * Created by PhpStorm.
 * User: root
 * Date: 08/09/2015
 * Time: 14:47
 */
class auto_package_views_plugin_query extends views_plugin_query_default {
    var $dynamic_fields = array();

    // used in case pager is not used by some display.
    // since we cannot get all items.
    var $override_current_page = -1;
    var $items_per_page = -1;
    function add_field($table, $field, $alias = '', $params = array()) {
        if (!isset($table)) {
            $this->dynamic_fields[$alias] = 'auto_package';
            return $alias;
        }
        elseif ($table != 'auto_package') {
            // field from another relationship: table_name__field_name
            if (stripos($table, '_auto_package') == strlen($table) - 9) {
                return substr($table, 0, strlen($table) - 8).'_'.$field;
            }
            else {
                $table.'__'.$field;
            }
        }
        return $field;
    }
    function execute(&$view) {
        return 'abc';
    }
    function query($get_count = FALSE) {
        if (!empty($this->options['query_tags']) &&
            is_array($this->options['query_tags']) &&
            in_array('database', $this->options['query_tags'])) {
            $options = $this->build_condition_database();
            return $options;
        }

        $options = $this->build_condition();
        return $options;
    }
}