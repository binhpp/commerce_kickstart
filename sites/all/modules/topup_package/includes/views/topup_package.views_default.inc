<?php
function topup_package_views_default_views() {
    $view = new view();
    $view->name = 'topup_package';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'topup_package';
    $view->human_name = 'Topup Package';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'Topup Package';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'none';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'full';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['style_plugin'] = 'table';
    $handler->display->display_options['style_options']['columns'] = array(
        'id' => 'id',
    );
    $handler->display->display_options['style_options']['default'] = 'id';
    $handler->display->display_options['style_options']['info'] = array(
        'id' => array(
            'sortable' => 1,
            'default_sort_order' => 'asc',
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
    );
    /* Field: Topup Backage: ID */
    $handler->display->display_options['fields']['id']['id'] = 'id';
    $handler->display->display_options['fields']['id']['table'] = 'topup_package';
    $handler->display->display_options['fields']['id']['field'] = 'id';
    /* Field: Topup Backage: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'topup_package';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    /* Field: Topup Backage: Code */
    $handler->display->display_options['fields']['code']['id'] = 'code';
    $handler->display->display_options['fields']['code']['table'] = 'topup_package';
    $handler->display->display_options['fields']['code']['field'] = 'code';
    /* Field: Topup Backage: Amount */
    $handler->display->display_options['fields']['amount']['id'] = 'amount';
    $handler->display->display_options['fields']['amount']['table'] = 'topup_package';
    $handler->display->display_options['fields']['amount']['field'] = 'amount';
    /* Field: Topup Backage: Month */
    $handler->display->display_options['fields']['month']['id'] = 'month';
    $handler->display->display_options['fields']['month']['table'] = 'topup_package';
    $handler->display->display_options['fields']['month']['field'] = 'month';
    /* Field: Topup Backage: Sms code */
    $handler->display->display_options['fields']['sms_code']['id'] = 'sms_code';
    $handler->display->display_options['fields']['sms_code']['table'] = 'topup_package';
    $handler->display->display_options['fields']['sms_code']['field'] = 'sms_code';
    /* Field: Topup Backage: Telco */
    $handler->display->display_options['fields']['telco']['id'] = 'telco';
    $handler->display->display_options['fields']['telco']['table'] = 'topup_package';
    $handler->display->display_options['fields']['telco']['field'] = 'telco';
    /* Field: Topup Backage: Status */
    $handler->display->display_options['fields']['status']['id'] = 'status';
    $handler->display->display_options['fields']['status']['table'] = 'topup_package';
    $handler->display->display_options['fields']['status']['field'] = 'status';
    /* Field: Topup Backage: Created at */
    $handler->display->display_options['fields']['created_at']['id'] = 'created_at';
    $handler->display->display_options['fields']['created_at']['table'] = 'topup_package';
    $handler->display->display_options['fields']['created_at']['field'] = 'created_at';
    /* Field: Topup Backage: Updated at */
    $handler->display->display_options['fields']['updated_at']['id'] = 'updated_at';
    $handler->display->display_options['fields']['updated_at']['table'] = 'topup_package';
    $handler->display->display_options['fields']['updated_at']['field'] = 'updated_at';
    /* Sort criterion: Topup Backage: ID */
    $handler->display->display_options['sorts']['id']['id'] = 'id';
    $handler->display->display_options['sorts']['id']['table'] = 'topup_package';
    $handler->display->display_options['sorts']['id']['field'] = 'id';
    $handler->display->display_options['sorts']['id']['exposed'] = TRUE;
    $handler->display->display_options['sorts']['id']['expose']['label'] = 'ID';
    /* Filter criterion: Topup Backage: Telco */
    $handler->display->display_options['filters']['telco']['id'] = 'telco';
    $handler->display->display_options['filters']['telco']['table'] = 'topup_package';
    $handler->display->display_options['filters']['telco']['field'] = 'telco';
    $handler->display->display_options['filters']['telco']['exposed'] = TRUE;
    $handler->display->display_options['filters']['telco']['expose']['operator_id'] = 'telco_op';
    $handler->display->display_options['filters']['telco']['expose']['label'] = 'Telco';
    $handler->display->display_options['filters']['telco']['expose']['operator'] = 'telco_op';
    $handler->display->display_options['filters']['telco']['expose']['identifier'] = 'telco';
    $handler->display->display_options['filters']['telco']['expose']['remember_roles'] = array(
        2 => '2',
        1 => 0,
        4 => 0,
        3 => 0,
    );

    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page');
    $handler->display->display_options['path'] = 'topup-package';
    $translatables['topup_package'] = array(
        t('Master'),
        t('Topup Package'),
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
        t('ID'),
        t('Name'),
        t('Code'),
        t('Amount'),
        t('Month'),
        t('Sms code'),
        t('Telco'),
        t('Status'),
        t('Created at'),
        t('Updated at'),
        t('Page'),
    );
    $views['topup_package'] = $view;
    return $views;
}