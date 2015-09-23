<?php
class RestPackageController extends EntityAPIController implements EntityAPIControllerInterface{
    public function create(array $values = array())
    {
        $values = array_merge($values, array(
            'id' => 0,
            'code' => '',
            'name' => '',
            'amount' => '',
            'month' => '',
            'telco' => '',
            'status' => '',
            'sms_code' => '',
        ));
        return parent::create($values);
    }
    public function rest_package_generate_data($entity) {
        $row = array();
        if(!empty($entity->id)) {
            $row['id'] = $entity->id;
            $row['name'] = $entity->name;
            $row['code'] = $entity->code;
            $row['sms_code'] = $entity->sms_code;
            $row['amount'] = $entity->amount . '000';
            $row['month'] = $entity->month;
            $row['telco'] = $entity->telco;
            $row['status'] = $entity->status;
        }else {
            $row['name'] = $entity->name;
            $row['code'] = $entity->code;
            $row['sms_code'] = $entity->sms_code;
            $row['amount'] = $entity->amount . '000';
            $row['month'] = $entity->month;
            $row['telco'] = $entity->telco;
            $row['status'] = $entity->status;
        }
        return $row;
    }
    public function save($entity, DatabaseTransaction $transaction = NULL) {
        $url = 'http://localhost:8181/subscription-rest/package/save';
        $data = entity_get_controller('rest_package')->rest_package_generate_data($entity);
        $headers = array();
        $respone_code = '';
        $options = array(
            'method' => 'POST',
            'data' => !empty($data) ? json_encode($data) : '{}',
            'headers' => $headers,
        );
        $respone = drupal_http_request($url, $options);
        if ($respone->code == 200) {
            $respone_code .= 'Create package name : ' . $data['name'] . ' done';
        } else {
            $respone_code .= 'Create package name : ' . $data['name'] . ' failed';
        }
        return $respone_code;
    }
    public function load($ids = array(), $conditions = array()) {
        $entities = array();
        $url = 'http://localhost:8181/subscription-rest/package/search';
        $headers = array();
        if ($ids != FALSE && !$conditions) {
            $queried_entities = array();
                foreach($ids as $id) {
                    $filter = array('id' => $id, );
                    $options = array(
                        'method' => 'POST',
                        'data' => !empty($filter) ? json_encode($filter) : '{}',
                        'headers' => $headers,
                    );
                    $respone = drupal_http_request($url, $options);
                    if ($respone->code == 200) {
                        $result = json_decode($respone->data);
                        foreach ($result->list as $row) {
                            $queried_entities[$row->id] = $row;
                        }
                    }
                }
        }else {
            $options = array(
                'method' => 'POST',
                'data' => '{}',
                'headers' => $headers,
            );
            $respone = drupal_http_request($url, $options);
            if ($respone->code == 200) {
                $result = json_decode($respone->data);
                foreach ($result->list as $row) {
                    $queried_entities[$row->id] = $row;
                }
            }
        }
        if (!empty($queried_entities)) {
            $entities += $queried_entities;
        }
        return $entities;
    }
}