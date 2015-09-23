<?php
function _rest_provides_get_url($path) {
    return variable_get('rest_provides_url').$path;
}

function _rest_provides_http_client_options() {
    return array(
        'timeout' => variable_get('rest_provides_conn_timeout'),
        'useragent' => 'Drupal MCA provider',
    );
}


function rest_provides_search($filter) {
    if(! isset($filter['pageNumber'])){
        $filter['pageNumber'] = 1;
    }
    if(! isset($filter['pageSize'])){
        $filter['pageSize'] = 20;
    }

    $client = mca_rest_http_post(_rest_provides_get_url('provider.json'), $filter, NULL, _rest_provides_http_client_options());
    $res = mca_rest_http_json_send($client, 1);
    $count = count($res->items);
    for ($i=0; $i<$count; $i++) {
        $res->items[$i] = mca_rest_array2obj($res->items[$i], 0);
        $res->items[$i] = mca_rest_datetime_parse($res->items[$i], 5);
    }
    return $res;
}

function rest_provides_get($id) {
    $filter['meta']['id'] = $id;
    $providers = rest_provides_search($filter);
    if(count($providers->items)>0)
        return $providers->items[0];

    return FALSE;
}