<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 24/09/2015
 * Time: 16:28
 */

function icb_inventory_form($form, &$form_state, $entity) {
    $form_state['inventory'] = $entity;
    field_attach_form('icb_inventory', $entity, $form, $form_state);
    $form['code'] = array(
        '#type' => 'textfield',
        '#title' => t('Inventory Code'),
        '#required' => TRUE,
        '#size' => 30,
        '#default_value' => !empty($entity->code) ? $entity->code : '',
    );
    $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Inventory Name'),
        '#required' => TRUE,
        '#size' => 30,
        '#default_value' => !empty($entity->name) ? $entity->name : '',
    );
    $form['note'] = array(
        '#type' => 'textarea',
        '#rows' => 10,
        '#title' => t('Inventory Note'),
        '#default_value' => !empty($entity->note) ? $entity->note : '',
    );
    $form['status'] = array(
        '#type' => 'select',
        '#title' => t('Status'),
        '#options' => icb_inventory_status_options(),
        '#default_value' => !empty($entity->status) ? $entity->status : '',
    );
    $form['actions'] = array(
        '#type' => 'actions',
        'submit' => array(
            '#type' => 'submit',
            '#value' => t('Submit'),
        ),
        'cancel' => array(
            '#type' => 'markup',
            '#markup' => l(t('Cancel'), 'icb-inventory'),
        ),
    );
    return $form;
}
function icb_inventory_form_submit($form, &$form_state) {
    $entity = $form_state['inventory'];
    $entity->code = $form_state['values']['code'];
    $entity->name = $form_state['values']['name'];
    $entity->note = $form_state['values']['note'];
    $entity->status = $form_state['values']['status'];
    field_attach_submit('icb_inventory', $entity, $form, $form_state);
    try {
        icb_inventory_save($entity);
        $msg = empty($entity->is_new) ? t('Inventory has been created successfully.') : t('Inventory data has been updated successfully.');
        drupal_set_message($msg);
        $form_state['redirect'] = 'icb-inventory';
    } catch(Exception $e) {
        watchdog_exception('icb_inventory',$e);
        drupal_set_message($e,'error');
    }
}