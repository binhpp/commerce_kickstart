<?php
/**
 * display all package entity
 * @return array
 */
function rest_package_list_entity() {
    $content = array();
    $entities = rest_package_load_multiple();
    if(!empty($entities)){
        foreach($entities as $entity){
            $row[] = array(
                'data' => array(
                    'id' => $entity->id,
                    'code' => $entity->code,
                    'name' => l($entity->name,'rest-package/'.$entity->id),
                    'amount' => $entity->amount,
                    'month' => $entity->month,
                    'telco' => $entity->telco,
                    'status' => $entity->status,
                    'sms_code' => $entity->sms_code,
                    'created_at' => $entity->created_at,
                    'options' => l('edit', 'rest-package/'.$entity->id.'/edit')
                ),
            );
        }
        $content['entity_table'] = array(
            '#theme' => 'table',
            '#rows' => $row,
            '#header' => array(
                t('ID'),
                t('Package Code'),
                t('Package Name'),
                t('Amount'),
                t('Month'),
                t('Telco'),
                t('Status'),
                t('Sms Code'),
                t('Created'),
                t('Options'),
            ),
        );
    }else {
        $content[] = array(
            '#type' => 'item',
            '#markup' => t('No package entities currently exist.'),
        );
    }
    return $content;
}

function rest_package_add() {
    $entity = entity_create('rest_package', array());
    return drupal_get_form('rest_package_form',$entity);
}

function rest_package_form($form, &$form_state, $entity = NULL) {
    $form['field_set'] = array(
        '#type' => 'fieldset',
        '#title' => t('Package Information'),
        '#prefix' => '<div id="field-code-wrapper">',
        '#suffix' => '</div>',
    );
    if (!empty($form_state['values']['amount']) && !empty($form_state['values']['month']) && empty($entity->code)){
        $result = $form_state['values']['amount'].sprintf('%02d',$form_state['values']['month']);
    } else if (!empty($entity->code)){
        $result = $entity->code;
    } else {
        $result = '';
    }
    $form['field_set']['code'] = array(
        '#type' => 'textfield',
        '#title' => 'Code',
        '#size' => 10,
        '#disabled' => TRUE,
        '#required' => TRUE,
        '#value' => $result
    );
    if (!empty($form_state['values']['amount']) && !empty($form_state['values']['month']) && empty($entity->sms_code)) {
        $smscode_value = sprintf('%03d', $form_state['values']['amount']) . sprintf('%02d', $form_state['values']['month']);
    } else if (!empty($entity->sms_code)) {
        $smscode_value = $entity->sms_code;
    } else {
        $smscode_value = '';
    }
    $form['field_set']['sms_code'] = array(
        '#type' => 'textfield',
        '#title' => 'SMS Code',
        '#size' => 10,
        '#disabled' => TRUE,
        '#required' => TRUE,
        '#value' => $smscode_value,
    );

    $form['field_set']['amount'] = array(
        '#type' => 'select',
        '#title' => 'Amount',
        '#description' => 'Select package amount',
        '#requied' => TRUE,
        '#options' => drupal_map_assoc(array('10' => '010', '20' => '020', '30' => '030', '50' => '050', '100' => '100',
            '200' => '200', '500' => '500')),
        '#default_value' => isset($entity->amount) ? $entity->amount : '10',
        '#ajax' => array(
            'wrapper' => 'field-code-wrapper',
            'callback' => 'ajax_auto_options',
            'event' => 'change',
        ),
    );
    $values = array();
    for($i = 1; $i <= 12; $i++) {
        $values[$i] = $i;
    }
    $form['field_set']['month'] = array(
        '#type' => 'select',
        '#title' => 'Month',
        '#description' => 'Select package month',
        '#requied' => TRUE,
        '#options' => drupal_map_assoc($values),
        '#default_value' => isset($entity->month) ? $entity->month : '1','#ajax' => array(
            'wrapper' => 'field-code-wrapper',
            'callback' => 'ajax_auto_options',
            'event' => 'change',
        ),
    );
    if (!empty($form_state['values']['amount']) && !empty($form_state['values']['month']) && empty($entity->name)) {
        $name_value = 'Gói nạp tiền '.(int)$form_state['values']['amount'].'k/' .$form_state['values']['month'].'T';
    } else if(!empty($entity->name)) {
        $name_value = $entity->name;
    }else {
        $name_value = '';
    }
    $form['field_set']['name'] = array(
        '#type' => 'textfield',
        '#title' => 'Name',
        '#description' => 'Enter package name',
        '#size' => 60,
        '#maxlength' => 50,
        '#required' => TRUE,
        '#value' => $name_value,
    );
    $form['field_set']['telco'] = array(
        '#type' => 'radios',
        '#title' => 'Telco',
        '#required' => TRUE,
        '#options' => array (
            'MOBI' => 'Mobifone',
            'VTEL' => 'Viettel',
            'VINA' => 'Vinaphone'
        ),
        '#default_value' => !empty($entity->telco) ? $entity->telco : 'MOBI',
    );

    $form['field_set']['status'] = array(
        '#type' => 'radios',
        '#title' => 'Package Status',
        '#options' => array(
            'enabled' => 'Enable',
            'disabled' => 'Disable',
        ),
        '#default_value' => !empty($entity->status) ? $entity->status : 'enabled',
    );

    $form['basic_entity'] = array(
        '#type' => 'value',
        '#value' => $entity,
    );
    $form['field_set']['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Create',
    );
    return $form;
}

