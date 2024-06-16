#include "pin_reader.hpp"

PinReader::PinReader(uint32_t pin, const struct device * dev, k_pipe* p1, k_pipe * p2):
	m_pin_number(pin), m_device(dev), m_pipe_1(p1), m_pipe_2(p2){}


void PinReader::start(){
    std::bitset<morse::MAX_BITS_WORD> sequence;
    uint low_count;
    uint index;

    while (1){
        // Retrieve word and then transmit to pipes.
        low_count = 0;
        index = 0;
        sequence.reset();
        while (low_count < morse::END_WORD){
            if(gpio_pin_get(m_device, m_pin_number)){
                for (int i = 0 ; i < low_count ; ++i){
                    sequence[index++] = false;
                }
                low_count = 0;
                sequence[index++] = true;
            }   else{
                ++low_count;
            }
            k_msleep(morse::TIME_UNIT);
        }

        _transmit_word(morse::morse_to_english(sequence));       
    }
}


void PinReader::_transmit_word(const std::array<char, morse::MAX_CHARS_WORD>& word){

    k_pipe_put (m_pipe_1, word.data(), sizeof(char) * morse::MAX_CHARS_WORD,
    NULL, sizeof(char) * morse::MAX_CHARS_WORD, K_MSEC(20));

    //TODO: Transmit to pipe2 as well
}