<?php
function ajax_user_autocomplete($form, &$form_state) {
    $form['info'] = array(
        '#markup' => '<div>' . t("This example does a simplest possible autocomplete by username. You'll need a few users on your system for it to make sense.") . '</div>'
    );
    $form['user'] = array(
        '#type' => 'textfield',
        '#title' =>t('Choose a user (or a people, depending on your usage preferrence'),
        '#autocomplete_path' => 'ajax-user/auto_complete_callback',
        '#ajax' => array(
            'callback' => 'ajax_user_node_callback',
            'wrapper' => 'autocomplete-by-node-ajax-replace',
        ),
    );
    $form['node'] = array(
        '#type' => 'textfield',
        '#title' => t('Choose a node by title'),
        '#prefix' => '<div id="autocomplete-by-node-ajax-replace">',
        '#suffix' => '</div>',
        '#disabled' => TRUE,
    );
    if(!empty($form_state['values']['user'])) {
        $author = user_load_by_name($form_state['values']['user']);
        if(!empty($author)) {
            $auto_complete_path = 'ajax-user/auto_node_complete/' . $author->uid;
            $form['node']['#autocomplete_path'] = $auto_complete_path;
            $form['node']['#title'] = t('Choose a node title authored by %author', array('%author' => $author->name));
            $form['node']['#disabled'] = FALSE;
        }
    }
    $form['actions'] = array(
        '#type' => 'actions',
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
    );
    return $form;
}
function ajax_user_autocomplete_callback($string = "") {
    $matches = array();
    if($string) {
        $result = db_select('users')
            ->fields('users', array('name', 'uid'))
            ->condition('name', db_like($string) . '%', 'LIKE')
            ->range(0, 10)
            ->execute();
        foreach ($result as $user) {
            $matches[$user->name] = check_plain($user->name) . "(uid = $user->uid)";
        }
    }
    drupal_json_output($matches);
}
function ajax_user_node_callback($form, $form_state) {
    return $form['node'];
}
function ajax_node_autocomplete_callback($author_uid, $string = "") {
    $matches = array();
    if ($author_uid > 0 && trim($string)) {
        $result = db_select('node')
            ->fields('node', array('nid', 'title'))
            ->condition('uid', $author_uid)
            ->condition('title', db_like($string) . '%', 'LIKE')
            ->range(0, 10)
            ->execute();
        foreach ($result as $node) {
            $matches[$node->title . " [$node->nid]"] = check_plain($node->title);
        }
    }

    drupal_json_output($matches);
}