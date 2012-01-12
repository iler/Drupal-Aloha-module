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

	$plugin_status = variable_get('aloha_plugins', array());
	$active_plugins = array();
	$inactive_plugins = array();
	
	foreach ($options as $key => $value) {
		if($plugin_status[$key]!='0') {
			$active_plugins[$key] = $value;
		}
		else {
			$inactive_plugins[$key] = $value;
		}
	}
  
	$form['aloha_plugins'] = array(
		'#type' => 'fieldset',
		'#title' => t('Plugins'),
		'#description' => t('Select plugins that you want to use with Aloha Editor.'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		'#tree' => TRUE,
	);
	
	$form['aloha_plugins']['active'] = array(
		'#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'aloha-active-plugins',
      ),
    ),
	);
	$form['aloha_plugins']['inactive'] = array(
		'#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'aloha-inactive-plugins',
      ),
    ),
	);
	
	$form['aloha_plugins']['active']['list'] = array(
		'#type' => 'checkboxes',
		'#options' => $active_plugins,
		'#title' => t('Enabled plugins'),
		'#default_value' => variable_get('aloha_plugins', array()),
		'#theme' => 'aloha_plugins_settings',
	);
	
	$form['aloha_plugins']['inactive']['list'] = array(
		'#type' => 'checkboxes',
		'#options' => $inactive_plugins,
	  '#title' => t('Disabled plugins'),
		'#theme' => 'aloha_plugins_settings',
	);
	
	//has_krumo();
	//krumo(variable_get('aloha_plugins', array()));
  
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
	has_krumo();
	krumo($variables);
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

	$plugin_status = variable_get('aloha_plugins', array());
	$active_plugins = array();
	$inactive_plugins = array();
	
	foreach ($options as $key => $value) {
		if($plugin_status[$key]!='0') {
			$active_plugins[$key] = $value;
		}
		else {
			$inactive_plugins[$key] = $value;
		}
	}
  
	$form['aloha_plugins'] = array(
		'#type' => 'fieldset',
		'#title' => t('Plugins'),
		'#description' => t('Select plugins that you want to use with Aloha Editor.'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
		'#tree' => TRUE,
	);
	
	$form['aloha_plugins']['active'] = array(
		'#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'aloha-active-plugins',
      ),
    ),
	);
	$form['aloha_plugins']['inactive'] = array(
		'#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'aloha-inactive-plugins',
      ),
    ),
	);
	
	$form['aloha_plugins']['active']['list'] = array(
		'#type' => 'checkboxes',
		'#options' => $active_plugins,
		'#title' => t('Enabled plugins'),
		'#default_value' => variable_get('aloha_plugins', array()),
		'#theme' => 'aloha_plugins_settings',
	);
	
	$form['aloha_plugins']['inactive']['list'] = array(
		'#type' => 'checkboxes',
		'#options' => $inactive_plugins,
	  '#title' => t('Disabled plugins'),
		'#theme' => 'aloha_plugins_settings',
	);
	
	//has_krumo();
	//krumo(variable_get('aloha_plugins', array()));
  
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
	has_krumo();
	krumo($variables);
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