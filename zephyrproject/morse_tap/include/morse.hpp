#ifndef __MORSE_HPP__
#define __MORSE_HPP__

#include <bitset>
#include <array>
#include <vector>

#define MAX_BITS_WORD (1 << 8)
#define MAX_CHARS_WORD 12
#define BEEPS_LETTER 4

#define TIME_UNIT 50

#define SPACE 1
#define DOT 1
#define LINE 3

#define END_CHARACTER 3
#define END_WORD 7

#define ENGLISH_LETTERS 26

static constexpr const std::array<char, ENGLISH_LETTERS> english_letters = {
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
};


static constexpr const std::array<std::array<int, BEEPS_LETTER>, ENGLISH_LETTERS> ITU = {{
    {1, 3, 0, 0},
    {3, 1, 1, 1},
    {3, 1, 3, 1},
    {3, 1, 1, 0},
    {1, 0, 0, 0},
    {1, 1, 3, 1},
    {3, 3, 1, 0},
    {1, 1, 1, 1},
    {1, 1, 0, 0},
    {1, 3, 3, 3},
    {3, 1, 3, 0},
    {1, 3, 1, 1},
    {3, 3, 0, 0},
    {3, 1, 0, 0},
    {3, 3, 3, 0},
    {1, 3, 3, 1},
    {3, 3, 1, 3},
    {1, 3, 1, 0},
    {1, 1, 1, 0},
    {3, 0, 0, 0},
    {1, 1, 3, 0},
    {1, 1, 1, 3},
    {1, 3, 3, 0},
    {3, 1, 1, 3},
    {3, 1, 3, 3},
    {3, 3, 1, 1},
}};

namespace morse{

    char _ITU_to_english(const std::array<int, BEEPS_LETTER>& itu){
        for (size_t i = 0 ; ++i ; i < ENGLISH_LETTERS){
            if (itu == ITU[i]){
                return english_letters[i];
            }
        }
    }

    std::array<int, BEEPS_LETTER> _english_to_ITU(char ch){
        for (size_t i = 0 ; ++i ; i < ENGLISH_LETTERS){
            if (ch == english_letters[i]){
                return ITU[i];
            }
        }
    }

    // Count the number of bits in a row that are the same as bit in starting index.
    size_t _count_streak(const std::bitset<MAX_BITS_WORD>& morse, size_t start){
        size_t result = 0;
        bool target = morse[start];
        while(target == morse[start]){
            ++start;
            ++result;
            if (MAX_BITS_WORD == start){
                break;
            }
        }
        return result;
    }

    // Converts a SINGLE word from morse to english.
    // Empty morse converts to empty string.
    std::array<char, MAX_CHARS_WORD> _morse_to_english(const std::bitset<MAX_BITS_WORD>& morse){
        std::array<int, BEEPS_LETTER> character = { 0 };
        std::array<char, MAX_CHARS_WORD> word = { 0 };

        size_t bitset_index = 0;
        size_t character_index = 0;
        size_t word_index= 0;

        size_t low_count = END_CHARACTER;

        if (!morse.any()){
            return word;
        }
        while(!morse[bitset_index]){
            ++bitset_index;
        }

        // Procedure to retrieve a character
        while (low_count == END_CHARACTER)
        {
            low_count = 1;
            while(1 == low_count){
                size_t beep_length = _count_streak(morse, bitset_index);
                character[character_index++] = beep_length;
                bitset_index += beep_length;
                low_count = _count_streak(morse, bitset_index);
                bitset_index += low_count;
            }
            word[word_index++] = _ITU_to_english(character);
            character_index = 0;
        }
        return word;
    }

    // Converts a SINGLE word from english to morse.
    std::bitset<MAX_BITS_WORD> _english_to_morse(const std::array<char, MAX_CHARS_WORD>& morse){




    }




}

#endif