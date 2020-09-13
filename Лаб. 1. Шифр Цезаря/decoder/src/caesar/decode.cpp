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
    bool first = true;
    os << "{";
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

LettersTable CorrelateFrequencies(const FrequencyTable& encoded_table,
                                  const FrequencyTable& original_table) {
    LettersTable encoded_to_original;
    std::set<russian::Utf8Char, russian::Utf8CharCompare> used_original_letters;

    for (const auto& [encoded_ch, encoded_freq] : encoded_table) {
        double min_delta = 100.0;
        russian::Utf8Char matched_ch = encoded_ch;
        for (const auto& [original_ch, original_freq] : original_table) {
            if (used_original_letters.count(original_ch) == 0) {
                const double delta = abs(encoded_freq - original_freq);
                if (delta < min_delta) {
                    min_delta = delta;
                    matched_ch = original_ch;
                }
            }
        }

        encoded_to_original[encoded_ch] = matched_ch;
        used_original_letters.insert(matched_ch);
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
    std::wcout << "\nEncoded frequencies: " << encoded << std::endl;
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
