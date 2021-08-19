/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr.h>
#include <console/console.h>

void main(void)
{
	console_init();

	while (1) {
		uint8_t c = console_getchar();

		console_putchar(c);
		if (c == '\r') {
			console_putchar('\n');
		}
	}
}
