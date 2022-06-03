#include "binary.hpp"

namespace Saber {

Endian get_local_endian() {
    uint16_t x = 0x0001;
    return *(reinterpret_cast<uint8_t *>(&x)) ? Endian::LITTLE : Endian::BIG;
}

void decompose_byte(uint8_t byte, std::ostream &out) {
    for (size_t i = c_bits_in_byte; i > 0; i--) {
        out << ((byte >> (i - 1)) & 1);
    }
}

void to_binary(int32_t value, std::ostream &out, Endian endian,
               const char *separator) {
    size_t bytes_number = sizeof(value);

    bool swap_endian = get_local_endian() != endian;

    for (size_t i = 0; i < bytes_number; i++) {
        size_t byte_index = swap_endian ? bytes_number - (i + 1) : i;
        size_t shift = byte_index * c_bits_in_byte;
        uint8_t byte = (value >> shift) & 0xff;

        decompose_byte(byte, out);

        if (i != bytes_number - 1) {
            out << separator;
        }
    }
}

} // namespace Saber