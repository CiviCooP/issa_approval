<?php
/**
 * @author Klaas Eikelboom (CiviCooP) <klaas.eikelboom@civicoop.org>
 * @date 1/18/18 9:06 PM
 * @license AGPL-3.0
 */

function issa_approval_views_data() {
  $data['issa_approval']['table']['group'] = t('ISSA Approval');
  $data['issa_approval']['table']['join'] = [
    // #global is a special flag which let's a table appear all the time.
    '#global' => [],
  ];
  $data['issa_approval']['overview'] = [
    'title' => t('Overview'),
    'help' => t('Overview for the board'),
    'field' => [
      'handler' => 'issa_approval_handler_field_overview',
      'click sortable' => FALSE,
    ],
  ];
  $data['issa_approval']['approval_link'] = [
    'title' => t('Approval'),
    'help' => t('Link for finding the approval form'),
    'field' => [
      'handler' => 'issa_approval_handler_field_approval_link',
      'click sortable' => FALSE,
    ],
  ];
  return $data;
}