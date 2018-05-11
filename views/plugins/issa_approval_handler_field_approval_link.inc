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

  function option_definition() {
    $options = parent::option_definition();
    $options[ISSA_APPROVAL_WEBFORM_NID] = array('default' => 1);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $query = db_query("SELECT nid, title FROM {node} WHERE type='webform'");
    $webformOptions = [];
    $records = $query->fetchAll();
    foreach ($records as $record) {
      $webformOptions[$record->nid] = $record->title;
    }

    $form['issa_approval'] = array(
      '#type' => 'fieldset',
      '#title' => t('Issa Approval'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 99,
    );

    $form['issa_approval_webform_id'] = array(
      '#type' => 'select',
      '#title' => t('Approval Form'),
      '#options' => $webformOptions,
      '#default_value' => $this->options[ISSA_APPROVAL_WEBFORM_NID],
      '#fieldset' => 'issa_approval',
    );
  }

  function render($values) {
    return issa_approval_helper::approval_link($values->id,$this->options[ISSA_APPROVAL_WEBFORM_NID]);
  }
}