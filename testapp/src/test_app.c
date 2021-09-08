#include "test_app.h"
#include "zephyr_includes.h"
#include "bt_specific.h"


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
