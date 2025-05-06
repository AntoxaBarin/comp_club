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


TEST_F(TestClub, UserLeavingAtClosingTest) {
    std::streambuf* oldCoutBuffer = std::cout.rdbuf();
    std::stringstream capturedOutput;
    std::cout.rdbuf(capturedOutput.rdbuf());

    const std::string input_file_path = "../test/test_data/test_1_input.txt";
    const std::string expected_file_path = "../test/test_data/test_1_expected.txt"; 

    comp_club::simulate(input_file_path);

    std::cout.rdbuf(oldCoutBuffer);
    EXPECT_EQ(capturedOutput.str(), readFileToString(expected_file_path));
}

} // namespace test
