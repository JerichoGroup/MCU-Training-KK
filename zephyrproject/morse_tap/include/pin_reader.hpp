#ifndef __PIN_READER_HPP__
#define __PIN_READER_HPP__

#include <exception>
#include <string>
#include <bitset>
#include <array>
#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <morse.hpp>


class PinReader
{
public:
	PinReader(uint32_t pin, const struct device * dev, k_pipe* p1, k_pipe * p2);

	~PinReader() = default;

    // Starts listening to input pin and publishing to pipes.
	void start();

private:
    void _transmit_word(const std::array<char, morse::MAX_CHARS_WORD>& word);

	uint32_t m_pin_number;
	const struct device * m_device;
	k_pipe* m_pipe_1;
	k_pipe* m_pipe_2;

};


#endif