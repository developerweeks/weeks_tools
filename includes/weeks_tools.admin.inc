<?php

/**
 * @file
 * The Weeks Tools Settings file.
 */

/**
 * I based this on the Missing Module Message Fixer Form.
 */
function weeks_tools_form() {
  $form = array();

  // Fancy title string.
  $title = t('This few settings are used in the various helper functions. I haz repo: <a href="@link" target="_blank">oh GitHub</a>.', array(
    '@link' => 'https://github.com/developerweeks/weeks_drupal_tools',
  ));

  // Title.
  $form['title'] = array(
    '#type' => 'item',
    '#markup' => '<h2><center>' . $title . '</h2></center>',
  );

  $form['strip_tags'] = array(
    '#type' => 'textfield',
    '#title' => 'The default html tags to strip',
    '#default_value' => variable_get('wt_unwanted_tags','span/h1/h2/h3/h4/div/strong'),
  );

  $form['line_separator'] = array(
    '#type' => 'textfield',
    '#title' => 'The default end-of-line indicator',
    '#default_value' => variable_get('wt_line_separator', ' <br>'),
    '#description' => 'an HTML br is useful for site messages, while a line break/carriage return is my preference on command line output.  Additionally, special characters like § are helpful if I want additional text processing on the results.'
  );

  // Fancy submit buttons to win this.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('I Approve!'),
    '#submit' => array('weeks_tools_form_submit'),
    '#prefix' => '<center>',
    '#suffix' => '</center>',
  );

  return $form;
}

/**
 * Submit handler for Weeks Tools admin Form.
 *
 * @param array $form
 * @param array $form_state
 */
function weeks_tools_form_submit(array $form, array &$form_state) {
  // set those variable values 
  variable_set('wt_unwanted_tags', $form_state['values']['strip_tags']);
  variable_set('wt_line_separator', $form_state['values']['line_separator']);

  // that was all we needed to do here
  return;
}