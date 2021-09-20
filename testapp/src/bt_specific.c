#include "bt_specific.h"
#include "zephyr_includes.h"

struct bt_conn *default_conn;
bool authenticating = false;

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_DIS_VAL)),
};

/* Framework Message handling Ends here */

/*
 * start_advertisement
 * Framework Request to start the Advertisement
 */
 
void start_advertisement(void)
{
    int err;
    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) 
        printk("ADVERTISE_FAILED\n");
    else
        printk("ADVERTISE_SUCCESSFULL\n");
}

/*
 * advertise_stop
 * Framework Request to stop the Advertisement
 */
 
void advertise_stop(void)
{
    bt_le_adv_stop();
    printk("ADVERTISE_STOP_SUCCESSFULL\n");
}

/*
 * get_security_level
 * Get the Security Level from the BT Stack
 */
 
void get_security_level()
{
    bt_security_t bt_sec;
    bt_sec = bt_conn_get_security(default_conn);
    if (bt_sec == BT_SECURITY_L1)
    {
        printk("BT_SECURITY_L1\n");
    }
    else if (bt_sec == BT_SECURITY_L4)
    {
        printk("BT_SECURITY_L4\n");
    }
    else
    {

        printk("Unknown Security Level %d\n",bt_sec);
    }
}

/*
 * passkey_confirm_received
 * Pass Key Confirmation Displayed on the Framework
 */
 
 void passkey_confirm_received(void)
{
    bt_conn_auth_passkey_confirm(default_conn);
}

void cancel_auth(void)
{
    auth_cancel(default_conn);
}

 /* Framework Message handling Ends here */
 
 /* Bluetooth Stack Call back Starts here */
 

/*
 * connected
 * BT Stack Connection Call back from Zehpyr Stack
 */
 
void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        printk("Connection failed (err 0x%02x)\n", err);
    } else {
        printk("CONNECT\n");
        default_conn = bt_conn_ref(conn);
        bt_conn_set_security(default_conn, BT_SECURITY_L4);
    }
}

/*
 * disconnected
 * BT Stack Connection Call back from Zehpyr Stack
 */
 
void disconnected(struct bt_conn *conn, uint8_t reason)
{
    printk("DISCONNECT\n");
    if (default_conn)
    {
        bt_conn_unref(default_conn);
        default_conn = NULL;
    }
}

/*
 * security_level_changed
 * BT Stack Connection Call back from Zehpyr Stack
 */
 
void security_level_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err)
{
    printk("Security Level Changed to : %d\n", level);
    if(level==1)
    {
        printk("BT_SECURITY_L1\n");
    }else if (level==4)
    {
        printk("BT_SECURITY_L4\n");
    }else{
        printk("\nHMM Something !! Wrong security_level_changed to %d\n", level);
    } 
}

/*
 * pairing_passkey_display
 * BT Stack Security Call back from Zehpyr Stack
 */

void pairing_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
   char addr[BT_ADDR_LE_STR_LEN];
   bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
   printk("Passkey for %s: %06u\n", addr, passkey);
}

/*
 * auth_confirm
 * BT Stack Security Call back from Zehpyr Stack
 */
 
void auth_confirm(struct bt_conn *conn, unsigned int passkey)
{
   default_conn = conn;
   char addr[BT_ADDR_LE_STR_LEN];
   char passkey_str[7];
   bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
   snprintk(passkey_str, 7, "%06u", passkey);
   printk("%s: %s\n", addr, passkey_str);
   if(authenticating==true)
   {
     bt_conn_auth_passkey_confirm(default_conn);
   }
   else
   {
       auth_cancel(default_conn);
   }
   authenticating = false;
}

/*
 * auth_cancel
 * BT Stack Security Call back from Zehpyr Stack
 */
 
void auth_cancel(struct bt_conn *conn)
{
   printk("Pairing cancelled\n");
   bt_conn_auth_cancel(conn);
}



/*
 * clear_all_bonds
 * Clear all stored bonding information
 */
 
void clear_all_bonds()
{
    bt_unpair(BT_ID_DEFAULT, BT_ADDR_LE_ANY);
}

/*
 * settings_runtime_load
 * Load the DIS Related settings
 */
 
int settings_runtime_load(void)
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
