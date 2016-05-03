<?php

/**
 * Administer page telegram_post
 */
function telegram_post_config_form($form, &$form_state)
{
  $form['telegram_post_apikey'] = array(
    '#required' => TRUE,
    '#type' => 'textfield',
    '#title' => t('Bot apikey:'),
    '#default_value' => variable_get('telegram_post_apikey'),
    '#description' => t('Enter apikey telegram bot. ') .
      l('Details how to get bot apikey.',
        'https://core.telegram.org/bots#botfather',
        array('attributes' => array('target' => '_blank'))),
  );

  $form['telegram_post_channel_name'] = array(
    '#required' => TRUE,
    '#type' => 'textfield',
    '#title' => t('Channel name:'),
    '#default_value' => variable_get('telegram_post_channel_name'),
    '#description' => t('Enter telegram channel name. Example: <u>@lib365</u>'),
  );

  return system_settings_form($form);
}

function telegram_post_config_form_validate($form, &$form_state)
{
  if (!preg_match('/^(@+[a-z0-9\-\_\s]+)/i', trim($form_state['values']['telegram_post_channel_name'])))
    form_set_error('pr_pas', t('Please, insert correct channel name. Example: <u>@lib365</u>'));
}