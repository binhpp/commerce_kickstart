<?php
function employees_view($employees) {
    drupal_set_title(entity_label('employees', $employees));
    return entity_view('employees', array(entity_id('employees', $employees) => $employees), 'full');
}