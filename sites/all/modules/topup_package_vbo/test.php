<?php
function load($ids = array(), $conditions = array()) {
    $entities = array();
    $revision_id = FALSE;
    $passed_ids = !empty($ids) ? array_flip($ids) : FALSE;

    if ($this->cache && !$revision_id) {
        $entities = $this->cacheGet($ids, $conditions);
        // If any entities were loaded, remove them from the ids still to load.
        if ($passed_ids) {
            $ids = array_keys(array_diff_key($passed_ids, $entities));
        }
    }

    // Support the entitycache module if activated.
    if (!empty($this->entityInfo['entity cache']) && !$revision_id && $ids && !$conditions) {
        $cached_entities = EntityCacheControllerHelper::entityCacheGet($this, $ids, $conditions);
        // If any entities were loaded, remove them from the ids still to load.
        $ids = array_diff($ids, array_keys($cached_entities));
        $entities += $cached_entities;

        // Add loaded entities to the static cache if we are not loading a
        // revision.
        if ($this->cache && !empty($cached_entities) && !$revision_id) {
            $this->cacheSet($cached_entities);
        }
    }

    if (!($this->cacheComplete && $ids === FALSE && !$conditions) && ($ids === FALSE || $ids || $revision_id)) {
        $queried_entities = array();

        $url = 'http://localhost:8181/subscription-rest/package/search';
        $headers = array();



        if (empty($ids)) {
            $options = array(
                'method' => 'POST',
                'data' => '{}',
                'headers' => $headers,
            );
            $respone = drupal_http_request($url, $options);
            if ($respone->code == 200) {
                $result = json_decode($respone->data);
            }
            foreach ($result->list as $row) {
                $queried_entities[$row->id] = $row;
            }
        } else {
            foreach ($ids as $id) {
                $filter = array('id' => $id,);
                $options = array(
                    'method' => 'POST',
                    'data' => !empty($filter) ? json_encode($filter) : '{}',
                    'headers' => $headers,
                );
                $respone = drupal_http_request($url, $options);
                if ($respone->code == 200) {
                    $result = json_decode($respone->data);

                    if (isset($entities[$result->list[0]->{$this->idKey}])) {
                        continue;
                    }

                    foreach ($result->list as $row) {
                        $queried_entities[$row->id] = $row;
                    }
                }
            }
        }

    }

    if (!empty($queried_entities)) {
        $this->attachLoad($queried_entities, $revision_id);
        $entities += $queried_entities;
    }

    // not loading a revision.
    if (!empty($this->entityInfo['entity cache']) && !empty($queried_entities) && !$revision_id) {
        EntityCacheControllerHelper::entityCacheSet($this, $queried_entities);
    }

    if ($this->cache) {
        // Add entities to the cache if we are not loading a revision.
        if (!empty($queried_entities) && !$revision_id) {
            $this->cacheSet($queried_entities);

            // Remember if we have cached all entities now.
            if (!$conditions && $ids === FALSE) {
                $this->cacheComplete = TRUE;
            }
        }
    }

    if ($passed_ids && $passed_ids = array_intersect_key($passed_ids, $entities)) {
        foreach ($passed_ids as $id => $value) {
            $passed_ids[$id] = $entities[$id];
        }
        $entities = $passed_ids;
    }
    return $entities;
}