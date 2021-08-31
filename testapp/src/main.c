/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <settings/settings.h>

#include <console/console.h>

/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_DIS_VAL)),
};

void start_advertisement(void)
{
	int err;
	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) 
		printk("ADVERTISE_FAILED\n");
	else
		printk("ADVERTISE_SUCCESSFULL\n");
}

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err 0x%02x)\n", err);
	} else {
		printk("CONNECT\n");
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("DISCONNECT\n");
}

static void advertise_stop(void)
{
	bt_le_adv_stop();
	printk("ADVERTISE_STOP_SUCCESSFULL\n");
}


static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};

void serial_read_thread(void)
{
	while (1) {
		char *s = console_getline();
		if (strcmp(s, "ADVERTISE") == 0)
		{
		   start_advertisement();
		}
		else if (strcmp(s, "ADVERTISE_STOP") == 0)
		{
		   advertise_stop();
		}
		else
			printk("%s\n", s);
	}
}

static int settings_runtime_load(void)
{
#if defined(CONFIG_BT_DIS_SETTINGS)
	settings_runtime_set("bt/dis/model",
			     "Zephyr Model",
			     sizeof("Zephyr Model"));
	settings_runtime_set("bt/dis/manuf",
			     "Zephyr Manufacturer",
			     sizeof("Zephyr Manufacturer"));
#if defined(CONFIG_BT_DIS_SERIAL_NUMBER)
	settings_runtime_set("bt/dis/serial",
			     CONFIG_BT_DIS_SERIAL_NUMBER_STR,
			     sizeof(CONFIG_BT_DIS_SERIAL_NUMBER_STR));
#endif
#if defined(CONFIG_BT_DIS_SW_REV)
	settings_runtime_set("bt/dis/sw",
			     CONFIG_BT_DIS_SW_REV_STR,
			     sizeof(CONFIG_BT_DIS_SW_REV_STR));
#endif
#if defined(CONFIG_BT_DIS_FW_REV)
	settings_runtime_set("bt/dis/fw",
			     CONFIG_BT_DIS_FW_REV_STR,
			     sizeof(CONFIG_BT_DIS_FW_REV_STR));
#endif
#if defined(CONFIG_BT_DIS_HW_REV)
	settings_runtime_set("bt/dis/hw",
			     CONFIG_BT_DIS_HW_REV_STR,
			     sizeof(CONFIG_BT_DIS_HW_REV_STR));
#endif
#endif
	return 0;
}

void main(void)
{
	int err;
	
	err = bt_enable(NULL);
	
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}
	
	if (IS_ENABLED(CONFIG_BT_SETTINGS)) {
		settings_load();
	}

	settings_runtime_load();

	bt_conn_cb_register(&conn_callbacks);
	
	printk("Read Thread Going to Start\n");
	console_getline_init();
}

K_THREAD_DEFINE(test_app_read, STACKSIZE, serial_read_thread, NULL, NULL, NULL,
		PRIORITY, 0, 0);
