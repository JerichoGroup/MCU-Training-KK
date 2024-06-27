#include <array>
#include <cstring>

#include <zephyr/drivers/uart.h>

#include "morse.hpp"

#include "uart_publisher.hpp"

UartPublisher::UartPublisher(const struct device * dev, k_msgq* p1):
m_dev(dev), m_msgq(p1) {
}

// static const struct device * gpiob = DEVICE_DT_GET(DT_NODELABEL(gpiob));

void UartPublisher::callback(){
    std::array<char, morse::MAX_CHARS_WORD> received_word = { 0 };
    k_msgq_get(m_msgq, received_word.data(), K_NO_WAIT);
    size_t length = std::strlen(received_word.data());
    
    for (size_t i = 0; i < length; i++) {
		uart_poll_out(m_dev, received_word.data()[i]);
	}
}