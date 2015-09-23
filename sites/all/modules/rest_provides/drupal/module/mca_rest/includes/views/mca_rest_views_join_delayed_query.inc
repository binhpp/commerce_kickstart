<?php 

/**
 * Implement <pre>delayed_join(&$view, $relationship)</pre> to join rest result (array of stdClass) with another set of result <br/>
 * Declare <pre>execute_join_query(&$view, $relationship)</pre> as abstract method so that result can be implemented by subclass
 * <p>How this object is constructed can be referred from views_handler_relationship.
 * </p>
 * 
 * @author Nam Pham
 * @see views_join
 * @see views_handler_relationship 
 * 
 */
class mca_rest_views_join_delayed_query extends views_join {
	
	/**
	 * execute_jion
	 * @param view $view
	 * @param array $relationship
	 */
	function execute_join_query(&$view, $relationship) {}
	
	/**
	 * join $view->result, called by view_query_plugin->execute()
	 * @param view $view
	 * @param string $alias relationship alias
	 * @param array $relationship
	 */
	function delayed_join(&$view, $alias, $relationship) {
		$mapping = $this->execute($view, $relationship);
		
		// joined fields from views
		$fields = array();
		foreach ($view->field as &$field) {
			if ($field->table == $this->table && $field->relationship == $alias) {
			  $field->field_alias = $alias.'_'.$field->field_alias;
				$fields[] = &$field;
			}
		}
		
		if (empty($mapping)) return;
		
		$left_handlers = array();
		$right_handlers = array();
		foreach ($view->result as &$left) {
			// read left_value
			if ( !isset($left_handlers[$this->left_field]) ) {
			  $handler = views_get_handler($this->left_table,$this->left_field,'field');
			  $handler->field_alias = $this->left_field;
			  $left_handlers[$this->left_field] = &$handler;
			}
			else {
			  $handler = &$left_handlers[$this->left_field];
			}
      $lvalue = $handler->get_value($left);
      if (empty($lvalue)) continue;
			
			// read & assign join/right_value from
			if (!isset($mapping[$lvalue])) continue;
			$rec = &$mapping[$lvalue];
			
			// map join fields' values
			foreach ($fields as &$field) {
        
			  $curObj = NULL;
			  if (strpos($field->field, '.') == false) {
			    if (!isset($right_handlers[$field->field])) {
			      $rhandler = views_get_handler($this->table, $field->real_field, 'field');
			      $rhandler->field_alias = $field->real_field;
			      $right_handlers[$field->field] = $rhandler;
			    }
			    else {
			      $rhandler = &$right_handlers[$field->field];
			    }
			    $curObj = $rhandler->get_value($rec);
			  }
			  else {
  			  $sub_fields = explode('.', $field->field);
          $field_alias = array_shift($sub_fields);
          $first_obj = isset($left->{$field_alias})?$left->{$field_alias}:NULL;
          $curObj = NULL;
          // extract object hier archical: meta.key = [meta, key]
          while(!empty($sub_fields)){
            if($curObj==NULL){
              if(! (isset($first_obj) && is_object($first_obj))){
                  $first_obj = new stdClass();
              }
              $curObj = &$first_obj;
            }
            $sub_field = array_shift($sub_fields);
            if(empty($sub_fields)){
              $curObj->{$sub_field}=$field->get_value($rec);
            }else{
              $obj = new stdClass();
              $curObj->{$sub_field} = $obj;
              $curObj = &$obj;
            }
          }
			  }
        
			  /**
			   * TODO review this with old code
			  if($curObj==NULL){
            if(isset($left->{$first_field})){
              //Should use a subclass of mca_rest_handler_field for field handler
              $field_name_full = "$field->table.$first_field";
              $left->{$field_name_full} = $rec->{$field->field};
            }else{
              $left->{$first_field} = $rec->{$field->field};
            }
        }else{
          $left->{$first_field} = $first_obj;
        }
         */
			  $left->{$field->field_alias} = $curObj;
			}
		}
	}
	
	/**
	 * 
	 * @param view $view
	 * @param array $relationship
	 */
	function execute(&$view, &$relationship) {
		$key = get_class($this).':'.$this->left_table.':'.$this->left_field.':'.$this->table.':'.$this->field;
		$execute = drupal_static(__FUNCTION__, array());
		
		if (!isset($execute[$key])) {
			$result = $this->execute_join_query($view, $relationship);
			
			$mapping = array();
			$handler = views_get_handler($this->table, $this->field, 'field');
			if (empty($handler->aliases[$this->field]))  // if this field is not configured, initialize configuration data (views_field_handler.inc)
			  $handler->aliases[$this->field] = $this->field;
			foreach ($result as &$rec) {
			  $value = $handler->get_value($rec, $this->field);
				if (!isset($value)) continue;
				// TODO use correct views_handler_field from $view->field
				$mapping[$value] = &$rec;
			}
			
			$execute[$key] = &$mapping;
		}
		
		return $execute[$key];
	}
}