function ajax_auto_options($form, $form_state) {
    return $form['field_set'];
}

function rest_package_form_validate($form, &$form_state) {
    $code = $form_state['values']['code'];
    if(empty($code)){
        form_set_error('code','Please select package amount and package month');
    }
}

function rest_package_form_submit($form, &$form_state) {
    $entity = $form_state['values']['basic_entity'];
    $entity->code = $form_state['values']['code'];
    $entity->sms_code = $form_state['values']['sms_code'];
    $entity->name = $form_state['values']['name'];
    $entity->amount = (int)$form_state['values']['amount'];
    $entity->month = $form_state['values']['month'];
    $entity->telco = $form_state['values']['telco'];
    $entity->status = $form_state['values']['status'];
    $entity->created_at = time();
    $result = entity_save('rest_package', $entity);
    drupal_set_message($result);
}

function rest_package_view($entity, $view_mode = 'full') {
    $entity_type = 'rest_package';

    //Start setting up the content.
    $entity->content = array(
        '#view_mode' => $view_mode,
    );

    field_attach_prepare_view($entity_type, array($entity->id => $entity),
        $view_mode);
    //We call entity_prepare_view() so it can invoke hook_entity_prepare_view()
    //for us.
    entity_prepare_view($entity_type, array($entity->id => $entity));
    //Now field_attach_view() generates the content for the fields.
    $entity->content += field_attach_view($entity_type, $entity, $view_mode);

    //OK, Field API done, now we can set up some of our own data.
    $entity->content['code'] = array(
        '#type' => 'item',
        '#title' => t('Package code'),
        '#markup' => $entity->code,
    );
    $entity->content['name'] = array(
        '#type' => 'item',
        '#title' => t('Package name'),
        '#markup' => $entity->name,
    );
    $entity->content['amount'] = array(
        '#type' => 'item',
        '#title' => t('Package amount'),
        '#markup' => $entity->amount,
    );
    $entity->content['month'] = array(
        '#type' => 'item',
        '#title' => t('Package month'),
        '#markup' => $entity->month,
    );
    $entity->content['telco'] = array(
        '#type' => 'item',
        '#title' => t('Package telco'),
        '#markup' => $entity->telco,
    );
    $entity->content['status'] = array(
        '#type' => 'item',
        '#title' => t('Package status'),
        '#markup' => $entity->status,
    );
    $entity->content['sms_code'] = array(
        '#type' => 'item',
        '#title' => t('Package sms_code'),
        '#markup' => $entity->sms_code,
    );
    $entity->content['created_at'] = array(
        '#type' => 'item',
        '#title' => t('Created'),
        '#markup' => $entity->created_at,
    );

//    $entity->content['uid'] = array(
//        '#type' => 'item',
//        '#title' => t('Creator'),
//        '#markup' => $wrapper->uid->name->value(),
//    );


    // Now to invoke some hooks. We need the language code for
    // hook_entity_view(), so let's get that.
    global $language;
    $langcode = $language->language;
    // And now invoke hook_entity_view().
    module_invoke_all('entity_view', $entity, $entity_type, $view_mode,
        $langcode);
    // Now invoke hook_entity_view_alter().
    drupal_alter(array('rest_package', 'entity_view'),
        $entity->content, $entity_type);

    // And finally return the content.
    return $entity->content;
}
