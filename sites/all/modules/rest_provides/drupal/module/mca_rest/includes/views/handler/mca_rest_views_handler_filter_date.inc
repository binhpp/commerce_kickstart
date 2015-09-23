<?php

class mca_rest_views_handler_filter_date extends views_handler_filter_date  {
  /**
   * Overidden
   * @param unknown $field
   */
  function op_between($field) {
    $a = gmdate('Y-m-d\TH:i:s\Z',strtotime($this->value['min']));
    $b = gmdate('Y-m-d\TH:i:s\Z',strtotime($this->value['max']));
    
    // This is safe because we are manually scrubbing the values.
    // It is necessary to do it this way because $a and $b are formulas when using an offset.
    $operator = strtoupper($this->operator);
    $this->query->add_where($this->options['group'], $field, "[$a TO $b]");
  }
}