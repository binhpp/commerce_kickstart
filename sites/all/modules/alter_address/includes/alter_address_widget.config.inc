<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 14/09/2015
 * Time: 11:26
 */

function alter_address_widget($form, &$form_state) {
    $form['alter_postal_address_widget'] = array(
        '#type' => 'textarea',
        '#title' => t('List City'),
        '#description' => t('City format: [City name]'),
        '#default_value' => variable_get('alter_postal_address_widget', array()),
        '#required' => TRUE
    );

    return system_settings_form($form);
}
