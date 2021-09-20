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
    .security_changed = security_level_changed
};

// callbacks for pairing - IO Capabilities
static struct bt_conn_auth_cb pairing_cb_display = {
      .passkey_display = pairing_passkey_display,
      .passkey_confirm = auth_confirm,
      .cancel = auth_cancel,
};

static void bt_ready_callback(int err)
{
    if(err)
    {
        printk("BT Initialization failed\n");
        return;
    }

    return;
}
void main(void)
{
    int err;
    
    err = bt_enable(bt_ready_callback);
    
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }
    
    clear_all_bonds();
    
    if (IS_ENABLED(CONFIG_BT_SETTINGS)) {
        settings_load();
    }

    settings_runtime_load();

    bt_conn_cb_register(&conn_callbacks);
    
    // callback for authentication step
    bt_conn_auth_cb_register(&pairing_cb_display);

    printk("Read Thread Going to Start\n");
    console_getline_init();
}

K_THREAD_DEFINE(test_app_read, STACKSIZE, serial_read_thread, NULL, NULL, NULL,
        PRIORITY, 0, 0);
