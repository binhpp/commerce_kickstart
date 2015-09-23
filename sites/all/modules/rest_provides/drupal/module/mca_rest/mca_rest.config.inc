<?php 

function mca_rest_settings_form($form, &$form_state) {
	
	$connTypes['drupal'] = 'Drupal API';
	
  if (class_exists('http\Client\Request')) {
		$connTypes['pecl_http'] = 'PECL HTTP v2';
	}
	
	$form['mca_rest_conn_type'] = array(
	  '#type' => 'select',
	  '#title' => 'Connection Type',
        '#options' => $connTypes,
	  '#required' => TRUE,
	  '#default_value' => variable_get('mca_rest_conn_type', 'drupal'),
	);
	
	$form = system_settings_form($form);
	
	return $form;
}
