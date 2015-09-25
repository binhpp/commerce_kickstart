<?php
/**
 * Created by PhpStorm.
 * User: binh
 * Date: 24/09/2015
 * Time: 15:17
 */

class ICBInventoryController extends EntityAPIController {
    public function save($entity, DatabaseTransaction $transaction = NULL) {
        global $user;
        $is_new = !empty($entity->is_new) || empty($entity->{$this->idKey});

        if($is_new) {
            $entity->created_by = $user->uid;
            $entity->created_at = REQUEST_TIME;
        }
        else {
            $entity->updated_by = $user->uid;
            $entity->updated_at = REQUEST_TIME;
        }
        return parent::save($entity, $transaction);
    }
}