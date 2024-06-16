#ifndef __PIN_READER_HPP__
#define __PIN_READER_HPP__

#include <exception>
#include <string>
#include <bitset>
#include <stdint.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <morse.hpp>





static const struct device * gpiob = DEVICE_DT_GET(DT_NODELABEL(gpiob));

class PinReader
{
public:
	PinReader(uint32_t pin, const struct device * dev, k_pipe* p1, k_pipe * p2):
	m_pin_number(pin), m_device(dev), m_pipe_1(p1), m_pipe_2(p2){}

	~PinReader() = default;

    // Starts listening to input pin and publishing to pipes.
	void Start();

private:
    void _transmit_word(const std::string& str);

	uint32_t m_pin_number;
	const struct device * m_device;
	k_pipe* m_pipe_1;
	k_pipe* m_pipe_2;

};

void PinReader::Start(){
    std::bitset<MAX_BITS_WORD> sequence;
    uint low_count;
    uint index;

    while (1){
        // Retrieve word and then transmit to 
        low_count = 0;
        index = 0;
        sequence.reset();
        while (low_count < END_WORD){
            if(gpio_pin_get(m_device, m_pin_number)){
                for (int i = 0 ; i < low_count ; ++i){
                    sequence[index++] = false;
                }
                low_count = 0;
                sequence[index++] = true;
            }   else{
                ++low_count;
            }
            k_msleep(TIME_UNIT);
        }
        // sequence = _morse_to_english(sequence);
        // _transmit_word(sequence);       
    }

}

#endif