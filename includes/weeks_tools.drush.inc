<?php
/**
 * @file
 * Provide Drush integration for release building and dependency building.
 */


/**
 * Implements hook_drush_help().
 *
 * @param string $section
 *
 * @return null|string
 */
function weeks_tools_drush_help($section) {
  switch ($section) {
    case 'weeks-tools-stressor':
      return dt("Rapidly loads nodes and checks is loading was successful");
    case 'weeks-tools-field-scan':
      return dt("Find nodes with the target string inside the indicated field");
    default:
      return NULL;
  }
}

/**
 * Implements hook_drush_command().
 */
function weeks_tools_drush_command() {
  $items = array();
  $items['weeks-tools-stressor'] = array(
    'description' => dt("Rapidly loads nodes and checks is loading was successful"),
    'aliases' => array(
      'wtsr',
    ),
    'arguments' => array(
      'nid' => 'NULL or a specific node id for rapid tests',
      'stress' => 'the number of node loads to run.  Will randomly pull nid if none is given'
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
  );

  $items['weeks-tools-field-scan'] = array(
    'description' => dt("Check field contents in the database for a target string"),
    'aliases' => array(
      'wtfs',
    ),
    'arguments' => array(
      'field' => 'machine name of the field to scan',
      'target' => 'the target string, defaults to "script"',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
  );

  return $items;
}
/*
this used to have 
'options' => array(
      'all' => dt('Fixes all module missing messages'),
    ),
*/

/**
 * Drush command.
 *
 * @param int $nid
 *        The node id of a specific page to test.  A db_query 
 *          is run to fetch a random nid if none is given
 * @param int $stress
 *        The number of times to load and release the nid, or a random nid
 */
function drush_weeks_tools_stressor( $nid = NULL, $stress = 10 ) {
  drush_log(dt('Starting stress loading of node(s)'), 'notice');
  weeks_tools_stress_load( $nid, $stress);
  drush_log(dt('Stressing is finished, drink some tea'), 'notice');
}

/**
 * Drush command.
 *
 * @param string $field
 *        The machine name of the field to scan.  A db_query 
 *          is run check all instances for the target string
 * @param string $target
 *        The string to be found
 */
function drush_weeks_tools_field_scan($field, $target = 'script' ) {
  // drush log default type is Notice
  drush_log(dt('Begin scan of field contents'));
  $findings = weeks_tools_field_db_scan($field, $target);
  foreach ($findings as $nid => $details) {
    drush_log(dt('Match found.  /node/'. $nid .' is a '. $details->type .' node.  '. $details->title ));
  }
  drush_log(dt('Scan complete'));
}