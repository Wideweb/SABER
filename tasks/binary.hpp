#pragma once

#include <cstdint>
#include <ostream>

namespace Saber {

const uint8_t c_bits_in_byte = 8;

enum class Endian { BIG, LITTLE };

Endian get_local_endian();

void decompose_byte(uint8_t byte, std::ostream &out);

void to_binary(int32_t value, std::ostream &out, Endian endian = Endian::LITTLE,
               const char *separator = " ");

} // namespace Saber