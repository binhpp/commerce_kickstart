<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 29/09/2015
 * Time: 09:58
 */
class topup_package_views_handler_field_name_edit extends views_handler_field {
    function construct() {
        parent::construct();
        $this->additional_fields['id'] = 'id';
        $this->additional_fields['name'] = 'name';
    }
    function query() {
        $this->ensure_my_table();
        $this->add_additional_fields();
    }
    function render($values) {
        return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
    }
    function views_form(&$form, &$form_state){
        $form[$this->options['id']] = array(
            '#type' => 'container',
            '#tree' => TRUE,
        );
        foreach($this->view->result as $row_index => $row) {
            $form[$this->options['id']][$row_index] = array(
                '#type' => 'textfield',
                '#default_value' => $row->{$this->aliases['name']},
//                '#element_validate' => array('topup_package_views_handler_field_name_edit_validate'),
                '#required' => TRUE,
            );
        }
        if($this->view->display_handler->plugin_name != 'page') {
            $form['#action'] = current_path();
        }
    }

    function views_form_submit($form, &$form_state) {
        $updates = array();
        foreach($this->view->result as $row_index => $row) {
            $value = $form_state['values'][$this->options['id']][$row_index];
            if ($row->{$this->aliases['name']} != $value) {
                $updates[$row->{$this->aliases['id']}] = $value;
            }
        }

        $packages = topup_package_load_multiple(array_keys($updates));
        foreach($packages as $key => $package) {
            $package->name = $updates[$key];
            entity_save('topup_package', $package);
        }

        drupal_set_message(t('Update @num topup_package name.', array('@num' => sizeof($updates))));
    }
}