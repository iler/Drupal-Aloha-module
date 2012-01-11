<?php

/**
 *  Aloha Editor Administrative settings form
 */
function aloha_admin() {
  $form = array();
  
  $form['aloha_link_plugin'] = array(
  	'#type' => 'checkbox',
    '#title' => t('Enable link plugin'),
    '#description' => t('Enables the link plugin for Aloha Editor.'),
    '#default_value' => variable_get('aloha_link_plugin', TRUE),
  );
  
  if(!file_exists(libraries_get_path('aloha') . '/lib/aloha.js')) {
    drupal_set_message(t('You need to download the !aloha and extract the entire contents of the archive into the %path folder of your server.', array('!aloha' => l(t('Aloha Editor'), 'http://www.aloha-editor.org/'), '%path' => 'sites/all/libraries/aloha')), 'error', FALSE);
  }
  
  $form = system_settings_form($form);

  return $form;
}