/*
 * Copyright (c) Venkatesan Madappan
 *
 */

#include "bt_specific.h"
#include "test_app.h"


/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};

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
