<?php
function rest_package_views_plugins() {
    $plugins = array();
    $plugins['query']['rest_package_query'] = array(
        'title' => t('Rest package query'),
        'handler' => 'rest_package_views_plugin_query',
    );
    return $plugins;
}
function rest_package_views_data() {
    $data['rest_package']['table']['group'] = t('Rest Package');
    $data['rest_package']['table']['entity type'] = 'rest_package';
    $data['rest_package']['table']['base'] = array(
        'field' => 'id',
        'title' => t('Rest Package'),
        'help' => t('Rest package help'),
        'query class' => 'rest_package_query',
    );
    $data['rest_package']['id'] =array(
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
    $data['rest_package']['code'] = array(
        'title' => t('Code'),
        'help' => t('The code of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['rest_package']['name'] = array(
        'title' => t('Name'),
        'help' => t('The name of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['rest_package']['amount'] = array(
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

    $data['rest_package']['month'] = array(
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

    $data['rest_package']['telco'] = array(
        'title' => t('Telco'),
        'help' => t('The telco of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['rest_package']['sms_code'] = array(
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

    $data['rest_package']['status'] = array(
        'title' => t('Status'),
        'help' => t('The status of this package'),
        'field' => array(
            'handler' => 'views_handler_field',
            'click sortable' => TRUE,
        ),
        'sort' => array(
            'handler' => 'views_handler_sort',
        ),
    );

    $data['rest_package']['created_at'] = array(
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

    $data['rest_package']['updated_at'] = array(
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