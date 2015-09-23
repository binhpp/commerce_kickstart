<?php 
class mca_rest_views_handler_field_date extends views_handler_field_date {
	/**
	 * retrive timestamp value by calling date
	 * @see views_handler_field::get_value()
	 */
	function get_value($values, $field = NULL) {
    $value = parent::get_value($values, $field);
    if (!empty($value) && $value instanceof DateTime) {
    	$value = $value->getTimestamp();
    }
    return $value;
  }
}