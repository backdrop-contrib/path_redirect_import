<?php
/**
 * @file
 * Page to import and export URL redirects.
 */

/**
 *  form for import redirect path
 */
function path_redirect_import_form() {
  $form = array();
  $form['csv'] = array(
    '#type' => 'fieldset',
    '#title' => t('Import URL Redirects from .csv or .txt file'),
  );

  $form['csv']['no_headers'] = array(
    '#type' => 'checkbox',
    '#title' => t('The imported file does not start with a header row.'),
  );

  $items = array(
    t('From URL (required)'),
    t('To URL (required)'),
    t('Redirect Status (optional -- set default below)'),
    t('Redirect Language (optional -- set default below)'),
  );

  $description = t('The CSV file must include columns in the following order:');
  $description .= theme('item_list', array('items' => $items));

  $form['csv']['csv_file'] = array(
    '#type' => 'file',
    '#description' => $description,
  );
  $form['csv']['delimiter'] = array(
    '#type' => 'textfield',
    '#title' => t('Delimiter'),
    '#default_value' => ',',
    '#maxlength' => 2,
    '#size' => 10,
  );
  $form['csv']['override'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override existing redirects'),
    '#description' => t('When unchecked, this option will prevent duplicate redirects.'),
    '#default_value' => FALSE,
  );
  $form['csv']['check_destination'] = array(
    '#type' => 'checkbox',
    '#title' => t('Limit destinations to internal paths'),
    '#description' => t('When unchecked, this option will allow destinations outside Backdrop.'),
    '#default_value' => TRUE,
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default values'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['advanced']['status_code'] = array(
    '#type' => 'select',
    '#title' => t('Default Redirect status'),
    '#description' =>
      t('You can find more information about HTTP redirect status codes at
      <a href="@status-codes">@status-codes</a>.',
      array('@status-codes' =>
        'http://en.wikipedia.org/wiki/List_of_HTTP_status_codes#3xx_Redirection',
      )
    ),
    '#default_value' => 301,
    '#options' => redirect_status_code_options(),
  );
  $form['advanced']['langcode'] = array(
    '#type' => 'select',
    '#title' => t('Default Redirect language'),
    '#description' => t('A redirect for a specific language will always be used when requesting this page in that language, and takes precedence over redirects for <em>All languages</em>.'),
    '#default_value' => LANGUAGE_NONE,
    '#options' => array(LANGUAGE_NONE => t('All languages')),
  );
  if (module_exists('locale')) {
    $form['advanced']['langcode']['#options'] = array(LANGUAGE_NONE => t('All languages')) + locale_language_list('name');
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  $form['#attributes'] = array('enctype' => "multipart/form-data");

  return $form;
}

/**
 * validate form function
 */
function path_redirect_import_form_validate($form, &$form_state) {
  $validators = array('file_validate_extensions' => array('csv txt'));
  if ($file = file_save_upload('csv_file', $validators)) {
    $form_state['uploaded_file'] = $file;
  }
  else {
    form_set_error('form', t('File upload failed.'));
  }
}

/**
 * Submit form function
 */
function path_redirect_import_form_submit($form, &$form_state) {
  ini_set('auto_detect_line_endings', TRUE);
  if (!isset($form_state['uploaded_file'])) {
    return;
  }
  $uri = $form_state['uploaded_file']->uri;
  $result = path_redirect_import_read_file($uri, $form_state['values']);
  if ($result['success']) {
    backdrop_set_message(implode('<br />', $result['message']));
  }
  else {
    backdrop_set_message(implode('<br />', $result['message']), 'error');
  }

  file_delete($form_state['uploaded_file']->fid);
}


/**
 * Export redirects page form
 */
function path_redirect_import_export_form() {
  $form['markup'] = array(
    '#type' => 'item',
    '#markup' => t('You can export all your redirects in path_redirect_import format'),
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Export redirects'),
  );

  return $form;
}

/**
 * Dump current redirects for download as csv.
 */
function path_redirect_import_export_form_submit($form, &$form_state) {
  $query = "SELECT source, redirect, source_options, status_code, langcode FROM {redirect}";
  $redirects = db_query($query)->fetchAll();

  if (!empty($redirects)) {
    path_redirect_import_export_redirects($redirects);
  }
  else {
    backdrop_set_message('Sorry, no redirects to export available at this moment');
  }
}

