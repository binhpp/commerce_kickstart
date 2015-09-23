<?php
/**
 * Created by PhpStorm.
 * User: root
 * Date: 08/09/2015
 * Time: 14:38
 */
/**
 * Implements hook_views_plugins()
 */
function auto_package_views_plugins() {
    $plugins = array();
    $plugins['query']['auto_package_query'] = array(
        'title' => t('Topup Package Query'),
        'handler' => 'auto_package_views_plugin_query',
    );
    return $plugins;
}
/**
 * Implements hook_views_data()
 */
function auto_package_views_data() {
    $data['auto_package']['table']['group'] = t('Auto Package');
    $data['auto_package']['table']['has_meta'] = 1;
    $data['auto_package']['table']['base'] = array(
        'field' => 'id',
        'title' => t('Auto Package'),
        'help' => t('Autopup Package Remote'),
        'query class' => 'auto_package_query',
    );
    $data['auto_package']['id'] = array(
        'title' => t('Package ID'),
        'help' => t('The numeric id of the package.'),
        'field' => array(
            'handler' => 'views_handler_field_numeric'
        )
    );
    $data['auto_package']['code'] = array(
        'title' => t('Package Code'),
        'help' => t('The code of the package.'),
        'field' => array(
            'handler' => 'views_handler_field'
        )
    );
    $data['auto_package']['month'] = array(
        'title' => t('Term'),
        'help' => t('The month of the package.'),
        'field' => array(
            'handler' => 'views_handler_field_numeric'
        )
    );
    $data['auto_package']['amount'] = array(
        'title' => t('Amuont'),
        'help' => t('The amount per month of the package.'),
        'field' => array(
            'handler' => 'views_handler_field_numeric'
        )
    );
    $data['auto_package']['id'] = array(
        'title' => t('Package ID'),
        'help' => t('The numeric id of the package.'),
        'field' => array(
            'handler' => 'views_handler_field_numeric'
        )
    );
    $data['auto_package']['status'] = array(
        'title' => t('Status'),
        'help' => t('The status of the package.'),
        'field' => array(
            'handler' => 'views_handler_field'
        ),
    );
    $data['auto_package']['telco'] = array(
        'title' => t('Telco'),
        'help' => t('The telco of the package.'),
        'field' => array(
            'handler' => 'views_handler_field'
        ),
    );
    $data['auto_package']['name'] = array(
        'title' => t('Package Name'),
        'help' => t('The name of the package.'),
        'field' => array(
            'handler' => 'views_handler_field'
        ),
    );
    $data['auto_package']['operations'] = array(
        'title' => t('Operations'),
        'help' => t('Package Operations'),
        'field' => array(
            'handler' => 'auto_package_handler_field_operations'
        ),
    );
    return $data;
}