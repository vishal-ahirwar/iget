
#include <catch2/catch_test_macros.hpp>
#include <path.hpp>

TEST_CASE("Test generatePath function")
{
    generatePath("test/test/test.cpp");
    REQUIRE(std::filesystem::exists("test"));
    REQUIRE(std::filesystem::exists("test/test"));
    generatePath("folder1/folder2/folder3/test.cpp");
    REQUIRE(std::filesystem::exists("folder1"));
    REQUIRE(std::filesystem::exists("folder1/folder2"));
    REQUIRE(std::filesystem::exists("folder1/folder2/folder3"));
    std::filesystem::remove_all("folder1");
    std::filesystem::remove_all("test");
};
