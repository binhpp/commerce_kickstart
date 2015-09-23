<?php

class rest_provides_views_plugins_query extends views_plugin_query_default {
    /**
     * Executes the query and fills the associated view object with according
     * values.
     *
     * Values to set: $view->result, $view->total_rows, $view->execute_time,
     * $view->current_page.
     */
    function add_field($table, $field, $alias = '', $params = array()) {
        return $field;
    }

    function query($get_count = FALSE) {
        $options = $this->build_condition();
        return $options;
    }

    function add_where($group, $field, $value = NULL, $operator = NULL) {
        $this->where['rest_provides'][] = array(
            'field' => $field,
            'value' => $value,
            'operator' => $operator,
        );
    }

    function build_condition($where = 'where') {
        $conditions = array(
            'pageNumber' => $this->pager->get_current_page()+1,
            'pageSize' => $this->pager->get_items_per_page(),
        );

        $conds = array_key_exists('rest_provides', $this->where) ? $this->where['rest_provides'] : array();
        foreach ($conds as $condition) {
            list($table, $field) = explode('.', $condition['field']);
            $value = $condition['value'];
            if ($table == 'rest_provides') {
                switch($field){
                    case 'status':
                    case 'type':
                        $conditions[$field] = $value[0];
                        break;
                    default:
                        $search = new stdClass();
                        $search->$field = $value;
                        $conditions['meta'] = $search;
                        break;
                }
            }
        }

        return $conditions;
    }

    function execute(&$view) {
        $start = microtime(TRUE);
        $query = $this->query();
        $pageview = rest_provides_search($query);
        $this->pager->total_items = $pageview->total;
        $this->pager->update_page_info();
        $view->result = $pageview->items;
        $view->total_rows = 20;
        $view->current_page = $this->pager->get_current_page();

        $view->execute_time = microtime(TRUE) - $start;
    }
}