#ifndef __PIN_READER_HPP__
#define __PIN_READER_HPP__

#include <bitset>
#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <morse.hpp>


class PinReader
{
public:
	PinReader(uint32_t pin, const struct device * dev, k_msgq* p1, k_msgq * p2);

	~PinReader() = default;

    // Reads bit from input pin, and transmitts a ready word if there is one.
	void callback();

private:
    void _transmit_word(const std::array<char, morse::MAX_CHARS_WORD>& word);

	uint32_t m_pin_number;
	const struct device * m_device;
	k_msgq* m_msgq_1;
	k_msgq* m_msgq_2;

	std::bitset<morse::MAX_BITS_WORD> m_current_word;
	size_t m_low_count;
    size_t m_index;

};


#endif