#include <array>
#include <cstring>

#include <zephyr/drivers/uart.h>

#include "morse.hpp"

#include "uart_publisher.hpp"

UartPublisher::UartPublisher(const struct device * dev, k_msgq* p1):
m_dev(dev), m_msgq(p1) {}

void UartPublisher::callback(){
    std::array<char, morse::MAX_CHARS_WORD> received_word = { 0 };
    k_msgq_get(m_msgq, received_word.data(), K_NO_WAIT);
    size_t length = std::strlen(received_word.data());

    if (length){
        //TODO: PUBLISH RECEIVED WORD IN UART.
        // uart_tx(const struct device *dev, received_word.data(), length,
        //         K_MSEC(morse::TIME_UNIT / 4));
        return;
    }

}