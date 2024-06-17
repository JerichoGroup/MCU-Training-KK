#include "led_signaler.hpp"

LedSignaler::LedSignaler(uint32_t pin, const struct device * dev, k_pipe* p1):
m_pin_number(pin), m_device(dev), m_pipe(p1){}

void LedSignaler::start(){
    std::array<char, morse::MAX_CHARS_WORD> received_word;
    k_msleep(morse::TIME_UNIT / 2);
	gpio_pin_configure(m_device,m_pin_number,GPIO_OUTPUT_ACTIVE);
    while(1){
        k_pipe_get(m_pipe, received_word.data(), morse::MAX_CHARS_WORD,
        NULL, morse::MAX_CHARS_WORD, K_FOREVER);

        _signal_bits_led(morse::english_to_morse(received_word));
    }
}

void LedSignaler::_signal_bits_led(const std::bitset<morse::MAX_BITS_WORD>& bits){
    size_t index = 0;
    size_t remaining = bits.count();
    while (remaining > 0){
        if (bits[index++]){
            --remaining;
            gpio_pin_set(m_device, m_pin_number, 1);
        }   else    {
            gpio_pin_set(m_device, m_pin_number, 0);
        }
        k_msleep(morse::TIME_UNIT);

    }
    for (size_t i = 0 ; i < morse::END_WORD ; ++i){
        gpio_pin_set(m_device, m_pin_number, 0);
        k_msleep(morse::TIME_UNIT);
    }
}

