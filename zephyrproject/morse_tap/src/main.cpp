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
#include "uart_publisher.hpp"


void pin_reader_entry(k_timer* timer);
void led_signaler_entry(k_timer* timer);
// void uart_publisher_entry(k_timer* timer);

#define THREAD_STACK_SIZE 8192
#define INPUT_PIN 11
#define LED_PIN 13
#define MSGQ_BUFFER_SIZE 8

static const struct device * gpiob = DEVICE_DT_GET(DT_NODELABEL(gpiob));
static const struct device * gpiod = DEVICE_DT_GET(DT_NODELABEL(gpiod));
static const struct device * UART_0 = NULL;//DEVICE_DT_GET(DT_NODELABEL(UART_0));

k_timer pin_read_timer, led_signal_timer, uart_publish_timer;

char uart_msgq_buffer[MSGQ_BUFFER_SIZE * morse::MAX_CHARS_WORD * sizeof(char)];
char led_msgq_buffer[MSGQ_BUFFER_SIZE * morse::MAX_CHARS_WORD * sizeof(char)];
k_msgq led_msgq, uart_msgq;

PinReader reader(INPUT_PIN, gpiob, &led_msgq, &uart_msgq);
LedSignaler signaler(LED_PIN, gpiod, &led_msgq);
UartPublisher publisher(UART_0, &uart_msgq);

/**
 * @brief Reads and records a bit from the input pin.
 * If the bit completes a word then it starts transmitting it.
 * 
 * @param timer The timer for the pin reads.
 */
void pin_reader_callback(k_timer* timer){
	reader.callback();
}

/**
 * @brief toggles a bit using the led if a word is being signaled.
 * Then checks if a new word has been transmitted by the reader.
 * 
 * @param timer The timer for the led signals.
 */
void led_signaler_callback(k_timer* timer){
	signaler.callback();
}
/**
 * @brief Checks for words transmitted by the reader and published them.
 *
 * @param timer The timer for the uart transmittions.
 */
void uart_publisher_callback(k_timer* timer){
	publisher.callback();
}


int main(void)
{
	gpio_pin_configure(gpiod, LED_PIN, GPIO_OUTPUT);
	gpio_pin_configure(gpiob, INPUT_PIN, GPIO_INPUT);

	k_timer_init(&pin_read_timer, pin_reader_callback, NULL);
	k_timer_init(&led_signal_timer, led_signaler_callback, NULL);
	k_timer_init(&uart_publish_timer, uart_publisher_callback, NULL);

	k_msgq_init(&led_msgq, led_msgq_buffer, sizeof(char) * morse::MAX_CHARS_WORD, MSGQ_BUFFER_SIZE);
	k_msgq_init(&uart_msgq, uart_msgq_buffer, sizeof(char) * morse::MAX_CHARS_WORD, MSGQ_BUFFER_SIZE);

	k_timer_start(&pin_read_timer, K_MSEC(morse::TIME_UNIT / 2), K_MSEC(morse::TIME_UNIT));
	k_timer_start(&led_signal_timer, K_MSEC(morse::TIME_UNIT / 2), K_MSEC(morse::TIME_UNIT));
	k_timer_start(&uart_publish_timer, K_MSEC(morse::TIME_UNIT / 2), K_MSEC(morse::TIME_UNIT));	
	
	while(1){}
	
	return 0;
}
