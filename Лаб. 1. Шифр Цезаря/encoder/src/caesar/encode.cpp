/**
 * @author: Polyakov Daniil
 * @mail: arjentix@gmail.com
 * @github: Arjentix
 * @date: 10.09.20
 */

#include "encode.h"

#include <utility>
#include <tuple>
#include <fstream>

#include "russian.h"

namespace caesar {

void Encode(const int offset, std::wistream& input, std::wostream& output) {
    while (input) {
        wchar_t ch_1 = input.get();
        if (ch_1 < 128) {
            output << ch_1;
            continue;
        }
        wchar_t ch_2 = input.get();

        if (russian::IsCapitalLetter({ch_1, ch_2})) {
            std::tie(ch_1, ch_2) = russian::NextCapital({ch_1, ch_2}, offset);
        } else if (russian::IsLowerLetter({ch_1, ch_2})) {
            std::tie(ch_1, ch_2) = russian::NextLower({ch_1, ch_2}, offset);
        }

        output << ch_1 << ch_2 << std::flush;
    }
}

} // namespace caesar
