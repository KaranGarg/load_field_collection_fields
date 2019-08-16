<?php

/**
 * @file
 * Field Collection Load module administration
 */

/**
 * Form Builder: Field collection load configuration
 *
 * @param $form
 * @param $form_state
 * @return $form
 */
function load_field_collection_fields_form($form, &$form_state) {
  $node_type_options = array();
  $selected_node_types = array();
  $selected_vocabularies = array();
  $selected_user_entity = array();

  // Get all available node types.
  $nodes_type = node_type_get_types();
  // The options to display in our checkboxes.
  foreach ($nodes_type as $bundle_machine_name => $node_type) {
    $node_type_options[$bundle_machine_name] = isset($node_type->name) ? $node_type->name : ucwords(str_replace("_", " ", $bundle_machine_name));
  }

  unset($node_type_options['customer']);
  unset($node_type_options['resource']);
  unset($node_type_options['event']);
  unset($node_type_options['cxo_mobile_content']);
  unset($node_type_options['security_advisories']);
  unset($node_type_options['resources']);
  unset($node_type_options['cxo_mobile_content_old']);
  unset($node_type_options['cxo_news']);
  unset($node_type_options['news']);
  unset($node_type_options['non_drupal_redirects']);
  unset($node_type_options['press']);
  unset($node_type_options['webcasts']);
  unset($node_type_options['zscaler_tools']);

  // Selected node bundles.
  $selected_bundles = variable_get('load_field_collection_fields_bundles');
  if (isset($selected_bundles) && !empty($selected_bundles)) {
    foreach ($selected_bundles as $bundle => $value) {
      $selected_node_types[$bundle] = ($value == 1) ? $bundle : $value;
    }
  }

  // Selected taxonomies.
  $selected_taxonomies = variable_get('load_field_collection_fields_taxonomies');

  if (isset($selected_taxonomies) && !empty($selected_taxonomies)) {
    foreach ($selected_taxonomies as $taxonomy => $value) {
      $selected_vocabularies[$taxonomy] = ($value == 1) ? $taxonomy : $value;
    }
  }



  // Selected user.
  $selected_user = variable_get('load_field_collection_fields_users');
  if (isset($selected_user) && !empty($selected_user)) {
    foreach ($selected_user as $user_entity => $value) {
      $selected_user_entity[$user_entity] = ($value == 1) ? $user_entity : $value;
    }
  }

  // Gets the list of all vocabularies.
  $taxonomies = taxonomy_get_vocabularies();
  $taxonomy_options = array();
  foreach ($taxonomies as $taxonomy) {
    $taxonomy_options[$taxonomy->machine_name] = $taxonomy->name;
  }

  unset($taxonomy_options['customers_bg_color']);
  unset($taxonomy_options['cxo_mobile_content_sections']);
  unset($taxonomy_options['leadership_type']);
  unset($taxonomy_options['news_source']);
  unset($taxonomy_options['resource_type']);
  unset($taxonomy_options['webcast_categories']);
  unset($taxonomy_options['zscaler_tools_category']);
  unset($taxonomy_options['blog']);
  unset($taxonomy_options['vertical']);
  unset($taxonomy_options['event_type']);

  $form['#theme'] = 'system_settings_form';

  $form['content_type'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Types'),
    '#description' => 'Content types for which field collection fields should be loaded when using <i>node_load</i>'
  );

  $form['content_type']['load_field_collection_fields_bundles'] = array(
    '#title_display' => 'invisible',
    '#type' => 'checkboxes',
    '#options' => $node_type_options,
    '#default_value' => $selected_node_types,
  );


  $form['taxonomy_term'] = array(
    '#type' => 'fieldset',
    '#title' => t('Taxonomies'),
    '#description' => 'Taxonomies for which field collection fields should be loaded when using <i>taxonomy_term_load</i>'
  );

  $form['taxonomy_term']['load_field_collection_fields_taxonomies'] = array(
    '#title_display' => 'invisible',
    '#type' => 'checkboxes',
    '#options' => $taxonomy_options,
    '#default_value' => $selected_vocabularies,
  );

  $form['users'] = array(
    '#type' => 'fieldset',
    '#title' => t('Users'),
    '#description' => 'If role attached field collection fields should be loaded when using <i>user_load</i>'
  );

  $form['users']['load_field_collection_fields_users'] = array(
    '#title_display' => 'invisible',
    '#type' => 'checkboxes',
    '#options' => array('user' => 'Users'),
    '#default_value' => $selected_user_entity,
  );

  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;

}

/**
 * Submit Handler: Field collection load configuration
 * @param $form
 * @param $form_state
 */
function load_field_collection_fields_form_submit($form, &$form_state) {
  $form_data = array();
  $form_data_vocab = array();
  $form_data_users = array();

  foreach ($form_state['values']['load_field_collection_fields_bundles'] as $key => $bundle_name) {
    $form_data[$key] = is_string($bundle_name) ? 1 : 0;
  }

  foreach ($form_state['values']['load_field_collection_fields_taxonomies'] as $key => $vocab_name) {
    $form_data_vocab[$key] = is_string($vocab_name) ? 1 : 0;
  }

  foreach ($form_state['values']['load_field_collection_fields_users'] as $key => $users) {
    $form_data_users[$key] = is_string($users) ? 1 : 0;
  }

  variable_set('load_field_collection_fields_bundles', $form_data);
  variable_set('load_field_collection_fields_taxonomies', $form_data_vocab);
  variable_set('load_field_collection_fields_users', $form_data_users);
  drupal_set_message(t('Your configurations have been saved.'));
}
