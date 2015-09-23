<?php
$views = array();
$view = new view();
$view->name = 'employees_views';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'employees';
$view->human_name = 'employees_views';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'employees_views';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
/* Field: Employees: Employees ID */
$handler->display->display_options['fields']['eid']['id'] = 'eid';
$handler->display->display_options['fields']['eid']['table'] = 'employees';
$handler->display->display_options['fields']['eid']['field'] = 'eid';
$handler->display->display_options['fields']['eid']['exclude'] = TRUE;
/* Field: Employees: Completed */
$handler->display->display_options['fields']['completed']['id'] = 'completed';
$handler->display->display_options['fields']['completed']['table'] = 'employees';
$handler->display->display_options['fields']['completed']['field'] = 'completed';
$handler->display->display_options['fields']['completed']['not'] = 0;
/* Field: Employees: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'employees';
$handler->display->display_options['fields']['title']['field'] = 'title';
/* Field: Employees: Author */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'employees';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
/* Field: Employees: Assignee */
$handler->display->display_options['fields']['company_assignee']['id'] = 'company_assignee';
$handler->display->display_options['fields']['company_assignee']['table'] = 'field_data_company_assignee';
$handler->display->display_options['fields']['company_assignee']['field'] = 'company_assignee';
$handler->display->display_options['fields']['company_assignee']['settings'] = array(
    'link' => 0,
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer employees entities';
$handler->display->display_options['path'] = 'admin/content/employees';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Employees';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

return $views;