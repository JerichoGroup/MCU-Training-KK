/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <string>
#include <task.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include "pin_reader.hpp"

void pin_reader_entry(void*, void*, void*);
void uart_publisher_entry(void*, void*, void*);
void led_signaler_entry(void*, void*, void*);

#define THREAD_STACK_SIZE 8192
#define INPUT_PIN 11

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct device * gpiob = DEVICE_DT_GET(DT_NODELABEL(gpiob));
static const struct device * gpiod = DEVICE_DT_GET(DT_NODELABEL(gpiod));

uint32_t input_pin = INPUT_PIN;

k_thread pin_reader, uart_publisher, led_signaler;

k_thread_stack_t pin_reader_stack[THREAD_STACK_SIZE];
k_thread_stack_t uart_publisher_stack[THREAD_STACK_SIZE];
k_thread_stack_t led_signaler_stack[THREAD_STACK_SIZE];

k_pipe led_pipe, uart_pipe;


/**
 * @brief Reads morse input from a pin and publishes the info.
 * 
 * @param p1 Adress of device on which the pin is sampled.
 * @param p2 Adress of first pipe to publish to.
 * @param p3 Adress of second pipe to publish to.
 */
void pin_reader_entry(void* p1, void* p2, void* p3){

	PinReader reader(INPUT_PIN, (const struct device *)p1, (k_pipe*)p2, (k_pipe*)p3);
	reader.Start();

}

void led_signaler_entry(void* p1, void* p2, void* p3){
	return;
}

// void uart_publisher_entry(void* p1, void* p2, void* p3){
// 	return;
// }



int main(void)
{
	k_pipe_init(&led_pipe, NULL, 0);
	k_pipe_init(&uart_pipe, NULL, 0);

	k_thread_create(&pin_reader, pin_reader_stack, THREAD_STACK_SIZE,
	pin_reader_entry, (void*)gpiod, (void*)&led_pipe, (void*)&uart_pipe, 1, K_ESSENTIAL, K_NO_WAIT);

	// k_thread_create(&uart_publisher, uart_publisher_stack, THREAD_STACK_SIZE, 
	// uart_publisher_entry, NULL, NULL, NULL, 1, K_ESSENTIAL, K_NO_WAIT);

	//TODO: ARGS
	k_thread_create(&led_signaler, led_signaler_stack, THREAD_STACK_SIZE,
	led_signaler_entry, NULL, NULL, NULL, 1, K_ESSENTIAL, K_NO_WAIT);

	/*TODO: Schedule/ Start threads if needed?*/

	return 0;
}
