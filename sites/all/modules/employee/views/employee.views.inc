<?php
/**
 * Implement hook_views_date()
 */
function employee_views_data() {
    $data ['employee']['table']['group'] = t('Employee table');

    $data ['employee']['table']['base'] = array(
        'field' => 'eid', // This is the identifier field for the view.
        'title' => t('Employee'),
        'help' => t('Employee table stores employees.'),
        'weight' => -10,
    );

    $data['employee']['table']['entity type'] = 'employee';

    $data ['employee']['eid'] = array(
        'title' => t('Eid'),
        'help' => t('Employee id field.'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
            'click sortable' => TRUE, // This is use by the table display plugin.
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_numeric',
        ),
    );

    $data['employee']['uid'] = array(
        'title' => t('Author'),
        'help' => t('The user authoring the content. If you need more fields than the uid add the content: author relationship'),
        'relationship' => array(
            'title' => t('Author'),
            'help' => t('Relate content to the user who created it.'),
            'handler' => 'views_handler_relationship',
            'base' => 'users',
            'field' => 'uid',
            'label' => t('author'),
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_user_name',
        ),
        'argument' => array(
            'handler' => 'views_handler_argument_numeric',
        ),
        'field' => array(
            'handler' => 'views_handler_field_user',
        ),
    );

    $data ['employee']['employee_id'] = array(
        'title' => t('Employee ID'),
        'help' => t('The employee id.'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE, // This is use by the table display plugin.
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string',
        ),
        'argument' => array(
            'handler' => 'views_handler_argument_string',
        ),
    );
    $data ['employee']['employee_id'] = array(
        'title' => t('Employee Id'),
        'help' => t('The employee id.'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE, // This is use by the table display plugin.
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string',
        ),
        'argument' => array(
            'handler' => 'views_handler_argument_string',
        ),
    );

    // Example numeric text field.
    $data ['employee']['full_name'] = array(
        'title' => t('Full Name'),
        'help' => t('A full name field.'),
        'field' => array(
            'handler' => 'views_handler_field_employee_capitalize',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data ['employee']['day_of_birth'] = array(
        'title' => t('Day Of Birth'),
        'help' => t('A day of birth field.'),
        'field' => array(
            'handler' => 'views_handler_field_date',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_date',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data ['employee']['gender'] = array(
        'title' => t('Gender'),
        'help' => t('A gender field.'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data ['employee']['created_date'] = array(
        'title' => t('Created Date'),
        'help' => t('A created date field.'),
        'field' => array(
            'handler' => 'views_handler_field_date',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_date',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    return $data;
}

//function employee_views_handlers(){
//    return array(
//        'info' => array(
//            'path' => drupal_get_path('module', 'employee') . '/views/handlers',
//        ),
//        'handlers' => array(
//            'views_handler_field_employee_capitalize' => array(
//                'parent' => 'views_handler_field',
//            ),
//        ),
//    );
//}