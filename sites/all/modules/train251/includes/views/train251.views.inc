<?php
/**
 * Implements hook_views_data().
 */
function train251_views_data()
{
  $data = array();

  //Base table
  $data['subscription_rest_package']['table']['group'] = t('Subscription Rest Package Groups');
  $data['subscription_rest_package']['table']['base'] = array(
    'title' => t('Subscription Rest Package Group'),
    'help' => t('Query Subscription Rest Package Groups.'),
    'query class' => 'subscription_rest_package_plugin_query',
  );

  $data['subscription_rest_package']['id'] = array(
    'title' => t('ID'),
    'help' => t('The id of this package'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_subscription_rest_package_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['subscription_rest_package']['code'] = array(
    'title' => t('Code'),
    'help' => t('The code of this package'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_subscription_rest_package_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['subscription_rest_package']['name'] = array(
    'title' => t('Name'),
    'help' => t('The name of this package'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_subscription_rest_package_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['subscription_rest_package']['amount'] = array(
    'title' => t('Amount'),
    'help' => t('The amount of this package'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_subscription_rest_package_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['subscription_rest_package']['month'] = array(
    'title' => t('Month'),
    'help' => t('The month of this package'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_subscription_rest_package_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['subscription_rest_package']['telco'] = array(
    'title' => t('Telco'),
    'help' => t('The telco of this package'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_subscription_rest_package_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['subscription_rest_package']['sms_code'] = array(
    'title' => t('Sms code'),
    'help' => t('The Sms code of this package'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_subscription_rest_package_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['subscription_rest_package']['status'] = array(
    'title' => t('Status'),
    'help' => t('The status of this package'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_subscription_rest_package_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['subscription_rest_package']['created_at'] = array(
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

  $data['subscription_rest_package']['updated_at'] = array(
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


