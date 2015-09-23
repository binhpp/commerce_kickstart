<?php
function change_installment_payment() {
    $form['change_installment_payment'] = array(
        '#type' => 'textfield',
        '#title' => t('Format price'),
        '#description' => t('Format product price'),
        '#default_value' => variable_get('change_installment_payment'),
        '#required' => TRUE
    );

    return system_settings_form($form);
}