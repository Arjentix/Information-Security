/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 13.09.2020
 */

#include "decode.h"

#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>

#include "russian.h"

namespace {

using FrequencyTable = std::map<russian::Utf8Char, double, russian::Utf8CharCompare>;
using LettersTable = std::map<russian::Utf8Char, russian::Utf8Char, russian::Utf8CharCompare>;

std::wostream& operator<<(std::wostream& os, const russian::Utf8Char& ch) {
    os << ch.first << ch.second << std::flush;
    return os;
}

template <typename T, typename U, typename C>
std::wostream& operator<<(std::wostream& os, const std::map<T, U, C>& m) {
    os << "{";
    bool first = true;
    for (const auto& [key, value] : m) {
        if (!first) {
            os << ", ";
        }
        os << key << ": " << value;
        first = false;
    }
    os << "}";

    return os;
}

/**
 * @brief   Gets table with frequency for every letter
 * 
 * @param   intput  input stream
 * 
 * @return  map with russian letter as key and percentage as value
 */
FrequencyTable GetFrequencyTable(std::wistream& input) {
    FrequencyTable table;
    int total_chars = 0;

    while (input) {
        russian::Utf8Char ch;
        input.get(ch.first);
        if (ch.first < 128) {
            continue;
        }
        input.get(ch.second);

        if (russian::IsCapitalLetter(ch) || russian::IsLowerLetter(ch)) {
            ++total_chars;
            ++table[russian::ToLower(ch)];
        }
    }

    for (auto& [ch, freq] : table) {
        freq = freq / total_chars * 100;
    }

    return table;
}

/**
 * @brief   Mathces encoded letter with original using frequency analysis
 * 
 * @param   encoded_letter  letter, encoded with caesar cipher
 * @param   encoded_freq    frequency of appearing encoded_letter in encoded_text
 * @param   original_table  table of frequencies of letters in not encrypted text
 * 
 * @return  matched letter from original_table
 */
russian::Utf8Char MatchLetter(const russian::Utf8Char& encoded_letter,
                              double encoded_freq,
                              const FrequencyTable& original_table) {
    double min_delta = 100.0;
    russian::Utf8Char match = encoded_letter;

    for (const auto& [original_letter, original_freq] : original_table) {
        const double delta = abs(encoded_freq - original_freq);
        if (delta < min_delta) {
            min_delta = delta;
            match = original_letter;
        }
    }

    return match;
}

/**
 * @brief   Compares to tables and mathes encoded letter to the original
 * 
 * @param   encoded_table   table with encoded letters frequencies
 * @param   original_table  table with original letters frequencies
 * 
 * @return  map with encoded letter as key and decoded letter as value
 */
LettersTable CorrelateFrequencies(const FrequencyTable& encoded_table,
                                  FrequencyTable original_table) {
    LettersTable encoded_to_original;
    std::map<int, int> key_to_frequency;

    for (const auto& [encoded_ch, encoded_freq] : encoded_table) {
        russian::Utf8Char matched_ch = MatchLetter(encoded_ch, encoded_freq, original_table);
        original_table.erase(matched_ch);

        const int diff = russian::Diff(encoded_ch, matched_ch);
        const int sign = diff > 0 ? 1 : -1;
        std::wcout << L"Diff between " << encoded_ch << L" and " << matched_ch << " = " << diff << std::endl;
        ++key_to_frequency[diff];
        ++key_to_frequency[sign*(std::abs(diff) - 32)];
    }

    auto it = std::max_element(key_to_frequency.begin(), key_to_frequency.end(),
        [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
            return lhs.second < rhs.second;
        }
    );
    const int key = it->first;
    std::cout << "🔑 Key = " << key << std::endl;

    for (const auto& [encoded_ch, encoded_freq] : encoded_table) {
        encoded_to_original[encoded_ch] = russian::PrevLower(encoded_ch, -key);
    }

    return encoded_to_original;
}

} // namespace

namespace caesar {

void Decode(std::wistream& stats_input, std::wistream& input,
            std::wostream& output) {
    std::wstringstream input_copy; // Need if input is std::wcin
    input_copy << input.rdbuf();

    FrequencyTable original = GetFrequencyTable(stats_input);
    std::wcout << "Original frequencies: " << original << std::endl;
    FrequencyTable encoded  = GetFrequencyTable(input_copy);
    std::wcout << "\nEncoded frequencies: " << encoded << "\n" << std::endl;
    LettersTable encoded_to_original = CorrelateFrequencies(encoded, original);
    std::wcout << "\nEncoded to original: " << encoded_to_original << "\n" << std::endl;

    input_copy.clear();
    input_copy.seekg(0);
    while (input_copy) {
        russian::Utf8Char ch;
        input_copy.get(ch.first);
        if (ch.first < 128) {
            output << ch.first;
            continue;
        }
        input_copy.get(ch.second);

        if (russian::IsCapitalLetter(ch)) {
            russian::Utf8Char replacement = russian::ToCapital(encoded_to_original.at(russian::ToLower(ch)));
            output << replacement.first << replacement.second << std::flush;
        } else if (russian::IsLowerLetter(ch)) {
            russian::Utf8Char replacement = encoded_to_original.at(russian::ToLower(ch));
            output << replacement.first << replacement.second << std::flush;
        }
    }
}


} // namespace caesar
