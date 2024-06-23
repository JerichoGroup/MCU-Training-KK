#ifndef __LED_SIGNALER_HPP_
#define __LED_SIGNALER_HPP_

#include <bitset>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <morse.hpp>

class LedSignaler
{
public:
    LedSignaler(uint32_t pin, const struct device * dev, k_msgq* p1);

    ~LedSignaler() = default;

    // Starts listening to input msgq and publishing to led.
	void callback();

private:

    uint32_t m_pin_number;
	const struct device * m_device;
	k_msgq* m_msgq;

    // Currently signaled word, index in word, remaining 1s,
    // and remaining zeroes to publish after the word.
    std::bitset<morse::MAX_BITS_WORD> m_current_word;
    size_t m_index;
    size_t m_remaining;
    size_t m_remaining_zeroes;
};

#endif /*__LED_SIGNALER_HPP_*/
