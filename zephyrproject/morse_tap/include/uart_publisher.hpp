#ifndef __UART_PUBLISHER_HPP__
#define __UART_PUBLISHER_HPP__

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>


class UartPublisher
{
public:
    UartPublisher(const struct device * dev, k_msgq* p1);
    ~UartPublisher() = default;

    void callback();
private:
    const struct device * m_dev;
    k_msgq* m_msgq;
};



#endif /* __UART_PUBLISHER_HPP__ */
