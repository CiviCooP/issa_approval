<?php
/**
 * @author Klaas Eikelboom (CiviCooP) <klaas.eikelboom@civicoop.org>
 * @date 1/18/18 9:19 PM
 * @license AGPL-3.0
 */

class issa_approval_handler_field_approval_link extends views_handler_field {

  function construct() {
    parent::construct();
  }

  function query() {
    // do nothing -- to override the parent query.
  }


  function render($values) {
    $query = [
      'cid2' => issa_approval_helper::currentUser(),
      'cid1' => $values->civicrm_case_contact_contact_id,
    ];
    $result = issa_approval_helper::commentActivity($values->civicrm_case_contact_contact_id);
    if ($result) {
      $query['activity1'] = $result;
    }
    return l('Approve', 'node/' . variable_get('issa_approval_webform_nid'), [
        "query" => $query,
      ]
    );
  }
}