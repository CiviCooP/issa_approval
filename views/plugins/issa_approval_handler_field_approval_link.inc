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
    return issa_approval_helper::approval_link($values->id);
  }
}