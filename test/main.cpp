#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

TEST_CASE("Hello, world")
{
    REQUIRE([] { return 42; }() == 42);
}
