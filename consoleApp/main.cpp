#include "binary.hpp"
#include "list.hpp"
#include "mesh-normal.hpp"

#include <iostream>

using namespace Saber;

int main() {
    to_binary(10, std::cout, Endian::LITTLE);
    std::cout << std::endl;

    List list;
    list.push_back("ONE");
    list.push_back("TWO");
    list.push_front("PREONE");

    auto *file = std::fopen("test_data.bin", "wb");
    list.serialize(file);
    std::fclose(file);

    List new_list;
    file = std::fopen("test_data.bin", "rb");
    new_list.deserialize(file);
    std::fclose(file);

    bool is_equal = new_list.size() == 3;
}