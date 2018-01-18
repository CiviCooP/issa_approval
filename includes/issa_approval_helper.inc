<?php
/**
 *  @author Klaas Eikelboom (CiviCooP) <klaas.eikelboom@civicoop.org>
 *  @date 1/18/18 9:00 PM
 *  @license AGPL-3.0
 */
class issa_approval_helper
{
    public static function currentUser(){
        civicrm_initialize();
        $session = CRM_Core_Session::singleton();
        return $session->get('userID');
    }

    static public function commentActivitySQL(){
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

    static public function commentActivity($contactId){

        return CRM_Core_DAO::singleValueQuery( self::commentActivitySQL(),array(
            '1' => array($contactId,'Integer'),
            '2' => array(self::currentUser(),'Integer')
        ));
    }

}