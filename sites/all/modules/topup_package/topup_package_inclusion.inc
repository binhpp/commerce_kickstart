<?php
function topup_package_list() {
    return 'abc';
}

/**
 * Add topup package entity
 */
function topup_package_add() {
    $entity = entity_get_controller('auto_topup_package')->create();
    return drupal_get_form('topup_package_form',$entity);
}
/**
 * Implement hook_form()
 */
function topup_package_form($form, &$form_state, $entity) {
    $form['description'] = array(
        '#type' => 'item',
        '#title' => t('A form for add an topup package entity'),
    );
    $form['basic_entity'] = array(
        '#type' => 'value',
        '#value' => $entity,
    );
    $form['topup_package_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Topup Package Information'),
    );
    $form['topup_package_info']['code'] = array(
        '#type' => 'textfield',
        '#title' => t('Package Code'),
        '#description' => t("Package code information"),
        '#size' => 25,
        '#maxlength' => 5,
        '#default_value' => $entity->full_name,
    );
    return $form;
}