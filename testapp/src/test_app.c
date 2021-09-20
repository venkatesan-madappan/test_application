#include "test_app.h"
#include "zephyr_includes.h"
#include "bt_specific.h"

extern bool authenticating;

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
        else if (strcmp(s, "AUTHENTICATION_CONFIRMED") == 0)
        {
           printk("Received Authentication_Confirmed \n");
           authenticating = true;
        }
        else if (strcmp(s, "AUTHENTICATION_CANCELED") == 0)
        {
            printk("Received Authentication Cancel \n");
            authenticating = false;
        }
        else if(strcmp(s, "CLEAR_BONDING") == 0)
        {
            printk("Clear Bonding \n");
            clear_all_bonds();
        }
        else if(strcmp(s, "GET_SECURITY_LEVEL") == 0)
        {
            get_security_level();
        }
        else
            printk("%s\n", s);
    }
}
