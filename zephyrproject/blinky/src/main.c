/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */

/* The devicetree node identifier for the "led1" alias. */

/*
 * A build error on this line means your board is unsuppo rted.
 * See the sample documentation for information on how to fix this.
 */

static const struct device * gpiod = DEVICE_DT_GET(DT_NODELABEL(gpiod));



int main(void)
{
	gpio_pin_configure(gpiod,13,GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure(gpiod,14,GPIO_OUTPUT_ACTIVE);

	gpio_pin_set(gpiod, 13, 1);
	gpio_pin_set(gpiod, 14, 1);
	while(1){}


	return 0;
}
