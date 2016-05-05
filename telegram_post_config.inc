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
    '#description' => t('Telegram bot API key.') .
      l('Learn how to create a telegram bot and get API key',
        'https://core.telegram.org/bots#botfather',
        array('attributes' => array('target' => '_blank'))),
  );

  $form['telegram_post_channel_name'] = array(
    '#required' => TRUE,
    '#type' => 'textfield',
    '#title' => t('Channel name:'),
    '#default_value' => variable_get('telegram_post_channel_name'),
    '#description' => t('Telegram channel name. Example: <u>@channel</u>'),
  );

  $form['telegram_post_default_value'] = array(
    '#type' => 'checkbox',
    '#title' => t('Post to Telegram by default'),
    '#default_value' => variable_get('telegram_post_default_value', 0),
    '#description' => t('When active, automatically post to Telegram when the node is first published.'),
  );

  $form['telegram_post_on_update'] = array(
    '#type' => 'checkbox',
    '#title' => t('Also post to Telegram on update'),
    '#default_value' => variable_get('telegram_post_on_update', 0),
    '#description' => t('Also announces to Telegram when the node is updated. May cause duplicate posts.'),
  );

  $form['telegram_post_default_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Default format string'),
    '#maxlength' => 140,
    '#description' => t('This text will be used as a template for posting to Telegram. ' .
      'Following token replacements are available: @url, @url-alias and @title'),
    '#default_value' => variable_get('twitter_post_default_format', t('New post: @title @url-alias')),
  );

  return system_settings_form($form);
}

function telegram_post_config_form_validate($form, &$form_state)
{
  if (!preg_match('/^(@+[a-z0-9\-\_\s]+)/i', trim($form_state['values']['telegram_post_channel_name'])))
    form_set_error('pr_pas', t('Please provide a valid channel name. Example: <u>@channel</u>'));
}