<?php
function topup_package_views_plugins() {
    $plugins = array();
    $plugins['query']['topup_package_query'] = array(
        'title' => t('Topup Package Query'),
        'handler' => 'topup_package_views_plugin_query'
    );
    return $plugins;
}
/**
 * Implement hook_views_data()
 */
function topup_package_views_data() {
    $data ['topup_package']['table']['group'] = t('Topup Package');
    $data ['topup_package']['table']['entity type'] = 'topup_package';
    $data ['topup_package']['table']['base'] = array(
        'field' => 'id',
        'title' => t('Topup Package'),
        'help' => t('Topup package help'),
        'query class' => 'topup_package_query',
    );

    $data['topup_package']['id'] = array(
        'title' => t('ID'),
        'help' => t('The id of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['topup_package']['code'] = array(
        'title' => t('Code'),
        'help' => t('The code of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['topup_package']['name'] = array(
        'title' => t('Name'),
        'help' => t('The name of this package'),
        'field' => array(
            'handler' => 'topup_package_views_handler_field_name',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['topup_package']['amount'] = array(
        'title' => t('Amount'),
        'help' => t('The amount of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['topup_package']['month'] = array(
        'title' => t('Month'),
        'help' => t('The month of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),

    );

    $data['topup_package']['telco'] = array(
        'title' => t('Telco'),
        'help' => t('The telco of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'views_handler_filter_string',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['topup_package']['sms_code'] = array(
        'title' => t('Sms code'),
        'help' => t('The Sms code of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['topup_package']['status'] = array(
        'title' => t('Status'),
        'help' => t('The status of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'filter' => array(
            'handler' => 'topup_package_views_handler_filter_status',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['topup_package']['created_at'] = array(
        'title' => t('Created at'),
        'help' => t('The created time of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['topup_package']['updated_at'] = array(
        'title' => t('Updated at'),
        'help' => t('The updated time of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    return $data;
}