<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 24/09/2015
 * Time: 17:45
 */

/**
 * Implements hook_views_default_views().
 */
function icb_inventory_views_default_views() {
    $view = new view();
    $view->name = 'icb_inventory_list';
    $view->description = '';
    $view->tag = 'default';
    $view->base_table = 'icb_inventory';
    $view->human_name = 'icb_inventory_list';
    $view->core = 7;
    $view->api_version = '3.0';
    $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

    /* Display: Master */
    $handler = $view->new_display('default', 'Master', 'default');
    $handler->display->display_options['title'] = 'Inventory';
    $handler->display->display_options['use_more_always'] = FALSE;
    $handler->display->display_options['access']['type'] = 'perm';
    $handler->display->display_options['access']['perm'] = 'ic_inventory_view';
    $handler->display->display_options['cache']['type'] = 'none';
    $handler->display->display_options['query']['type'] = 'views_query';
    $handler->display->display_options['exposed_form']['type'] = 'basic';
    $handler->display->display_options['pager']['type'] = 'full';
    $handler->display->display_options['pager']['options']['items_per_page'] = '10';
    $handler->display->display_options['style_plugin'] = 'table';
    /* Field: Icare Inventory New: Inventory Id */
    $handler->display->display_options['fields']['code']['id'] = 'code';
    $handler->display->display_options['fields']['code']['table'] = 'icb_inventory';
    $handler->display->display_options['fields']['code']['field'] = 'code';
    $handler->display->display_options['fields']['code']['label'] = 'code';
    /* Field: Icare Inventory New: Inventory name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'icb_inventory';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['label'] = 'Name';
    /* Field: Icare Inventory New: Note */
    $handler->display->display_options['fields']['note']['id'] = 'note';
    $handler->display->display_options['fields']['note']['table'] = 'icb_inventory';
    $handler->display->display_options['fields']['note']['field'] = 'note';
    /* Field: Icare Inventory New: Status */
    $handler->display->display_options['fields']['status']['id'] = 'status';
    $handler->display->display_options['fields']['status']['table'] = 'icb_inventory';
    $handler->display->display_options['fields']['status']['field'] = 'status';
    $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
    /* Field: Icare Inventory New: Created time */
    $handler->display->display_options['fields']['created_at']['id'] = 'created_at';
    $handler->display->display_options['fields']['created_at']['table'] = 'icb_inventory';
    $handler->display->display_options['fields']['created_at']['field'] = 'created_at';
    $handler->display->display_options['fields']['created_at']['label'] = 'Created';
    $handler->display->display_options['fields']['created_at']['date_format'] = 'short';
    $handler->display->display_options['fields']['created_at']['second_date_format'] = 'long';
    /* Field: Icare Inventory New: Edit */
    $handler->display->display_options['fields']['edit']['id'] = 'edit';
    $handler->display->display_options['fields']['edit']['table'] = 'icb_inventory';
    $handler->display->display_options['fields']['edit']['field'] = 'edit';
    /* Filter criterion: Icare Inventory New: Status */
    $handler->display->display_options['filters']['status']['id'] = 'status';
    $handler->display->display_options['filters']['status']['table'] = 'icb_inventory';
    $handler->display->display_options['filters']['status']['field'] = 'status';
    $handler->display->display_options['filters']['status']['exposed'] = TRUE;
    $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
    $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
    $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
    $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
    $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
        2 => '2',
        1 => 0,
        3 => 0,
    );
    /* Filter criterion: Icare Inventory New: ID */
    $handler->display->display_options['filters']['id']['id'] = 'id';
    $handler->display->display_options['filters']['id']['table'] = 'icb_inventory';
    $handler->display->display_options['filters']['id']['field'] = 'id';
    $handler->display->display_options['filters']['id']['exposed'] = TRUE;
    $handler->display->display_options['filters']['id']['expose']['operator_id'] = 'id_op';
    $handler->display->display_options['filters']['id']['expose']['label'] = 'Name & Code';
    $handler->display->display_options['filters']['id']['expose']['operator'] = 'id_op';
    $handler->display->display_options['filters']['id']['expose']['identifier'] = 'id';
    $handler->display->display_options['filters']['id']['expose']['remember_roles'] = array(
        2 => '2',
        1 => 0,
        3 => 0,
    );

    /* Display: Page */
    $handler = $view->new_display('page', 'Page', 'page');
    $handler->display->display_options['path'] = 'icb-inventory';
    $handler->display->display_options['menu']['type'] = 'normal';
    $handler->display->display_options['menu']['title'] = 'iCare Inventory';
    $handler->display->display_options['menu']['weight'] = '0';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;
    
    $views [$view->name] = $view;
    return $views;
}