/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <string>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include "pin_reader.hpp"
#include "led_signaler.hpp"


void pin_reader_entry(void*, void*, void*);
void uart_publisher_entry(void*, void*, void*);
void led_signaler_entry(void*, void*, void*);

#define THREAD_STACK_SIZE 8192
#define INPUT_PIN 11
#define LED_PIN 13

static const struct device * gpiob = DEVICE_DT_GET(DT_NODELABEL(gpiob));
static const struct device * gpiod = DEVICE_DT_GET(DT_NODELABEL(gpiod));



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
	reader.start();
}

void led_signaler_entry(void* p1, void* p2, void* p3){
	LedSignaler signaler(LED_PIN, (const struct device *)p1, (k_pipe*)p2);
	signaler.start();
}

// TODO: void uart_publisher_entry(void* p1, void* p2, void* p3){
// 	return;
// }

int main(void)
{
	k_tid_t pin_reader_id;
	k_tid_t led_signaler_id;
	k_pipe_init(&led_pipe, NULL, 0);
	k_pipe_init(&uart_pipe, NULL, 0);

	pin_reader_id = k_thread_create(&pin_reader, pin_reader_stack, THREAD_STACK_SIZE,
	pin_reader_entry, (void*)gpiob, (void*)&led_pipe, (void*)&uart_pipe, 0, K_ESSENTIAL, K_NO_WAIT);

	// TODO: k_thread_create(&uart_publisher, uart_publisher_stack, THREAD_STACK_SIZE, 
	// uart_publisher_entry, ???, (void*)&uart_pipe, NULL, 1, K_ESSENTIAL, K_NO_WAIT);

	// led_signaler_id = k_thread_create(&led_signaler, led_signaler_stack, THREAD_STACK_SIZE,
	// led_signaler_entry, (void*)gpiod, (void*)&led_pipe, NULL, 1, K_ESSENTIAL, K_NO_WAIT);


	// std::bitset<22> sig;
	// sig[1] = true;
	// sig[3] = true;
	// sig[5] = true;
	// sig[7] = true;
	// sig[11] = true;
	// sig[13] = true;
	// for (size_t i = 0 ; i < 21 ; ++i){
	// 	gpio_pin_configure(gpiod,LED_PIN,GPIO_OUTPUT_ACTIVE);
	// 	gpio_pin_set(gpiod,LED_PIN,sig[i]);
    //     k_msleep(morse::TIME_UNIT);
	// }
	k_thread_join(&pin_reader, K_FOREVER);
	k_thread_join(&led_signaler, K_FOREVER);
	return 0;
}
