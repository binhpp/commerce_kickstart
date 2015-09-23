<?php
/**
 * Implement hook_views_plugins
 * In provider to define a custom query class of table mca_provider for views UI module
 * @return array
 */
function rest_provides_views_plugins() {
    $plugins = array();
    $plugins['query']['rest_provides_query'] = array(
        'title' => t('Rest Provides Query'),
        'handler' => t('rest_provides_views_plugins_query')
    );
    return $plugins;
}
function rest_provides_views_data() {
    $data['rest_provides']['table']['group'] = t('Rest Provides');
    $data['rest_provides']['table']['base'] = array(
        'field' => 'id',
        'title' => t('Rest Provides'),
        'help' => t('The MCA provides'),
        'weight' => -10,
        'query class' => 'rest_provides_query',
    );
    $data['rest_provides']['id'] = array(
        'title' => t('ID'),
        'help' => t('The numeric id of rest provides'),
        'field' => array(
            'handler' => 'views_handler_field_numeric',
            'click sortable' => TRUE,
        ),
    );
    $data['rest_provides']['name'] = array(
        'title' => t('Name'),
        'help' => t('Provides Name'),
        'field' => array(
            'handler' => 'views_handler_field',
        ),
    );
    $data['rest_provides']['username'] = array(
        'title' => t('Username'),
        'help' => t('Provider Username'),
        'field' => array(
            'handler' => 'views_handler_field',
        ),
    );
    $data['rest_provides']['meta.status'] = array(
        'title' => t('Status'),
        'help' => t('Provider Status'),
        'field' => array(
            'handler' => 'rest_provides_handler_field_meta',
        ),
    );
    $data['rest_provides']['created_at'] = array(
        'title' => t('Created'),
        'help' => t('Time provider was created'),
        'field' => array(
            'handler' => 'mca_rest_views_handler_field_date',
        ),
    );

    $data['rest_provides']['updated_at'] = array(
        'title' => t('Modified'),
        'help' => t('Time of provider\'s last updated'),
        'field' => array(
            'handler' => 'mca_rest_views_handler_field_date',
        ),
    );
    return $data;
}