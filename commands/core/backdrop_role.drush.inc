<?php

/**
 * Implementation of hook_drush_command().
 */
function backdrop_role_drush_command() {
  $items['backdrop-role-create'] = array(
    'description' => 'Create a new role.',
    'examples' => array(
      "drush role-create 'test role'" => "Create a new role 'test role' on D6 or D7; auto-assign the rid. On D8, 'test role' is the rid, and the human-readable name is set to 'Test role'.",
      "drush role-create 'test role' 'Test role'" => "Create a new role with a machine name of 'test role', and a human-readable name of 'Test role'. On D6 and D7, behaves as the previous example."
    ),
    'arguments' => array(
      'machine name' => 'The symbolic machine name for the role. Required.',
      'human-readable name' => 'A descriptive name for the role. Optional; Drupal 8 only.  Ignored in D6 and D7.',
    ),
    'aliases' => array('rcrt'),
    'callback' => 'backdrop_command_role_create',
  );
  $items['backdrop-role-delete'] = array(
    'description' => 'Delete a role.',
    'examples' => array(
      "drush role-delete 'test role'" => "Delete the role 'test role'.",
    ),
    'arguments' => array(
      'machine name' => 'The symbolic machine name for the role. Required.  In D6 and D7, this may also be a numeric role ID.',
    ),
    'aliases' => array('rdel'),
    'callback' => 'backdrop_command_role_delete',
  );
  $items['backdrop-role-add-perm'] = array(
    'description' => 'Grant specified permission(s) to a role.',
    'examples' => array(
      "drush role-add-perm 'anonymous user' 'post comments'" => 'Allow anon users to post comments.',
      "drush role-add-perm 'anonymous user' \"'post comments','access content'\"" => 'Allow anon users to post comments and access content.',
      "drush role-add-perm 'authenticated user' --module=node" => 'Select a permission from "node" permissions to add to logged in users.'
    ),
    'arguments' => array(
      'role' => 'The role to modify.  Required.',
      'permissions' => 'The list of permission to grant, delimited by commas. Required, unless the --module option is used.',
    ),
    'required-arguments' => 1,
    'options' => array(
      'module' => 'Select the permission to modify from an interactive list of all permissions available in the specified module.',
    ),
    'global-options' => array(
      'cache-clear',
    ),
    'aliases' => array('rap',),
    'callback' => 'backdrop_command_role_add_perm',
  );

  $items['backdrop-role-remove-perm'] = array(
    'description' => 'Remove specified permission(s) from a role.',
    'examples' => array(
      "drush role-remove-perm 'anonymous user' 'access content'" => 'Hide content from anon users.',
    ),
    'arguments' => array(
      'role' => 'The role to modify.',
      'permissions' => 'The list of permission to grant, delimited by commas. Required, unless the --module option is used.',
    ),
    'required-arguments' => 1,
    'options' => array(
      'module' => 'Select the permission to modify from an interactive list of all permissions available in the specified module.',
    ),
    'global-options' => array(
      'cache-clear',
    ),
    'aliases' => array('rmp'),
    'callback' => 'backdrop_command_role_remove_perm',
  );

  $items['backdrop-role-list'] = array(
    'description' => 'Display a list of all roles defined on the system.  If a role name is provided as an argument, then all of the permissions of that role will be listed.  If a permission name is provided as an option, then all of the roles that have been granted that permission will be listed.',
    'examples' => array(
      "drush role-list --filter='administer nodes'" => 'Display a list of roles that have the administer nodes permission assigned.',
      "drush role-list 'anonymous user'" => 'Display all of the permissions assigned to the anon user role.'
    ),
    'arguments' => array(
      'role' => 'The role to list.  Optional; if specified, lists all permissions assigned to that role.  If no role is specified, lists all of the roles available on the system.',
    ),
    'options' => array(
      'filter' => 'Limits the list of roles to only those that have been assigned the specified permission. Optional; may not be specified if a role argument is provided.',
    ),
    'outputformat' => array(
      'default' => 'table',
      'pipe-format' => 'list',
      'field-labels' => array('rid' => 'ID', 'label' => 'Role Label', 'perm' => "Permission"),
      'output-data-type' => 'format-table',
    ),
    'aliases' => array('rls'),
    'callback' => 'backdrop_command_role_list'
  );

  return $items;
}

/**
 * Create the specified role
 */
function backdrop_command_role_create($rid, $role_name = '') {
  $role = drush_role_get_class();
  $result = $role->role_create($rid, $role_name);
  if ($result !== FALSE) {
    drush_log(dt('Created "!role"', array('!role' => $rid)), LogLevel::SUCCESS);
  }
  return $result;
}

/**
 * Delete the specified role
 */
function backdrop_command_role_delete($rid) {
  $role = drush_role_get_class($rid);
  if ($role === FALSE) {
    return FALSE;
  }
  $result = $role->delete();
  if ($result !== FALSE) {
    drush_log(dt('Deleted "!role"', array('!role' => $rid)), LogLevel::SUCCESS);
  }
  return $result;
}

/**
 * Add one or more permission(s) to the specified role.
 *
 * @param string $rid machine name for a role
 * @param null|string $permissions machine names, delimited by commas.
 *
 * @return bool
 */
