<?php
/**
 * Created by PhpStorm.
 * User: monster
 * Date: 14/08/2015
 * Time: 14:16
 */
class subscription_rest_package_plugin_query extends views_plugin_query {

  var $offset = 1;
  /**
   * An array of fields.
   */
  var $fields = array();

  /**
   * An array of sections of the WHERE query. Each section is in itself
   * an array of pieces and a flag as to whether or not it should be AND
   * or OR.
   */
  var $where = array();

  /**
   * A simple array of order by clauses.
   */
  var $orderby = array();

  /**
   * The current used pager plugin.
   *
   * @var views_plugin_pager
   */
  var $pager = NULL;

  /**
   * An array mapping table aliases and field names to field aliases.
   */
  var $field_aliases = array();

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


  function add_orderby($table, $field = NULL, $order = 'ASC', $alias = '', $params = array()) {
//    if ($field) {
//      $as = $this->add_field($table, $field, $as, $params);
//    }

    $this->orderby[] = array(
      'field' => $field,
      'direction' => strtoupper($order)
    );

    /**
     * -- removing, this should be taken care of by field adding now.
     * -- leaving commented because I am unsure.
    // If grouping, all items in the order by must also be in the
    // group by clause. Check $table to ensure that this is not a
    // formula.
    if ($this->groupby && $table) {
    $this->add_groupby($as);
    }
     */
  }

  function add_where($group, $field, $value = NULL, $operator = NULL) {
    // Ensure all variants of 0 are actually 0. Thus '', 0 and NULL are all
    // the default group.
    if (empty($group)) {
      $group = 0;
    }

    // Check for a group.
    if (!isset($this->where[$group])) {
      $this->set_where_group('AND', $group);
    }

    $this->where[$group]['conditions'][] = array(
      'field' => $field,
      'value' => $value,
      'operator' => $operator,
    );
  }

  /**
   * Set an OFFSET on the query, specifying a number of results to skip
   */
  function set_offset($offset) {
    $this->offset = $offset;
  }

  function query($get_count = FALSE) {
    $data = '';
//    if (!empty($this->orderby)) {
//      foreach ($this->orderby as $key => $item) {
//        if ($data == '') {
//          $data .= '"order_by":"' . $item['field'] . '"';
//          if ($item['direction'] == 'ASC') {
//            $data .= ',"order_asc":' . 'true';
//          } else {
//            $data .= ',"order_asc":' . 'false';
//          }
//        } else {
//          $data .= ',"order_by":"' . $item['field'] . '"';
//          if ($item['direction'] == 'ASC') {
//            $data .= ',"order_asc":' . 'true';
//          } else {
//            $data .= ',"order_asc":' . 'false';
//          }
//        }
//      }
//    }
    $filters = array();
    if (!empty($this->orderby)) {
      foreach ($this->orderby as $key => $item) {
        $filters['order_by'] = $item['field'];
        if ($item['direction'] == 'ASC') {
          $filters['order_asc'] = 'true';
        } else {
          $filters['order_asc'] = 'false';
        }
      }
    }
    if (!empty($this->where)) {
      foreach ($this->where as $key => $item) {
        if (!empty($item['conditions']['0']['value'])) {
          $filters[$item['conditions']['0']['field']] = $item['conditions']['0']['value'];
        }
      }
    }
//    if (!empty($this->where)) {
//      foreach ($this->where as $key => $item) {
//        if (!empty($item['conditions']['0']['value'])) {
//          if ($data == '') {
//            $data .= '"' . $item['conditions']['0']['field'] . '":"' . $item['conditions']['0']['value'] . '"';
//          } else {
//            $data .= ',"' . $item['conditions']['0']['field'] . '":"' . $item['conditions']['0']['value'] . '"';
//          }
//        }
//
//      }
//    }

    if (!$get_count) {
      if (!empty($this->limit) || !empty($this->offset)) {
        $limit  = intval(!empty($this->limit) ? $this->limit : 999999);
        $offset = intval(!empty($this->offset) ? $this->offset : 0);
//        $query->range($offset, $limit);
        if ($this->offset != 0 && $this->limit != 999999) {
          $filters['page_number'] = $this->offset/$this->limit + 1;
        }
//        $filters['page_number'] = $offset;
        if ($limit < 999999)
        {
          $filters['page_size'] = $limit;
        }
      }
    }

//    $data = '{' . $data . '}';

    return $filters;
  }

  function build(&$view) {

    // Store the view in the object to be able to use it later.
    $this->view = $view;

    $view->init_pager();

    // Let the pager modify the query to add limits.
    $this->pager->query();

    $view->build_info['query'] = $this->query();
    $view->build_info['count_query'] = $this->query(TRUE);
  }

  function execute(&$view) {
    $url = 'http://localhost:8181/subscription-rest/package/search';
    $headers = array();



    $filter = $this->query();

    $options = array(
      'method' => 'POST',
      'data' => json_encode($filter),
      'headers' => $headers,
    );

    $respone = drupal_http_request($url, $options);
    $json_output = json_decode($respone->data, true);
    foreach($json_output['list'] as $key => $item) {
      $row = new stdClass();
      foreach($item as $delta => $property) {
        $row->$delta = $property;
      }
      $view->result[] = $row;
    }
    $view->total_rows = $json_output['total'];
    $view->current_page = (int) $filter['page_number'];
    $view->items_per_page = (int) $filter['page_size'];
    empty($filter['period_id_merge']) ?: $view->period_id_merge = $filter['period_id_merge'];
    $this->pager->total_items = $json_output['total'];
    $this->pager->update_page_info();


  }
}