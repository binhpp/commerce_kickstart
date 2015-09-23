<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 23/09/2015
 * Time: 16:21
 */
function file_api_admin_setting($form, &$form_state) {
    $form['saving_file_location'] = array(
        '#type' => 'radios',
        '#title' => 'Saving file location',
        '#description' => 'Choose your saving file location',
        '#options' => drupal_map_assoc(array('local' => 'Local', 'amazons3' => 'Amazon S3')),
        '#default_value' => variable_get('saving_file_location', 'Local'),
    );
    return system_settings_form($form);
}