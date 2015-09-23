<?php
/**
 * Implements hook_views_data_alter()
 */
function employees_views_data_alter(&$data) {
    $data['views']['employees_create_employees_form'] = array(
        'title' => t('Create employees form'),
        'help' => t('Provides a form for creating employees'),
        'area' => array(
            'handler' => 'employees_handler_create_employees_form_area',
        ),
    );
}