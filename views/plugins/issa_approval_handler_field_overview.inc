<?php
/**
 * @author Klaas Eikelboom (CiviCooP) <klaas.eikelboom@civicoop.org>
 * @date 1/18/18 9:12 PM
 * @license AGPL-3.0
 */

class issa_approval_handler_field_overview extends views_handler_field {

  function construct() {
    parent::construct();
  }

  function query() {
    // do nothing -- to override the parent query.
  }

  function render($values) {
    if(isset($values->civicrm_relationship_civicrm_contact__civicrm_case_id)){
      return l('Overview','link/' . $values-> civicrm_relationship_civicrm_contact__civicrm_case_id .
                          '/' . $values -> civicrm_contact_civicrm_relationship_1_id .
                          '/ '. $values -> civicrm_contact_civicrm_relationship_id);
    } else {
      return '--';
    };
  }

}