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
int settings_runtime_load(void);
void disconnected(struct bt_conn *conn, uint8_t reason);
void connected(struct bt_conn *conn, uint8_t err);

#endif
