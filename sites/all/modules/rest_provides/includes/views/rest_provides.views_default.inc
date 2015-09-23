<?php
function rest_provides_views_default_views() {
    $view = new view();
    $view->name = 'rest_provides';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'rest_provides';
    $view->human_name = 'Rest Provides';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'Rest Provides';
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
        'name' => 'name',
        'meta.status' => 'meta.status',
        'username' => 'username',
        'created_at' => 'created_at',
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
        'name' => array(
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'meta.status' => array(
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'username' => array(
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
        'created_at' => array(
            'align' => '',
            'separator' => '',
            'empty_column' => 0,
        ),
    );
    /* Field: Rest Provides: ID */
    $handler->display->display_options['fields']['id']['id'] = 'id';
    $handler->display->display_options['fields']['id']['table'] = 'rest_provides';
    $handler->display->display_options['fields']['id']['field'] = 'id';
    /* Field: Rest Provides: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'rest_provides';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    /* Field: Rest Provides: Status */
    $handler->display->display_options['fields']['meta.status']['id'] = 'meta.status';
    $handler->display->display_options['fields']['meta.status']['table'] = 'rest_provides';
    $handler->display->display_options['fields']['meta.status']['field'] = 'meta.status';
    /* Field: Rest Provides: Username */
    $handler->display->display_options['fields']['username']['id'] = 'username';
    $handler->display->display_options['fields']['username']['table'] = 'rest_provides';
    $handler->display->display_options['fields']['username']['field'] = 'username';
    /* Field: Rest Provides: Created */
    $handler->display->display_options['fields']['created_at']['id'] = 'created_at';
    $handler->display->display_options['fields']['created_at']['table'] = 'rest_provides';
    $handler->display->display_options['fields']['created_at']['field'] = 'created_at';
    $handler->display->display_options['fields']['created_at']['date_format'] = 'long';
    $handler->display->display_options['fields']['created_at']['second_date_format'] = 'long';

    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page');
    $handler->display->display_options['path'] = 'rest-provides';
    $views['rest_provides'] = $view;
    return $views;
}