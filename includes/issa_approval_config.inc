<?php

/**
 * Handles all configuration specific tasks. Used the singleton
 * pattern for efficient caching.
 *
 * @author Klaas Eikelboom (CiviCooP)
 * @date 19 Jan 2018
 * @license AGPL-3.0
 */
class issa_approval_config {

  static private $_singleton = NULL;

  private $_approveDenyCustomFields = [];

  private $_approveDenyCustomTable = NULL;

  private $_approvalActivityTypeId = NULL;

  private $_approvalCaseTypeId = NULL;

  public function __construct() {
    civicrm_initialize();
    $this->setUpApproveDeny();
    $this->setUpTypeIds();
  }

  private function setUpApproveDeny() {
    try {
      $approveDenyCustomGroup = civicrm_api3('CustomGroup', 'getsingle', [
        'name' => 'Approval',
        'extends' => 'Activity',
      ]);
      $this->_approveDenyCustomTable = $approveDenyCustomGroup['table_name'];
    } catch (CiviCRM_API3_Exception $ex) {
      throw new Exception('Could not find a custom group with name [Approval] in ' . __METHOD__ . ', is required for Ilga Approval Processing. Contact your system administrator, 
        error from API CustomGroup getsingle: ' . $ex->getMessage());
    };
    // now get possible custom fields in the group
    try {
      $customFields = civicrm_api3('CustomField', 'get', [
        'custom_group_id' => $approveDenyCustomGroup['id'],
      ]);
      foreach ($customFields['values'] as $field) {
        $this->_approveDenyCustomFields [$field['name']] = $field['column_name'];
      }
    } catch (CiviCRM_API3_Exception $ex) {
    }
  }

  private function setUpTypeIds() {
    try {
      $this->_approvalCaseTypeId = civicrm_api3('CaseType', 'getvalue', [
        'name' => "member_application",
        'return' => 'id',
      ]);
    } catch (CiviCRM_API3_Exception $ex) {
      drupal_set_message(t('Case type member_application not configured'), 'error');
    }
    try {
      $this->_approvalActivityTypeId = civicrm_api3('OptionValue', 'getvalue', [
        'option_group_id' => "activity_type",
        'name' => "approve",
        'return' => 'value',
      ]);
    } catch (CiviCRM_API3_Exception $ex) {
      drupal_set_message(t('Activity Type Approve not configured'), 'error');
    }
  }

  /**
   * @return array
   */
  public function getApproveDenyCustomFields() {
    return $this->_approveDenyCustomFields;
  }

  /**
   * @return null
   */
  public function getApproveDenyCustomTable() {
    return $this->_approveDenyCustomTable;
  }

  /**
   * @return null
   */
  public function getApprovalActivityTypeId() {
    return $this->_approvalActivityTypeId;
  }

  /**
   * @return null
   */
  public function getApprovalCaseTypeId() {
    return $this->_approvalCaseTypeId;
  }

  /**
   * Method to return singleton object
   *
   * @return object $_singleton
   * @access public
   * @static
   */
  public static function &singleton() {
    if (self::$_singleton === NULL) {
      self::$_singleton = new issa_approval_config();
    }
    return self::$_singleton;
  }
}