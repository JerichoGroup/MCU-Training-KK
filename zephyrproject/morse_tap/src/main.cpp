/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <task.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>


void pin_reader_entry(void*, void*, void*);
void uart_publisher_entry(void*, void*, void*);
void led_signaler_entry(void*, void*, void*);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS     150
#define THREAD_STACK_SIZE 1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED2_NODE DT_ALIAS(led2)


/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);


class TEST{

};

void pin_reader_entry(void* p1, void* p2, void* p3){
	return;
}
void uart_publisher_entry(void* p1, void* p2, void* p3){
	return;
}
void led_signaler_entry(void* p1, void* p2, void* p3){
	return;
}


k_thread pin_reader, uart_publisher, led_signaler;
k_thread_stack_t pin_reader_stack[THREAD_STACK_SIZE];
k_thread_stack_t uart_publisher_stack[THREAD_STACK_SIZE];
k_thread_stack_t led_signaler_stack[THREAD_STACK_SIZE];


int main(void)
{

	k_thread_create(&pin_reader, pin_reader_stack, THREAD_STACK_SIZE, );
	k_thread_create(&uart_publisher, uart_publisher_stack, THREAD_STACK_SIZE, );
	k_thread_create(&led_signaler, led_signaler_stack, THREAD_STACK_SIZE, );



	vTaskStartScheduler()
	xTaskCreate(NULL,"",1,NULL,1,NULL);

	

	// void gpio_init_callback()
	//gpio_pin_configure_dt(&random_pin, )
	// int is_input_on = gpio_pin_read(&input_pin, INPUT_PIN)




	// int ret0;
	// int ret2;

	// bool led_state = true;

	// if (!gpio_is_ready_dt(&led0)) {
	// 	return 0;
	// }

	// if (!gpio_is_ready_dt(&led2)) {
	// 	return 0;
	// }

	// ret0 = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	// ret2 = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);

	// if (ret0 < 0) {
	// 	return 0;
	// }
	// if (ret2 < 0) {
	// 	return 0;
	// }

	// while (1) {
	// 	ret0 = gpio_pin_toggle_dt(&led0);
	// 	ret2 = gpio_pin_toggle_dt(&led2);

	// 	if (ret0 < 0) {
	// 		return 0;
	// 	}
	// 	if (ret2 < 0) {
	// 		return 0;
	// 	}

	// 	led_state = !led_state;
	// 	printf("LED state: %s\n", led_state ? "ON" : "OFF");
	// 	k_msleep(SLEEP_TIME_MS);
	// }
	// return 0;
}
