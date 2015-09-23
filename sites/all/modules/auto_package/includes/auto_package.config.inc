<?php
/**
 * Created by PhpStorm.
 * User: root
 * Date: 08/09/2015
 * Time: 14:24
 */
function auto_package_settings_form($form, &$form_state) {
    $form['auto_package_subscription_rest'] = array(
        '#type' => 'textfield',
        '#title' => t ( 'Subscription Rest API' ),
        '#default_value' => variable_get ( 'auto_package_subscription_rest', 'http://localhost:8586/subscription-rest' )
    );
    $form['auto_package_rest'] = array(
        '#type' => 'textfield',
        '#title' => t ( 'Autotopup Rest API' ),
        '#default_value' => variable_get ( 'auto_package_rest', 'http://localhost:8586/autotopup-rest' )
    );
    return system_settings_form($form);
}