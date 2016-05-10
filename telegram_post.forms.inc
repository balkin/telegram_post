<?php

/**
 * Generate a telegram announce form
 * @param $form
 */
function __telegram_post_process_node_form(&$form)
{
  $node = $form['#node'];
  $updating = !empty($node->nid) && !empty($node->status);
  $default = variable_get('telegram_post_default_value', 0);
  if ($default && $updating) {
    $default = variable_get('telegram_post_on_update', 0);
  }
  // Create a fieldset
  $form['telegram_post'] = array(
    '#type' => 'fieldset',
    '#title' => t('Post to Telegram'),
    '#group' => 'additional_settings',
    '#weight' => 1,
    '#default_value' => $default,
  );

  $form['telegram_post']['post_to_telegram'] = array(
    '#type' => 'checkbox',
    '#title' => t('Post to Telegram'),
    '#description' => t('Announce this post to Telegram.'),
  );

  $apikey = variable_get('telegram_post_apikey');
  $channel = variable_get('telegram_post_channel_name');

  // If Telegram Post module was not configured, we should disable this option
  if (empty($apikey) && empty($channel)) {
    $form['telegram_post']['post_to_telegram']['#disabled'] = TRUE;
    $form['telegram_post']['post_to_telegram']['#value'] = 0;
    $form['telegram_post']['post_to_telegram']['#description'] = t("API Key or Channel were not specified.");
    return;
  }

  $form['telegram_post']['status'] = array(
    '#type' => 'textfield',
    '#id' => 'telegram-status',
    '#default_value' => $updating ? telegram_post_get_update_message() : telegram_post_get_create_message(),
    '#description' => t('This text will be used as a template for posting to Telegram. Following token replacements are available: @url, @url-alias and @title'),
    '#maxlength' => 200,
    '#states' => array(
      'visible' => array(
        ':input[name="post_to_telegram"]' => array(
          'checked' => TRUE,
        ),
      )
    )
  );

}
