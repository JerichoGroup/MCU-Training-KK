#include "led_signaler.hpp"

LedSignaler::LedSignaler(uint32_t pin, const struct device * dev, k_msgq* p1):
m_pin_number(pin), m_device(dev), m_msgq(p1),
m_current_word(), m_index(0), m_remaining(0){}


void LedSignaler::callback(){

    if(m_remaining_zeroes > 0){
        gpio_pin_set(m_device, m_pin_number, 0);
        --m_remaining_zeroes;
    }
    else {
        if(m_remaining > 0){
            if (m_current_word[m_index++]){
                --m_remaining;
                gpio_pin_set(m_device, m_pin_number, 1);
            }   else    {
                gpio_pin_set(m_device, m_pin_number, 0);
            }
            if(0 == m_remaining){
                m_remaining_zeroes = morse::END_WORD;
            }
        }   else if(0 == m_remaining)   {
            std::array<char, morse::MAX_CHARS_WORD> received_word = { 0 };
            k_msgq_get(m_msgq, received_word.data(), K_NO_WAIT);
            m_current_word = morse::english_to_morse(received_word);
            m_index = 0;
            m_remaining = m_current_word.count();
        }
    }


}

