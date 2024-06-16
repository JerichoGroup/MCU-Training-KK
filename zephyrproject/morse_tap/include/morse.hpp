#ifndef __MORSE_HPP__
#define __MORSE_HPP__

#include <bitset>
#include <array>
#include <vector>


namespace morse{

    constexpr const size_t MAX_BITS_WORD = (1 << 8);
    constexpr const size_t MAX_CHARS_WORD = 12;

    constexpr const size_t TIME_UNIT = 50;

    constexpr const size_t SPACE = 1;
    constexpr const size_t DOT = 1;
    constexpr const size_t LINE = 3;

    constexpr const size_t END_CHARACTER = 3;
    constexpr const size_t END_WORD = 7;


    // Converts a SINGLE word from morse to english.
    // Empty morse converts to empty string.
    std::array<char, MAX_CHARS_WORD> morse_to_english(const std::bitset<MAX_BITS_WORD>& morse);

    // Converts a SINGLE word from english to morse.
    std::bitset<MAX_BITS_WORD> english_to_morse(const std::array<char, MAX_CHARS_WORD>& word);


}

#endif