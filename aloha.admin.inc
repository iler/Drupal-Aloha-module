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
  				$options[$folder]=ucfirst($folder);
  			}
  		}
  	}
  }
  
	$form['aloha_plugins'] = array(
		'#type' => 'checkboxes',
		'#options' => $options,
		'#title' => t('Plugins'),
		'#description' => t('Select plugins that you want to use with Aloha Editor.'),
		'#default_value' => variable_get('aloha_plugins', array()),
	);
  
  if(!file_exists(libraries_get_path('aloha') . '/lib/aloha.js')) {
    drupal_set_message(t('You need to download the !aloha and extract the entire contents of the archive into the %path folder of your server.', array('!aloha' => l(t('Aloha Editor'), 'http://www.aloha-editor.org/'), '%path' => 'sites/all/libraries/aloha')), 'error', FALSE);
  }
  
  $form = system_settings_form($form);

  return $form;
}