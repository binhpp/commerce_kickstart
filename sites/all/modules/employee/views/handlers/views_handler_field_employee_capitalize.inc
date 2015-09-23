<?php
class views_handler_field_employee_capitalize extends views_handler_field {
    function option_definition() {
        $options = parent::option_definition();
        $options['format_capitalize'] = array('default' => FALSE, 'bool' => TRUE);
        return $options;
    }

    function options_form(&$form, &$form_state) {

        $form['format_capitalize'] = array(
            '#type' => 'checkbox',
            '#title' => t('Format capital'),
            '#description' => t('If checked, the text will be capitalized.'),
            '#default_value' => $this->options['format_capital'],
        );
        parent::options_form($form, $form_state);
    }

    function render($values) {
        $value = $this->get_value($values);
        // Should we format as a plural.
        if (!empty($this->options['format_capitalize'])) {
            $value = strtoupper($value);
        }
        return $this->sanitize_value($value);
    }
}