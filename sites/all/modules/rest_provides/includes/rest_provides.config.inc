<?php
function rest_provides_setting_form($form, &$form_state) {
    $form['rest_provides_url'] = array(
        '#type' => 'textfield',
        '#title' => 'REST URL',
        '#description' => 'URL where provider REST is deployed (including trailing slash)',
        '#required' => TRUE,
        '#default_value' => variable_get('rest_provides_url'),
    );

    $form['rest_provides_conn_timeout'] = array(
        '#type' => 'textfield',
        '#title' => 'Connection Timeout',
        '#description' => 'Timeout in seconds for the connection to the REST service',
        '#required' => TRUE,
        '#default_value' => variable_get('rest_provides_conn_timeout'),
    );

    $form['rest_provides_ajax'] = array(
        '#markup' => '<div id="rest_provides_ajax"></div>',
    );

    $form = system_settings_form($form);

    $form['actions']['test'] = array(
        '#type' => 'button',
        '#value' => 'Test Connection',
        '#ajax' => array(
            'callback' => 'rest_provides_settings_connection_test',
            'wrapper' => 'rest_provides_ajax',
            'method' => 'replace',
        ),
    );

    //views_get_view('');

    return $form;
}

function rest_provides_settings_connection_test($form, $form_state) {
    $error = NULL;
    try {
        $client = mca_rest_http_get($form['rest_provides_url']['#value'].'hello.json', array('name' => 'Drupal Test'));
        $client->send();
        $res = $client->getResponse();
        if ($res->getResponseCode()!=200)
            throw new Exception('Invalid response code: '.$res->getResponseCode());
        $msg = $res->getBody()->toString();
    } catch (Exception $ex) {
        $error = $ex;
    }

    if (empty($error)) {
        $type = 'status';
        $msg = 'Connection tested successfully: '.(empty($msg)?'unknow message':$msg);
    }
    else {
        $type = 'error';
        $msg = empty($error->xdebug_message)?$error->getMessage():$error->xdebug_message;
    }

    return array(
        '#type' => 'container',
        '#attributes' => array('id'=> 'rest_provides_ajax', 'class' => array('messages', $type)),
        'content' => array(
            '#markup' => $msg,
        ),
    );
}