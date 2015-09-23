<?php
/**
 * call mca_provider service to get all provider
 */
function rest_provides_get_all_provides() {
    $providers = array();
    $pageNumber = 1;
    $pageSize = 20;

    do {
        $result = rest_provides_search(array(
            'pageNumber' => $pageNumber,
            'pageSize' => $pageSize
        ));
        $providers = array_merge($providers, $result->items);

        $pageNumber++;
    } while(count($result->items) == 20);

    return $providers;
}