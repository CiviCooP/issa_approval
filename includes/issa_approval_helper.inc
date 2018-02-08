<?php

/**
 * @author Klaas Eikelboom (CiviCooP) <klaas.eikelboom@civicoop.org>
 * @date 1/18/18 9:00 PM
 * @license AGPL-3.0
 */
class issa_approval_helper {

  public static function currentUser() {
    civicrm_initialize();
    $session = CRM_Core_Session::singleton();
    return $session->get('userID');
  }

  static public function commentActivitySQL() {
    $config = issa_approval_config::singleton();
    return "SELECT act.id AS activity_id
          ,      ad.{$config->getApproveDenyCustomFields()['Approve']} approvedeny
          FROM   civicrm_case cas
          JOIN   civicrm_case_contact cc     ON (cc.case_id = cas.id AND cc.contact_id=%1)
          JOIN   civicrm_case_activity cact  ON (cact.case_id = cas.id) 
          JOIN   civicrm_activity      act   ON (act.id = cact.activity_id AND act.is_deleted=0 AND act.activity_type_id = {$config->getApprovalActivityTypeId()} AND act.is_current_revision=1 )
          JOIN   civicrm_activity_contact acc ON (acc.activity_id = act.id and acc.record_type_id=2 and acc.contact_id=%2)         
          JOIN   {$config->getApproveDenyCustomTable()} ad ON (ad.entity_id = act.id)
          where  cas.case_type_id = {$config->getApprovalCaseTypeId()}
         ";
  }

  static public function commentActivity($contactId) {

    return CRM_Core_DAO::singleValueQuery(self::commentActivitySQL(), [
      '1' => [$contactId, 'Integer'],
      '2' => [self::currentUser(), 'Integer'],
    ]);
  }

  static public function colleagues($contactId) {
    $dao = CRM_Core_DAO::executeQuery("
        SELECT c.display_name FROM civicrm_contact c
        JOIN civicrm_relationship rup ON (c.id = rup.contact_id_a AND rup.relationship_type_id=%2)
        JOIN civicrm_relationship rdown ON (rup.contact_id_b = rdown.contact_id_a AND rdown.relationship_type_id=%3)
        WHERE rdown.contact_id_b = %1 AND rup.contact_id_a !=%1
        ORDER BY c.sort_name", [
      1 => [$contactId, 'Integer'],
      2 => [variable_get(ISSA_APPROVAL_EMPLOYEE_TYPE_ID, 5), 'Integer'],
      3 => [variable_get(ISSA_APPROVAL_CONTACTPERSON_TYPE_ID, 5), 'Integer'],
    ]);
    $result = [];
    while ($dao->fetch()) {
      $result[] = $dao->display_name;
    }
    return $result;
  }

  static public function webform_submitted($webform) {
    global $user;
    $query = "SELECT 1 FROM {webform_submissions} WHERE nid=:nid AND uid=:uid AND is_draft=0";
    return db_query($query, [
      ':nid' => variable_get($webform),
      ':uid' => $user->uid,
    ])->rowCount();

  }

  static public function webform_submission_id($webform) {
    global $user;
    $query = "SELECT sid FROM {webform_submissions} WHERE nid=:nid AND uid=:uid LIMIT 1";
    return db_query($query, [
      ':nid' => variable_get($webform),
      ':uid' => $user->uid,
    ])->fetchField();
  }

  static public function webform_link($webform) {
    $nodeurl = 'node/' . variable_get($webform);
    if (issa_approval_helper::webform_submitted($webform)) {
      return $nodeurl . '/submission/' . issa_approval_helper::webform_submission_id($webform) . '/edit';
    }
    else {
      return $nodeurl;
    }
  }

}