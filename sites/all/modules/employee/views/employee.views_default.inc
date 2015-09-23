<?php
function employee_views_default_views() {
    $view = new view();
    $view->name = 'employee_views_table_2';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'employee';
    $view->human_name = 'Employee Views Table';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'Employee Views Table';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'none';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'full';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['style_plugin'] = 'table';
    $handler->display->display_options['style_options']['columns'] = array(
        'eid' => 'eid',
        'employee_id' => 'employee_id',
        'full_name' => 'full_name',
        'created_date' => 'created_date',
        'day_of_birth' => 'day_of_birth',
        'gender' => 'gender',
        'uid' => 'uid',
    );
    $handler->display->display_options['style_options']['default'] = 'eid';
    $handler->display->display_options['style_options']['info'] = array(
        'eid' => array(
            'sortable' => 1,
            'default_sort_order' => 'asc',
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'employee_id' => array(
            'sortable' => 1,
            'default_sort_order' => 'asc',
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'full_name' => array(
            'sortable' => 1,
            'default_sort_order' => 'asc',
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'created_date' => array(
            'sortable' => 1,
            'default_sort_order' => 'asc',
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'day_of_birth' => array(
            'sortable' => 1,
            'default_sort_order' => 'asc',
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'gender' => array(
            'sortable' => 1,
            'default_sort_order' => 'asc',
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'uid' => array(
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
    );
    /* Field: Employee table: Eid */
    $handler->display->display_options['fields']['eid']['id'] = 'eid';
    $handler->display->display_options['fields']['eid']['table'] = 'employee';
    $handler->display->display_options['fields']['eid']['field'] = 'eid';
    /* Field: Employee table: Employee Id */
    $handler->display->display_options['fields']['employee_id']['id'] = 'employee_id';
    $handler->display->display_options['fields']['employee_id']['table'] = 'employee';
    $handler->display->display_options['fields']['employee_id']['field'] = 'employee_id';
    /* Field: Employee table: Full Name */
    $handler->display->display_options['fields']['full_name']['id'] = 'full_name';
    $handler->display->display_options['fields']['full_name']['table'] = 'employee';
    $handler->display->display_options['fields']['full_name']['field'] = 'full_name';
    $handler->display->display_options['fields']['full_name']['format_capitalize'] = TRUE;
    /* Field: Employee table: Created Date */
    $handler->display->display_options['fields']['created_date']['id'] = 'created_date';
    $handler->display->display_options['fields']['created_date']['table'] = 'employee';
    $handler->display->display_options['fields']['created_date']['field'] = 'created_date';
    $handler->display->display_options['fields']['created_date']['date_format'] = 'long';
    $handler->display->display_options['fields']['created_date']['second_date_format'] = 'long';
    /* Field: Employee table: Day Of Birth */
    $handler->display->display_options['fields']['day_of_birth']['id'] = 'day_of_birth';
    $handler->display->display_options['fields']['day_of_birth']['table'] = 'employee';
    $handler->display->display_options['fields']['day_of_birth']['field'] = 'day_of_birth';
    $handler->display->display_options['fields']['day_of_birth']['date_format'] = 'long';
    $handler->display->display_options['fields']['day_of_birth']['second_date_format'] = 'long';
    /* Field: Employee table: Gender */
    $handler->display->display_options['fields']['gender']['id'] = 'gender';
    $handler->display->display_options['fields']['gender']['table'] = 'employee';
    $handler->display->display_options['fields']['gender']['field'] = 'gender';
    /* Field: Employee table: Author */
    $handler->display->display_options['fields']['uid']['id'] = 'uid';
    $handler->display->display_options['fields']['uid']['table'] = 'employee';
    $handler->display->display_options['fields']['uid']['field'] = 'uid';
    /* Sort criterion: Employee table: Eid */
    $handler->display->display_options['sorts']['eid']['id'] = 'eid';
    $handler->display->display_options['sorts']['eid']['table'] = 'employee';
    $handler->display->display_options['sorts']['eid']['field'] = 'eid';
    $handler->display->display_options['sorts']['eid']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['eid']['expose']['label'] = 'Eid';
    /* Sort criterion: Employee table: Employee Id */
    $handler->display->display_options['sorts']['employee_id']['id'] = 'employee_id';
    $handler->display->display_options['sorts']['employee_id']['table'] = 'employee';
    $handler->display->display_options['sorts']['employee_id']['field'] = 'employee_id';
    $handler->display->display_options['sorts']['employee_id']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['employee_id']['expose']['label'] = 'Employee Id';
    /* Sort criterion: Employee table: Full Name */
    $handler->display->display_options['sorts']['full_name']['id'] = 'full_name';
    $handler->display->display_options['sorts']['full_name']['table'] = 'employee';
    $handler->display->display_options['sorts']['full_name']['field'] = 'full_name';
    $handler->display->display_options['sorts']['full_name']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['full_name']['expose']['label'] = 'Full Name';
    /* Sort criterion: Employee table: Created Date */
    $handler->display->display_options['sorts']['created_date']['id'] = 'created_date';
    $handler->display->display_options['sorts']['created_date']['table'] = 'employee';
    $handler->display->display_options['sorts']['created_date']['field'] = 'created_date';
    $handler->display->display_options['sorts']['created_date']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['created_date']['expose']['label'] = 'Created Date';
    /* Sort criterion: Employee table: Day Of Birth */
    $handler->display->display_options['sorts']['day_of_birth']['id'] = 'day_of_birth';
    $handler->display->display_options['sorts']['day_of_birth']['table'] = 'employee';
    $handler->display->display_options['sorts']['day_of_birth']['field'] = 'day_of_birth';
    $handler->display->display_options['sorts']['day_of_birth']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['day_of_birth']['expose']['label'] = 'Day Of Birth';
    /* Sort criterion: Employee table: Gender */
    $handler->display->display_options['sorts']['gender']['id'] = 'gender';
    $handler->display->display_options['sorts']['gender']['table'] = 'employee';
    $handler->display->display_options['sorts']['gender']['field'] = 'gender';
    $handler->display->display_options['sorts']['gender']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['gender']['expose']['label'] = 'Gender';
    /* Contextual filter: Employee table: Author */
    $handler->display->display_options['arguments']['uid']['id'] = 'uid';
    $handler->display->display_options['arguments']['uid']['table'] = 'employee';
    $handler->display->display_options['arguments']['uid']['field'] = 'uid';
    $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
    $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
    $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
    /* Filter criterion: Employee table: Author */
    $handler->display->display_options['filters']['uid']['id'] = 'uid';
    $handler->display->display_options['filters']['uid']['table'] = 'employee';
    $handler->display->display_options['filters']['uid']['field'] = 'uid';
    $handler->display->display_options['filters']['uid']['value'] = '';
    $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
    $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
    $handler->display->display_options['filters']['uid']['expose']['label'] = 'Author';
    $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
    $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
    $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
        2 => '2',
        1 => 0,
        4 => 0,
        3 => 0,
    );
    /* Filter criterion: Employee table: Created Date */
    $handler->display->display_options['filters']['created_date']['id'] = 'created_date';
    $handler->display->display_options['filters']['created_date']['table'] = 'employee';
    $handler->display->display_options['filters']['created_date']['field'] = 'created_date';
    $handler->display->display_options['filters']['created_date']['operator'] = '<';
    $handler->display->display_options['filters']['created_date']['exposed'] = TRUE;
    $handler->display->display_options['filters']['created_date']['expose']['operator_id'] = 'created_date_op';
    $handler->display->display_options['filters']['created_date']['expose']['label'] = 'Created Date';
    $handler->display->display_options['filters']['created_date']['expose']['operator'] = 'created_date_op';
    $handler->display->display_options['filters']['created_date']['expose']['identifier'] = 'created_date';
    $handler->display->display_options['filters']['created_date']['expose']['remember_roles'] = array(
        2 => '2',
        1 => 0,
        4 => 0,
        3 => 0,
    );
    /* Filter criterion: Employee table: Employee Id */
    $handler->display->display_options['filters']['employee_id']['id'] = 'employee_id';
    $handler->display->display_options['filters']['employee_id']['table'] = 'employee';
    $handler->display->display_options['filters']['employee_id']['field'] = 'employee_id';
    $handler->display->display_options['filters']['employee_id']['exposed'] = TRUE;
    $handler->display->display_options['filters']['employee_id']['expose']['operator_id'] = 'employee_id_op';
    $handler->display->display_options['filters']['employee_id']['expose']['label'] = 'Employee Id';
    $handler->display->display_options['filters']['employee_id']['expose']['operator'] = 'employee_id_op';
    $handler->display->display_options['filters']['employee_id']['expose']['identifier'] = 'employee_id';
    $handler->display->display_options['filters']['employee_id']['expose']['remember_roles'] = array(
        2 => '2',
        1 => 0,
        4 => 0,
        3 => 0,
    );

    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page');
    $handler->display->display_options['path'] = 'employee-views-table';
    $handler->display->display_options['menu']['title'] = 'Views Employee';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'main-menu';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;

    /* Display: Page 1: Employee */
    $handler = $view->new_display('page', 'Page 1: Employee', 'page_2');
    $handler->display->display_options['path'] = 'user/%/employee';
    $handler->display->display_options['menu']['type'] = 'tab';
    $handler->display->display_options['menu']['title'] = 'Employee';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['name'] = 'user-menu';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;
    $translatables['employee_views_table_2'] = array(
        t('Master'),
        t('Employee Views Table'),
        t('more'),
        t('Apply'),
        t('Reset'),
        t('Sort by'),
        t('Asc'),
        t('Desc'),
        t('Items per page'),
        t('- All -'),
        t('Offset'),
        t('« first'),
        t('‹ previous'),
        t('next ›'),
        t('last »'),
        t('Eid'),
        t('.'),
        t(','),
        t('Employee Id'),
        t('Full Name'),
        t('Created Date'),
        t('Day Of Birth'),
        t('Gender'),
        t('Author'),
        t('All'),
        t('Page'),
        t('Page 1: Employee'),
    );
    $views['employee_views_table_2'] = $view;
    return $views;
}