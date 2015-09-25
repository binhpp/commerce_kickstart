<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 24/09/2015
 * Time: 17:24
 */

/**
 * Implement hook_views_data()
 */
function icb_inventory_views_data() {
    $data['icb_inventory']['table']['group'] = t('Icare Inventory New');

    $data['icb_inventory']['table']['base'] = array(
        'field' => 'id',
        'title' => t('Inventory New'),
        'help' => t('The inventory')
    );

    $data['icb_inventory']['id'] = array(
        'title' => t('ID'),
        'help' => t('The unique identifier of inventory'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_in_operator',
            'options callback' => 'icb_inventory_list',
        )
    );

    $data['icb_inventory']['code'] = array(
        'title' => t('Inventory Id'),
        'help' => t('Inventory Id'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
    );

    $data['icb_inventory']['name'] = array(
        'title' => 'Inventory name',
        'help' => 'Inventory name',
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string'
        ),
    );

    $data['icb_inventory']['note'] = array(
        'title' => t('Note'),
        'help' => t('Note'),
        'field' => array(
            'handler' => 'views_handler_field',
        ),
    );

    $data['icb_inventory']['status'] = array(
        'title' => t('Status'),
        'help' => t('Status'),
        'field' => array(
            'handler' => 'icb_inventory_views_field_status',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_in_operator',
            'options callback' => 'icb_inventory_status_options',
        ),
    );

    $data['icb_inventory']['created_by'] = array(
        'title' => t('Created by'),
        'help' => t('User created request'),
        'field' => array(
            'handler' => 'views_handler_field_user',
        ),
        'relationship' => array(
            'title' => t('User created request'),
            'help' => t("Relate this inventory to Users"),
            'handler' => 'views_handler_relationship',
            'base' => 'users',
            'base field' => 'uid',
        ),
    );

    $data['icb_inventory']['created_at'] = array(
        'title' => t('Created time'),
        'help' => t('Created time'),
        'field' => array(
            'handler' => 'views_handler_field_date',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_date',
        ),
    );

    $data['icb_inventory']['updated_by'] = array(
        'title' => t('Update by'),
        'help' => t('User update inventory'),
        'field' => array(
            'handler' => 'views_handler_field_user',
        ),
        'relationship' => array(
            'title' => t('Users'),
            'help' => t("Relate this inventory to Users"),
            'handler' => 'views_handler_relationship',
            'base' => 'users',
            'base field' => 'uid',
        ),
    );

    $data['icb_inventory']['updated_at'] = array(
        'title' => t('Update time'),
        'help' => t('Update time'),
        'field' => array(
            'handler' => 'views_handler_field_date',
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_date',
        ),
    );

    $data['icb_inventory']['data'] = array(
        'title' => t('Data'),
        'help' => t('Data'),
        'field' => array(
            'handler' => 'views_handler_field',
        ),
    );

    $data ['icb_inventory'] ['edit'] = array (
        'title' => t ( 'Edit' ),
        'help' => t ( 'Edit Detail Inventory' ),
        'field' => array (
            'handler' => 'icb_inventory_handler_field_edit_detail'
        )
    );

    return $data;
}