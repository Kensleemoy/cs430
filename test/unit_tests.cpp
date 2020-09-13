#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"

int yes = 1;
int no = 1;

TEST_CASE("piLeib tests", "[testing]") {
    REQUIRE(yes == 1);
    REQUIRE( no == 0);
}