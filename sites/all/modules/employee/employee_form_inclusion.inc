<?php
function employee_list_uid2() {
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'employee')
        ->propertyCondition('uid', 2)
        ->propertyCondition('created_date',strtotime(date("Y-m-1", strtotime("this month") )),'>=')
        ->propertyCondition('created_date',strtotime(date("Y-m-t", strtotime("this month") )),'<=');

    $result = $query->execute();
    $emp = entity_load('employee', array_keys($result['employee']));
    $variables = array(
        'url' => 'http://localhost/drupal/employee/list/uid2',
        'text' => 'List Employees in this month',
        'item' => $emp
    );
    return theme('employee_template_full', $variables) ;
}
function employee_entity_property_info_alter(&$info) {
    // Add meta-data about the basic node properties.
    $properties = &$info['employee']['properties'];

    $properties['eid'] = array(
        'label' => t("Automatic Employee ID"),
        'type' => 'integer',
        'description' => t("The unique ID of the employee."),
        'schema field' => 'eid',
    );

    $properties['employee_id'] = array(
        'label' => t("Employee ID"),
        'type' => 'text',
        'description' => t("The Employee ID"),
        'schema field' => 'employee_id',
    );

    $properties['full_name'] = array(
        'label' => t("Employee Full Name"),
        'type' => 'text',
        'description' => t("The employee full name."),
        'schema field' => 'full_name',
    );

    $properties['day_of_birth'] = array(
        'label' => t("Employee Birthday"),
        'type' => 'integer',
        'description' => t("The employee birthday."),
        'schema field' => 'day_of_birth',
    );

    $properties['gender'] = array(
        'label' => t("Gender"),
        'type' => 'integer',
        'description' => t("The employee's gender."),
        'schema field' => 'gender',
    );

    $properties['created_date'] = array(
        'label' => t("Created date"),
        'type' => 'integer',
        'description' => t("The employee's created date."),
        'schema field' => 'created_date',
    );

    $properties['uid'] = array(
        'label' => t("User Created"),
        'type' => 'user',
        'description' => t("The author creates this employee."),
        'setter callback' => 'entity_property_verbatim_set',
        'schema field' => 'uid',
    );
}

function employee_list_entities($bundle) {
    $content = array();
    // Load all of our entities.
    $entities = employee_load_multiple(FALSE,array('company' => $bundle));
    if (!empty($entities)) {
        foreach ($entities as $entity) {
            // Create tabular rows for our entities.
            $rows[] = array(
                'data' => array(
                    'id' => $entity->eid,
                    'full_name' => l($entity->full_name, 'employee/' . $entity->eid),
                    'bundle' => $entity->company,
                ),
            );
        }
        // Put our entities into a themed table. See theme_table() for details.
        $content['entity_table'] = array(
            '#theme' => 'table',
            '#rows' => $rows,
            '#header' => array(t('ID'), t('Full'), t('Company')),
        );
    }
    else {
        // There were no entities. Tell the user.
        $content[] = array(
            '#type' => 'item',
            '#markup' => t('No employee entities currently exist.'),
        );
    }
    return $content;
}
function employee_list() {
    $content = array();
    // Load all of our entities.
    $entities = employee_load_multiple();
    if (!empty($entities)) {
        foreach ($entities as $entity) {
            // Create tabular rows for our entities.
            $rows[] = array(
                'data' => array(
                    'id' => $entity->eid,
                    'full_name' => l($entity->full_name, 'employee/' . $entity->eid),
                    'bundle' => $entity->company,
                ),
            );
        }
        // Put our entities into a themed table. See theme_table() for details.
        $content['entity_table'] = array(
            '#theme' => 'table',
            '#rows' => $rows,
            '#header' => array(t('ID'), t('Full'), t('Company')),
        );
    }
    else {
        // There were no entities. Tell the user.
        $content[] = array(
            '#type' => 'item',
            '#markup' => t('No employee entities currently exist.'),
        );
    }
    return $content;
}

