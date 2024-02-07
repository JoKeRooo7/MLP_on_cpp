#include <queue>
#include <stdexcept>
#include <gtest/gtest.h>

#include "../src/reader/csv_reader.h"



TEST(ReadFile, NotCorrectExtension) {
    s21::CSVReader data;
    EXPECT_THROW(data.LoadFile("csv.h"), std::invalid_argument);
} 

// TEST(ReadFile, NotFindFile) {
//     s21::CSVReader data;
//     EXPECT_THROW(data.LoadFile("main.csv"), std::runtime_error);
// }

TEST(ReadFile, WriteOnBuffer) {
    s21::CSVReader data;
    s21::Buffer<s21::CSVReader::DataFormat>& buffer_data = data.GetBuffer();
    // unsigned int num_of_lines = data.LoadFile("../datasets/large_data/emnist-letters-test.csv");
    // EXPECT_EQ(num_of_lines, 14800);
    data.LoadFile("../datasets/large_data/emnist-letters-test.csv");
    s21::CSVReader::DataFormat element;
    element = buffer_data.TakeElement();
    EXPECT_EQ(element.first, 1);
    EXPECT_EQ(element.second[0], 0);
}


TEST(ReadFile, ReadFullData) {
    s21::CSVReader data;
    s21::Buffer<s21::CSVReader::DataFormat>& buffer_data = data.GetBuffer();
    // unsigned int num_of_lines = data.LoadFile("../datasets/large_data/emnist-letters-train.csv");
    // EXPECT_EQ(num_of_lines, 88800);
    data.LoadFile("../datasets/large_data/emnist-letters-train.csv");
    s21::CSVReader::DataFormat element;
    while (buffer_data.IsOpen()) {
        element = buffer_data.TakeElement();
    }
    EXPECT_EQ(element.first, 12);
}
