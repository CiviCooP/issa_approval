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
  $data['issa_approval']['did_i_comment'] = [
    'title' => t('Did I comment'),
    'help' => t('Did I comment on this application'),
    'field' => [
      'handler' => 'issa_approval_handler_field_did_i_comment',
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