function employee_form($form, &$form_state, $entity) {
    $form['description'] = array(
        '#type' => 'item',
        '#title' => t('A form for an employee to register themself'),
    );
    $form['basic_entity'] = array(
        '#type' => 'value',
        '#value' => $entity,
    );

    $form['person_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('Personal Information'),
    );
    $max_num = variable_get('employee_max', 30);
    $required_info = variable_get('required_info', 0) ;
    $form['person_info']['full_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Full name'),
        '#description' => t("Your full name's here"),
        '#size' => 25,
        '#maxlength' => $max_num,
        '#required' => $required_info==0 ? TRUE : FALSE,
        '#default_value' => $entity->full_name,
    );
    $form['person_info']['employee_id'] = array(
        '#type' => 'textfield',
        '#title' => t('Employee ID'),
        '#description' => t("Your employee id's here"),
        '#size' => '25',
        '#maxlength' => 11,
        '#default_value' => $entity->employee_id,
    );
    $form ['person_info']['day_of_birth']   =   array(
        '#title'            =>  t('Day of birth'),
        '#description' => t("Your birthday information's here"),
        '#type'             =>  'date_popup', //use module date_popup
        '#date_format'      =>   "Y-m-d",
        '#attributes'       =>  array('placeholder' =>  t('Day of birth')),
        '#default_value' => $entity->day_of_birth,
    );

    $form ['person_info']['gender'] = array(
        '#type' => 'radios',
        '#title' => t('Gender'),
        '#description' => t("Your gender's here"),
        '#options' => array(
            t('Male'),
            t('Female'),
        ),
        '#default_value' => $entity->gender,
    );

    field_attach_form('employee', $entity, $form, $form_state);

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#weight' => 100,
    );

    $form['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete'),
        '#submit' => array('employee_edit_delete'),
        '#weight' => 200,
    );
    return $form;
}
function employee_administration_form () {

    $form['employee_max'] = array(
        '#type' => 'textfield',
        '#title' => t('Maximum number of characters for employee name'),
        '#default_value' => variable_get('employee_max', 30),
        '#size' => 2,
        '#maxlength' => 2,
        '#description' => t('The maximum number of characters of employee name field.'),
        '#required' => TRUE,
    );

    $form ['required_info'] = array(
        '#type' => 'radios',
        '#title' => t('Required'),
        '#description' => t("Set your employee full name state to be required"),
        '#options' => array(
            t('Required'),
            t('Not required'),
        ),
        '#default_value' => 0,
    );
    return system_settings_form($form);
}
function employee_add($bundle = '' ) {
    $entity = entity_get_controller('employee')->create(array('company' => $bundle));
    return drupal_get_form('employee_form',$entity);
}
function employee_form_submit($form, &$form_state) {
    $entity = $form_state['values']['basic_entity'];
    $entity->full_name = $form_state['values']['full_name'];
    $entity->employee_id = $form_state['values']['employee_id'] ;
    $entity->day_of_birth = strtotime($form_state['values']['day_of_birth']);
    $entity->gender = $form_state['values']['gender'];
    field_attach_submit('employee', $entity, $form, $form_state);
    employee_save($entity);
    $form_state['redirect'] = 'employee/' . $entity->eid;
}
function employee_form_validate($form, &$form_state) {
    field_attach_form_validate('employee', $form_state['values']['basic_entity'], $form, $form_state);
}
function employee_save(&$entity) {
    try {
        entity_save('employee', $entity);
        watchdog('employee',
            'Adding employee successfully'
        );
    } catch (Exception $e) {
        watchdog_exception('employee',$e,'Failed to save employee into the database.');
    }
}

function employee_edit_delete($form, &$form_state) {
    $entity = $form_state['values']['basic_entity'];
    employee_delete($entity);
    drupal_set_message(t('The entity %full_name (ID %id) has been deleted',
            array('%full_name' => $entity->full_name, '%id' => $entity->eid))
    );
}
function employee_delete($entity) {
    entity_delete('employee', entity_id('employee' ,$entity));
    watchdog('employee',
        'Deleting employee successfully'
    );
}


function employee_all() {
    $query = new EntityFieldQuery();
    $query
        ->entityCondition('entity_type','employee')
        ->propertyCondition('uid',2)
        ->propertyCondition('created_date',strtotime(date("Y-m-1", strtotime("0 month") )),'>=')
        ->propertyCondition('created_date',strtotime(date("Y-m-t", strtotime("0 month") )),'<=');

    $result = $query->execute() ;
    $emp = entity_load('employee', array_keys($result['employee']));
    $variables = array(
        'url' => 'http://binh.com/',
        'text' => 'A demonstration about employees',
        'item' => $emp
    );
    return theme('employee_template_full', $variables);
}
/**
 * list all employee created by the current logged-in user using contextual filter.
 */
function employee_current_user_view() {
//    if(property_exists($GLOBALS['user'],'login')){//Set user login
//        return views_embed_view('employee_views_table_2', 'default', $GLOBALS['user']->uid);
//    } else {
//        return drupal_not_found();
//    }
    global $user;
    return views_embed_view('employee_views_table_2', 'default', $user->uid);
}
//function employee_current_user_view() {
//    // load the view
//    $view = views_get_view('employee_views_table_2');
//// set active display on the view
//    $view->set_display($display_id = 'default');
//// set any needed arguments
//    $view->set_arguments(array(arg(0),arg(1)));
//// execute the view
//    $view->execute();
//// display the results
//    print $view->render();
//}