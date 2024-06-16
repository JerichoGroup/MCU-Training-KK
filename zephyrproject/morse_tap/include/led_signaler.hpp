#ifndef __LED_SIGNALER_HPP_
#define __LED_SIGNALER_HPP_

#include <array>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <morse.hpp>

class LedSignaler
{
public:
    LedSignaler(uint32_t pin, const struct device * dev, k_pipe* p1);
    ~LedSignaler() = default;

    // Starts listening to input pipe and publishing to led.
	void start();

private:
    void _signal_bits_led(const std::bitset<morse::MAX_BITS_WORD>& bits);

    uint32_t m_pin_number;
	const struct device * m_device;
	k_pipe* m_pipe;
    //std::queue<std::array<char, morse::MAX_CHARS_WORD>> m_queue;
};

#endif /*__LED_SIGNALER_HPP_*/
