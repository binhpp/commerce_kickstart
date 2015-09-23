<?php 

/**
 * this class is designed to join _field_data (referenced entity)
 * @author Nam Pham
 *
 */
abstract class mca_rest_views_join_ref_field extends mca_rest_views_join_delayed_query {
  
  /**
   * return from $view->result and return an associative array of rows whose elements are array of 
   * row instance and are keyed by the foreign key value
   * @param string $base_field name of the left field
   * @param string $field_name name of the field attached to entity instances
   * @param view $view
   * @param array $relationship
   */
  abstract function get_mapped_data($base_field, $field_name, $view, $relationship);
  
  /**
   * return an associative array of keyed objects referred by $view->result
   * @param array $keys
   * @param string $field_name name of the field attached to entity instances
   * @param view $view
   * @param array $relationship
   */
  abstract function get_referenced_data($keys, $field_name, $view, $relationship);
  
  function execute_join_query(&$view, $relationship) {
    // prepare short_names
    $values = array();
    $field_name = $relationship->field;
    
    $entity_types = mca_rest_views_get_entity_types($view);
    if (empty($entity_types)) {
      watchdog('mca_user', 'Reference field mca_user_ref cannot find matching entity type regarding to base_table for @view_id (@display_id', array(
      '@view_id' => $view->name,
      '@display_id' => $view->current_display,
      ), WATCHDOG_ERROR);
      return;
    }
    
    $related = array();
    foreach ($entity_types as $entity_type => $entity_key) {
      $instances = field_info_instances($entity_type);
      foreach ($instances as $bundled_instances) {
        if (empty($bundled_instances[$field_name])) continue;
        $related[$entity_type] = $entity_key;
        break;
      }
    }
    
    if (count($related) != 1) {
      watchdog('mca_user', 'Reference field mca_user_ref find related entity and bundle for field @field_name for @view_id (@display_id', array(
      '@field_name' => $field_name,
      '@view_id' => $view->name,
      '@display_id' => $view->current_display,
      ), WATCHDOG_ERROR);
      return;
    }
    $base_field = array_values($related)[0];
    
    $mapped_rows = $this->get_mapped_data($base_field, $field_name, $view, $relationship);
    if (empty($mapped_rows)) return;
    
    $ref_rows = $this->get_referenced_data(array_keys($mapped_rows), $field_name, $view, $relationship);
    
    $row_field = $relationship->alias;
    foreach ($ref_rows as $ref_id => $ref_row) {
      $rows = $mapped_rows[$ref_id];
      // assign alias field
      foreach ($rows as &$row)
        $row->$row_field = $ref_row;
    }
    
    // assign relationship's fields
    foreach($view->field as $field) {
      if (empty($field->relationship) || $field->relationship != $relationship->alias)
        continue;
      
      if (isset($field->definition['mca_rest_field'])) {
        $old = $field->definition['mca_rest_field'];
        $new = $relationship->alias.'_'.$old;
        _mca_rest_views_joint_ref_field_assign_alias($old, $new, $field, $view, $row_field);
        // assign field_alias
        $field->field_alias = $new;
      }
      elseif (isset($field->definition['mca_rest_fields'])) {
        foreach ($field->definition['mca_rest_fields'] as $old) {
          $new = $relationship->alias.'_'.$old;
          _mca_rest_views_joint_ref_field_assign_alias($old, $new, $field, $view, $row_field);
          $field->aliases[$old] = $new;
        }
      }
      elseif (empty($field->field_alias) || $field->field_alias == 'unknown') {
        // translate field aliases values with prefix
        if (!empty($field->aliases)) {
          // assigned $field->aliases
          foreach ($field->aliases as $field_name => $field_alias) {
            foreach ($view->result as $row) {
              if (empty($row->$row_field) || !empty($row->$field_alias)) continue;
              $value = $field->get_value(empty($row->$row_field), $field_name);
              if (!empty($value))
                $row->$field_alias = $value;
            }
          }
        }
        else {
          // @todo resolve this case
        }
      }
      else {
        $cloned = clone($field);
        $cloned->relationship = NULL;
        $cloned->field_alias = substr($cloned->field_alias, strlen($row_field) + 1);
    
        $row_alias = $field->field_alias;
        foreach ($view->result as $row) {
          if (empty($row->$row_field)) continue;
          $row->$row_alias = $cloned->get_value($row->$row_field);
        }
      }
    }
  }
}

function _mca_rest_views_joint_ref_field_assign_alias($old_alias, $new_alias, $field, $view, $row_field) {
  $alias = empty($field->field_alias)?NULL:$field->field_alias;
  
  // get raw values from view handlers
  $values = array();
  $field->field_alias = $old_alias;
  foreach ($view->result as $rid => $row) {
    if (empty($row->$row_field)) continue;
    $values[$rid] = $field->get_value($row->$row_field);
  }
  
  foreach ($view->result as $rid => $row) {
    if (empty($values[$rid]) || !empty($row->$new_alias)) continue;
    $row->$new_alias = $values[$rid];
  }
  
  // reset field_alias
  $field->field_alias = $alias;
}
