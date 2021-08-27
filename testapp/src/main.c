/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr.h>
#include <console/console.h>
#include <sys/printk.h>
#include <string.h>

/* size of stack area used by each thread */
#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

void serial_read_thread(void)
{
	while (1) {
		char *s = console_getline();
		printk("%s\n", s);
	}
}

void main(void)
{
	printk("Read Thread Going to Start\n");
	console_getline_init();
}

K_THREAD_DEFINE(test_app_read, STACKSIZE, serial_read_thread, NULL, NULL, NULL,
		PRIORITY, 0, 0);
