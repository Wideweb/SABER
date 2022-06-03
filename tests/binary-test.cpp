#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

#include "binary.hpp"

using namespace Saber;

SCENARIO("Binary conversion") {
    GIVEN("One byte positive number") {

        WHEN("Little Endinan") {
            std::stringstream ss;
            to_binary(1, ss, Endian::LITTLE);
            REQUIRE(ss.str() == "00000001 00000000 00000000 00000000");
        }

        WHEN("Big Endinan") {
            std::stringstream ss;
            to_binary(1, ss, Endian::BIG);
            REQUIRE(ss.str() == "00000000 00000000 00000000 00000001");
        }
    }

    GIVEN("Multibyte number positive") {

        WHEN("Little Endinan") {
            std::stringstream ss;
            to_binary(134217728 + 262144 + 512 + 1, ss, Endian::LITTLE);
            REQUIRE(ss.str() == "00000001 00000010 00000100 00001000");
        }

        WHEN("Big Endinan") {
            std::stringstream ss;
            to_binary(134217728 + 262144 + 512 + 1, ss, Endian::BIG);
            REQUIRE(ss.str() == "00001000 00000100 00000010 00000001");
        }
    }

    GIVEN("One byte negative number") {

        WHEN("Little Endinan") {
            std::stringstream ss;
            to_binary(-1, ss, Endian::LITTLE);
            REQUIRE(ss.str() == "11111111 11111111 11111111 11111111");
        }

        WHEN("Big Endinan") {
            std::stringstream ss;
            to_binary(-1, ss, Endian::BIG);
            REQUIRE(ss.str() == "11111111 11111111 11111111 11111111");
        }
    }

    GIVEN("Multibyte negative number") {

        WHEN("Little Endinan") {
            std::stringstream ss;
            to_binary(-(134217728 + 262144 + 512 + 1), ss, Endian::LITTLE);
            REQUIRE(ss.str() == "11111111 11111101 11111011 11110111");
        }

        WHEN("Big Endinan") {
            std::stringstream ss;
            to_binary(-(134217728 + 262144 + 512 + 1), ss, Endian::BIG);
            REQUIRE(ss.str() == "11110111 11111011 11111101 11111111");
        }
    }
}