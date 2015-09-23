<?php
class rest_package_views_plugin_query extends views_plugin_query {
    var $fields = array();
    function add_field($table, $field, $alias = '', $params = array()) {
        // Make sure an alias is assigned
        $alias = $alias ? $alias : $field;

        // PostgreSQL truncates aliases to 63 characters: http://drupal.org/node/571548

        // We limit the length of the original alias up to 60 characters
        // to get a unique alias later if its have duplicates
        $alias = strtolower(substr($alias, 0, 60));

        // Create a field info array.
        $field_info = array(
                'field' => $field,
                'table' => $table,
                'alias' => $alias,
            ) + $params;

        // Test to see if the field is actually the same or not. Due to
        // differing parameters changing the aggregation function, we need
        // to do some automatic alias collision detection:
        $base = $alias;
        $counter = 0;
        while (!empty($this->fields[$alias]) && $this->fields[$alias] != $field_info) {
            $field_info['alias'] = $alias = $base . '_' . ++$counter;
        }

        if (empty($this->fields[$alias])) {
            $this->fields[$alias] = $field_info;
        }

        // Keep track of all aliases used.
        $this->field_aliases[$table][$field] = $alias;

        return $alias;
    }
    function execute(&$view) {
        $url = 'http://localhost:8181/subscription-rest/package/search';
        $header = '';
        $options = array(
            'method' => 'POST',
            'data' => '{}',
            'header' => $header,
        );
        $response = drupal_http_request($url, $options);
        $json_output =json_decode($response->data,true);
        $view->result = array();
        foreach($json_output['list'] as $key => $item){
            $row = new stdClass();
            foreach($item as $delta => $value){
                $row->$delta = $value;
            }
            $view->result[] = $row;
        }
    }
}