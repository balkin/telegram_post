<?php

/**
 * Добавляем чекбокс, который будет указывать стоит ли отсылать сообщение
 */
function __telegram_item_process_node_form(&$form) {
  // добавляем новый fieldset и задаем ему вес
  $form['telegram_item'] = array(
	'#type'   => 'fieldset',
	'#title'  => t('Telegram item'),
	'#group'  => 'additional_settings',
	'#weight' => -11,
  );

  $form['telegram_item']['telegram_item_post_this_node'] = array(
	'#type'          => 'checkbox',
	'#title'         => t('Send to Telegram'),
	'#description'   => t('After you submit this node it will be send to Telegram.'),
  );

  $apikey = variable_get('telegram_item_apikey');
  $channel = variable_get('telegram_item_channel_name');

  // отключаем элемент управления, если мы не настроили telegram в админке
  if (empty($apikey) && empty($channel)) {
	$form['telegram_item']['telegram_item_post_this_node']['#disabled']    = TRUE;
	$form['telegram_item']['telegram_item_post_this_node']['#value']       = 0;
	$form['telegram_item']['telegram_item_post_this_node']['#description'] =
	  t("You can't Telegram nodes until apikey or channel is empty.");
  }
}
