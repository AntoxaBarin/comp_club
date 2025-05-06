#include <gtest/gtest.h>

#include <fstream>

#include "../source/simulation.hpp"

namespace test {

class TestClub : public testing::Test {
public:
    void TearDown() override {};
    void SetUp() override {};
};

static std::string readFileToString(const std::string& filePath) {
    std::ifstream in(filePath);
    if (!in.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

static void runTest(int test_num) {
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::stringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());

    const std::string input_file_path = "../test/test_data/test_" + std::to_string(test_num) + "_input.txt";
    const std::string expected_file_path = "../test/test_data/test_" + std::to_string(test_num) + "_expected.txt"; 

    comp_club::simulate(input_file_path);

    std::cout.rdbuf(oldCoutBuffer);
    EXPECT_EQ(capturedOutput.str(), readFileToString(expected_file_path));
}


TEST_F(TestClub, UserLeavingAtClosingTest) {
    runTest(1);
}

TEST_F(TestClub, CorrectMoneyPerComputerTest) {
    runTest(2);
}

TEST_F(TestClub, CorrectComputerChangeTest) {
    runTest(3);
}

TEST_F(TestClub, QueueTest) {
    runTest(4);
}

TEST_F(TestClub, TaskExampleInputTest) {
    runTest(5);
}

TEST_F(TestClub, PlaceIsBusyTest) {
    runTest(6);
}

TEST_F(TestClub, OneMinuteUsersTest) {
    runTest(7);
}

TEST_F(TestClub, YouShallNotPassTest) {
    runTest(8);
}

TEST_F(TestClub, NoEventsTest) {
    runTest(9);
}

TEST_F(TestClub, ICanWaitNoLongerTest) {
    runTest(10);
}

} // namespace test
