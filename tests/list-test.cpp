#include "catch.hpp"

#include "list.hpp"

const char *c_file = "test_data";

using namespace Saber;

TEST_CASE("list serialization") {

    SECTION("size is preserved after deserialize") {
        List list;
        list.push_back("ONE");
        list.push_back("TWO");
        list.push_front("PREONE");

        auto *file = std::fopen(c_file, "wb");
        list.serialize(file);
        std::fclose(file);

        List new_list;
        file = std::fopen(c_file, "rb");
        new_list.deserialize(file);
        std::fclose(file);

        REQUIRE(new_list.size() == 3);
    }

    SECTION("order is preserved after deserialize") {
        List list;
        list.push_back("ONE");
        list.push_back("TWO");
        list.push_front("PREONE");

        auto *file = std::fopen(c_file, "wb");
        list.serialize(file);
        std::fclose(file);

        List new_list;
        file = std::fopen(c_file, "rb");
        new_list.deserialize(file);
        std::fclose(file);

        auto expected = {"PREONE", "ONE", "TWO"};

        bool is_equal =
            std::equal(expected.begin(), expected.end(), new_list.begin(),
                       [](const std::string &one, const ListNode &two) {
                           return two.data == one;
                       });

        REQUIRE(is_equal);
    }

    SECTION("random elements are preserved after deserialize") {
        List list;
        auto &one = list.push_back("ONE");
        auto &two = list.push_back("TWO");
        auto &preone = list.push_front("PREONE");
        auto &prepreone = list.push_front("PREPREONE");

        one.rand = &prepreone;
        two.rand = &prepreone;
        preone.rand = &one;
        prepreone.rand = &two;

        auto *file = std::fopen(c_file, "wb");
        list.serialize(file);
        std::fclose(file);

        List new_list;
        file = std::fopen(c_file, "rb");
        new_list.deserialize(file);
        std::fclose(file);

        REQUIRE(new_list.find("ONE")->rand ==
                new_list.find("PREPREONE").get_ptr());
        REQUIRE(new_list.find("TWO")->rand ==
                new_list.find("PREPREONE").get_ptr());
        REQUIRE(new_list.find("PREONE")->rand ==
                new_list.find("ONE").get_ptr());
        REQUIRE(new_list.find("PREPREONE")->rand ==
                new_list.find("TWO").get_ptr());
    }
}