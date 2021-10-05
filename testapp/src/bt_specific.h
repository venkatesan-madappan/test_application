#ifndef __BT_SPECIFIC_H__
#define __BT_SPECIFIC_H__

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <settings/settings.h>

void start_advertisement(void);
void advertise_stop(void);
void passkey_confirm_received(void);
void cancel_auth(void);
void get_security_level(void);
void set_security_level(bt_security_t);


void disconnected(struct bt_conn *conn, uint8_t reason);
void connected(struct bt_conn *conn, uint8_t err);

void clear_all_bonds();

void security_level_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err);
void pairing_passkey_display(struct bt_conn *conn, unsigned int passkey);
void auth_cancel(struct bt_conn *conn);
void auth_confirm(struct bt_conn *conn, unsigned int passkey);
#endif
