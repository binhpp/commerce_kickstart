<?php
function company_type_form($form, &$form_state, $company_type, $op = 'edit') {
    if ($op == 'clone') {
        $company_type->label .= ' (cloned)';
        $company_type->type = '';
    }
    $form['label'] = array(
        '#title' => t('Label'),
        '#type' => 'textfield',
        '#default_value' => $company_type->label,
        '#description' => t('The human-readable name of this company type.'),
        '#required' => TRUE,
        '#size' => 30,
    );
    $form['type'] = array(
        '#type' => 'machine_name',
        '#default_value' => isset($company_type->type) ? $company_type->type : '',
        '#maxlength' => 32,
        '#disabled' => $company_type->isLocked() && $op != 'clone',
        '#machine_name' => array(
            'exists' => 'product_types',
            'source' => array('label'),
        ),
        '#description' => t('A unique machine-readable name for this company type. It must only contain lowercase letters, numbers, and underscores.'),
    );
    $form['description'] = array(
        '#type' => 'textarea',
        '#default_value' => isset($company_type->description) ? $company_type->description : '',
        '#description' => t('Description about the company type.'),
    );
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save company type'),
        '#weight' => 40,
    );
    if (!$company_type->isLocked() && $op != 'add' && $op != 'clone') {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete company type'),
            '#weight' => 45,
            '#limit_validation_errors' => array(),
            '#submit' => array('company_type_form_submit_delete')
        );
    }
    return $form;
}
function company_type_form_submit(&$form, &$form_state) {
    $company_type = entity_ui_form_submit_build_entity($form, $form_state);
    company_type_save($company_type);
    $form_state['redirect'] = 'admin/structure/company-types';
}

function company_type_form_submit_delete(&$form, &$form_state) {
    $form_state['redirect'] = 'admin/structure/company-types/' . $form_state['company_type']->type . '/delete';
}
function company_type_form_delete_confirm($form, &$form_state, $company_type) {
    $form_state['company_type'] = $company_type;
    // Always provide entity id in the same form key as in the entity edit form.
    $form['company_type_id'] = array('#type' => 'value', '#value' => entity_id('company_type' ,$company_type));
    return confirm_form($form,
        t('Are you sure you want to delete company type %type ?', array('%type' => entity_label('company_type', $company_type))),
        'company_type/' . entity_id('company_type' ,$company_type),
        t('This action cannot be undone.'),
        t('Delete'),
        t('Cancel')
    );
}
function company_type_form_delete_confirm_submit($form, &$form_state) {
    $company_type = $form_state['company_type'];
    company_type_delete($company_type);

    watchdog('company_type', '@type: deleted %title.', array('@type' => $company_type->type, '%title' => $company_type->label));
    drupal_set_message(t('@type %title has been deleted.', array('@type' => $company_type->type, '%title' => $company_type->label)));

    $form_state['redirect'] = 'admin/structure/company-types';
}
function employees_admin_add_page() {
    $items = array();
    $types = company_types();
    foreach($types as $key => $company_type) {
        $items[] = l(entity_label('company_type', $company_type), 'employees/add/' . $key);
    }
    return array(
        'list' => array(
            '#theme' => 'item_list',
            '#items' => $items,
            '#title' => t('Select company to create.'),
        ),
    );
}
/**
 * Add new employee page callback.
 */
function employees_add($type) {
    $company_type = company_types($type);

    $employees = entity_create('employees', array('type' => $type));
    drupal_set_title(t('Create @name', array('@name' => entity_label('company_type', $company_type))));

    $output = drupal_get_form('employees_form', $employees);

    return $output;
}
function employees_form($form, &$form_state, $employees) {
    $form_state['employees'] = $employees;
    $form['title'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' => t('Name'),
        '#default_value' => $employees->title,
    );

    $form['description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => $employees->description,
    );

    $form['completed'] = array(
        '#type' => 'checkbox',
        '#title' => t('Completed'),
        '#default_value' => $employees->completed,
    );

    $form['uid'] = array(
        '#type' => 'value',
        '#value' => $employees->uid,
    );

    field_attach_form('employees', $employees, $form, $form_state);

    $submit = array();
    if (!empty($form['#submit'])) {
        $submit += $form['#submit'];
    }

    $form['actions'] = array(
        '#weight' => 100,
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save employee'),
        '#submit' => $submit + array('employees_form_submit'),
    );

    // Show Delete button if we edit task.
    $employees_id = entity_id('employees' ,$employees);
    if (!empty($employees_id) && employees_access('edit', $employees)) {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete'),
            '#submit' => array('employees_form_submit_delete'),
        );
    }

    $form['#validate'][] = 'employees_form_validate';

    return $form;
}
function employees_form_submit($form, &$form_state) {
    $employees = $form_state['employees'];
    entity_form_submit_build_entity('employees', $employees, $form, $form_state);
    employees_save($employees);
    $employees_uri = entity_uri('employees', $employees);
    $form_state['redirect'] = $employees_uri['path'];
    drupal_set_message(t('Employees %title saved.', array('%title' => entity_label('employees', $employees))));
}
function employees_form_validate() {

}
function employees_form_submit_delete($form, &$form_state) {
    $destination = array();
    if(isset($_GET['destination'])) {
        $destination = drupal_get_destination();
        unset($_GET['destination']);
    }
    $employees = $form_state['employees'];
    $employees_uri = entity_uri('employees', $employees);
    $form_state['redirect'] = array($employees_uri['path'] . '/delete', array('query' => $destination));
}
function employees_delete_form($form, &$form_state, $employees) {
    $form_state['employees'] = $employees;
    // Always provide entity id in the same form key as in the entity edit form.
    $form['company_type_id'] = array('#type' => 'value', '#value' => entity_id('employees' ,$employees));
    $employees_uri = entity_uri('employees', $employees);
    return confirm_form($form,
        t('Are you sure you want to delete employees %title?', array('%title' => entity_label('employees', $employees))),
        $employees_uri['path'],
        t('This action cannot be undone.'),
        t('Delete'),
        t('Cancel')
    );
}
function employees_delete_form_submit($form, &$form_state) {
    $employees = $form_state['employees'];
    employees_delete($employees);

    drupal_set_message(t('Employee %title deleted.', array('%title' => entity_label('employees', $employees))));

    $form_state['redirect'] = '<front>';
}