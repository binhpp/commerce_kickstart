<?php
/**
 * Created by PhpStorm.
 * User: root
 * Date: 08/09/2015
 * Time: 14:53
 */
class auto_package_handler_field_operations extends views_handler_field {
    function  init(&$view, &$options) {
        parent::init($view, $options);
        $this->additional_fields['id'] = 'id';
    }
    function render($values) {
        $package_id = $this->get_value($values, 'id');

        // Get the operations links. Child links need to be local-task (with parent menu) & context inline
        $links = menu_contextual_links('auto_package', 'auto/package', array($package_id));

        if (!empty($links)) {
            return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
        }
    }
}