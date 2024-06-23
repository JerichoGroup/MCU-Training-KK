// #include <zephyr/sys_clock.h>

#include <array>
#include <bitset>

#include "pin_reader.hpp"


PinReader::PinReader(uint32_t pin, const struct device * dev, k_msgq* p1, k_msgq * p2):
	m_pin_number(pin), m_device(dev), m_msgq_1(p1), m_msgq_2(p2),
    m_current_word(), m_low_count(0), m_index(0){}


void PinReader::callback(){

    int pin_status = gpio_pin_get(m_device, m_pin_number);
    if(pin_status){
        for (size_t i = 0 ; i < m_low_count ; ++i){
            m_current_word[m_index++] = false;
        }
        m_low_count = 0;
        m_current_word[m_index++] = true;
    }   else{
        ++m_low_count;
    }

    if(morse::END_WORD == m_low_count){
        _transmit_word(morse::morse_to_english(m_current_word));  
        m_current_word.reset();
        m_low_count = 0;
        m_index = 0;     
    }
}


void PinReader::_transmit_word(const std::array<char, morse::MAX_CHARS_WORD>& word){

    k_msgq_put (m_msgq_1, word.data(), K_NO_WAIT);
    k_msgq_put (m_msgq_2, word.data(), K_NO_WAIT);
}