<<<<<<< HEAD
function backdrop_command_role_add_perm($role_name, $permissions = NULL) {
=======
function backdrop_command_role_add_perm($rid, $permissions = NULL) {
>>>>>>> 975365361335dbb481fda2070f1d5f2f245d16c8
  if (is_null($permissions)) {
    // Assume --module is used thus inject a FALSE
    $perms = array(FALSE);
  }
  else {
    $perms = _convert_csv_to_array($permissions);
  }

  $added_perm = FALSE;

  foreach($perms as $perm) {
<<<<<<< HEAD
    $result = backdrop_command_role_perm('add', $role_name, $perm);
=======
    $result = backdrop_command_role_perm('add', $rid, $perm);
>>>>>>> 975365361335dbb481fda2070f1d5f2f245d16c8
    if ($result !== FALSE) {
      $added_perm = TRUE;
      drush_log(dt('Added "!perm" to "!role"', array('!perm' => $perm, '!role' => $result->name)), LogLevel::SUCCESS);
    }
  }

  if ($added_perm) {
    cache_clear_all();
  }

  return $result;
}

/**
 * Remove permission(s) from the specified role.
 *
 * @param string $rid machine name for a role
 * @param null|string $permissions machine names, delimited by commas.
 *
 * @return bool
 */
function backdrop_command_role_remove_perm($rid, $permissions = NULL) {
  if (is_null($permissions)) {
    // Assume --module is used thus inject a FALSE
    $perms = array(FALSE);
  }
  else {
    $perms = _convert_csv_to_array($permissions);
  }

  $removed_perm = FALSE;

  foreach($perms as $perm) {
    $result = backdrop_command_role_perm('remove', $rid, $perm);
    if ($result !== FALSE) {
      $removed_perm = TRUE;
      drush_log(dt('Removed "!perm" from "!role"', array('!perm' => $perm, '!role' => $result->name)), LogLevel::OK);
    }
  }

  if ($removed_perm) {
    drush_drupal_cache_clear_all();
  }

  return $result;
}

/**
 * Implement permission add / remove operations.
 *
 * @param string $action 'add' | 'remove'
 * @param string $rid
 * @param string|null $permission
 *
 * @return bool|RoleBase
 *
 * @see drush_set_error()
<<<<<<< HEAD
 * TODO: $rid should be $role_name
 */
function backdrop_command_role_perm($action, $role_name, $permission = NULL) {
  $role = user_role_load($role_name);
=======
 */
function backdrop_command_role_perm($action, $rid, $permission = NULL) {
  $role = user_role_load($rid);
>>>>>>> 975365361335dbb481fda2070f1d5f2f245d16c8
  if (!$role) {
    return FALSE;
  }

<<<<<<< HEAD
  // If a permission wasn't provided, but the module option is specified,
  // provide a list of permissions provided by that module.
  if (!$permission && $module = drush_get_option('module', FALSE)) {
    drush_include_engine('backdrop', 'environment');
=======

  // If a permission wasn't provided, but the module option is specified,
  // provide a list of permissions provided by that module.
  if (!$permission && $module = drush_get_option('module', FALSE)) {
    drush_include_engine('drupal', 'environment');
>>>>>>> 975365361335dbb481fda2070f1d5f2f245d16c8
    if (!drush_module_exists($module)) {
      return drush_set_error('DRUSH_ROLE_ERROR', dt('!module not enabled!', array('!module' => $module)));
    }
    $module_perms = $role->getModulePerms($module);
    if (empty($module_perms)) {
      return drush_set_error('DRUSH_ROLE_NO_PERMISSIONS', dt('No permissions found for module !module', array('!module' => $module)));
    }
    $choice = drush_choice($module_perms, "Enter a number to choose which permission to $action.");
    if ($choice === FALSE) {
      return drush_user_abort();
    }
    $permission = $module_perms[$choice];
  }
  else {
    $permissions = $role->getAllModulePerms();
    if (!in_array($permission, $permissions)) {
      return drush_set_error(dt('Could not find the permission: !perm', array('!perm' => $permission)));
    }
  }

  $result = $role->{$action}($permission);
  if ($result === FALSE) {
    return FALSE;
  }
  return $role;
}

/**
 * Displays a list of roles
 */
function backdrop_command_role_list($rid = '') {
  $result = array();
  if (empty($rid)) {
    drush_hide_output_fields(array('perm'));
    // Get options passed.
    $perm = drush_get_option('filter');
    $roles = array();

    // Get all roles - if $perm is empty user_roles retrieves all roles.
    $roles = user_roles(FALSE, $perm);
    if (empty($roles)) {
      return drush_set_error('DRUSH_NO_ROLES', dt("No roles found."));
    }
    foreach ($roles as $rid => $value) {
      $role = drush_role_get_class($rid);
      $result[$role->name] = array(
        'rid' => $rid,
        'label' => $role->name,
      );
    }
  }
  else {
    drush_hide_output_fields(array('rid', 'label'));
    $role = drush_role_get_class($rid);
    if (!$role) {
      return FALSE;
    }
    $perms = $role->getPerms();
    foreach ($perms as $permission) {
      $result[$permission] = array(
        'perm' => $permission);
    }
  }
  return $result;
}
