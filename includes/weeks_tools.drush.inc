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