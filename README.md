# ISSA Approval

For the International Step by Step Association an approval process is created. This is mostly done by using CiviCRM Case, Drupal Webforms and Drupal Views. This (Drupal) module adds some pieces of functionality to make the complete solution working. Consider it as glue. Use it as inspiration but not in production.

## What is contains

- A checklist for the applicant that can be used as reach all the webforms that must be completed.
- A block with links to the same webforms.
- A block that shows all the colleagues in an organisation.
- A checklist for boardmembers that shows all the information used to evaluate an application.
- A webform (that feels like a view) thats shows all the votes with motivation for an application

## Configuration

To configure the checklists and the blocks for use with the required webforms use the configuration screen at `/admin/config/system/issa-approval`

## Permissions

- `issa approval check list` - gives access to the applicant checklist
- `issa approval board` - gives access to the boardmembers checklist and the view with the voters

## And ...

To create a Custom Url in a webform that returns to the checklist of an organisation use `/issa-approval/board-check-list/[submission:contact-id:1]`