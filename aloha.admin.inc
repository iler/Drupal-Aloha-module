<?php

/**
 *  Aloha Editor Administrative settings form
 */
function aloha_admin() {
	$form = array();
  $options = array();
  $dir = libraries_get_path('aloha') . '/plugins';
  $categories = array('common', 'extra');
  if($dir) {
  	foreach($categories as $category) {
  		foreach(array_diff(scandir($dir.'/'.$category),array('.','..')) as $folder) {
  			if(is_dir($dir.'/'.$category.'/'.$folder)) {
  				$options[$category.'/'.$folder]=ucfirst($folder);
  			}
  		}
  	}
  }
  
	$form['aloha_plugins'] = array(
		'#type' => 'fieldset',
		'#title' => t('Plugins'),
		'#description' => t('Select plugins that you want to use with Aloha Editor.'),
		'#collapsible' => TRUE,
		'#collapsed' => TRUE,
		'#tree' => TRUE,
	);
	
	$form['aloha_plugins']['list'] = array(
		'#type' => 'checkboxes',
		'#options' => $options,
		'#default_value' => variable_get('aloha_plugins', array()),
	);
  
  if(!file_exists(libraries_get_path('aloha') . '/lib/aloha.js')) {
    drupal_set_message(t('You need to download the !aloha and extract the entire contents of the archive into the %path folder of your server.', array('!aloha' => l(t('Aloha Editor'), 'http://www.aloha-editor.org/'), '%path' => 'sites/all/libraries/aloha')), 'error', FALSE);
  }
  
  $form = system_settings_form($form);
  $form['#submit'][] = 'aloha_admin_submit';

  return $form;
}

/**
 * Layout for the plugins list.
 */
function theme_aloha_plugins_settings($variables) {
	
}

/**
 * Clear JS cache only on Save submit
 *
 * @param <type> $form
 * @param <type> $form_state
 */
function aloha_admin_submit($form, &$form_state) {

  // Check if submit button was pressed and rebuild the functionality.
  // We must use "clicked_button" becaus values['op'] was unset by
  // system_settings_form_submit.
  $op = isset($form_state['clicked_button']['#value']) ? $form_state['clicked_button']['#value'] : '';
  if ($op == t('Save configuration')) {
    drupal_clear_js_cache();
  }
}