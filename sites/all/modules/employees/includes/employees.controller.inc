<?php
class EmployeesController extends EntityAPIController {
    public function create(array $values = array()) {
        global $user;
        $values += array(
            'title' => '',
            'description' => '',
            'completed' => FALSE,
            'created' => REQUEST_TIME,
            'changed' => REQUEST_TIME,
            'uid' => $user->uid,
        );
        return parent::create($values);
    }
    public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
        $wrapper = entity_metadata_wrapper('employees', $entity);
        $content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));

        $content['description'] = array(
            '#theme' => 'field',
            '#weight' => 0,
            '#title' =>t('Description'),
            '#access' => TRUE,
            '#label_display' => 'above',
            '#view_mode' => 'full',
            '#field_name' => 'description',
            '#field_type' => 'text',
            '#language' => LANGUAGE_NONE,
            '#entity_type' => 'employees',
            '#bundle' => $entity->type,
            '#items' => array(array('value' => $entity->description)),
            '#formatter' => 'text_default',
            0 => array('#markup' => check_plain($entity->description))
        );

        if ($entity->completed == 0) {
            $completed = t('No');
        }
        else {
            $completed = t('Yes');
        }
        $content['completed'] = array(
            '#theme' => 'field',
            '#weight' => 0,
            '#title' =>t('Completed'),
            '#access' => TRUE,
            '#label_display' => 'above',
            '#view_mode' => 'full',
            '#field_name' => 'completed',
            '#field_type' => 'text',
            '#language' => LANGUAGE_NONE,
            '#entity_type' => 'employees',
            '#bundle' => $entity->type,
            '#items' => array(array('value' => $completed)),
            '#formatter' => 'text_default',
            0 => array('#markup' => check_plain($completed))
        );


        return parent::buildContent($entity, $view_mode, $langcode, $content);
    }
}
class CompanyTypeController extends EntityAPIControllerExportable {
    public function create(array $values = array()){
        $values += array(
            'label' => '',
            'description' => '',
        );
        return parent::create($values);
    }
    public function save($entity, DatabaseTransaction $transaction = NULL) {
        parent::save($entity, $transaction);
        // Rebuild menu registry. We do not call menu_rebuild directly, but set
        // variable that indicates rebuild in the end.
        // @see http://drupal.org/node/1399618
        variable_set('menu_rebuild_needed', TRUE);
    }
}
class CompanyTypeUIController extends EntityDefaultUIController {
    /**
     * Overrides hook_menu() defaults.
     */
    public function hook_menu() {
        $items = parent::hook_menu();
        $items[$this->path]['description'] = 'Manage Employees types.';
        return $items;
    }
}
class Employees extends Entity {
    protected function defaultLabel() {
        return $this->title;
    }

    protected function defaultUri() {
        return array('path' => 'employees/' . $this->identifier());
    }
}
class CompanyType extends Entity {
    public $type;
    public $label;
    public $weight = 0;

    public function __construct($values = array()) {
        parent::__construct($values, 'company_type');
    }

    function isLocked() {
        return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
    }

    protected function defaultLabel() {
        return $this->type;
    }
}