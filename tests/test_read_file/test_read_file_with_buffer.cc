#include <queue>
#include <stdexcept>
#include <gtest/gtest.h>

#include "../../src/model/csv_reader/csv_reader.h"



TEST(ReadFile, NotCorrectExtension) {
    s21::CSVReader data;
    EXPECT_THROW(data.LoadFile("csv.h"), std::invalid_argument);
} 

TEST(ReadFile, NotFindFile) {
    s21::CSVReader data;
    EXPECT_THROW(data.LoadFile("main.csv"), std::runtime_error);
}

TEST(ReadFile, WriteOnBuffer) {
    s21::CSVReader data;
    s21::Buffer<s21::CSVReader::DataFormat>& buffer_data = data.GetBuffer();
    // unsigned int num_of_lines = data.LoadFile("../datasets/large_data/emnist-letters-test.csv");
    // EXPECT_EQ(num_of_lines, 14800);
    data.LoadFile("../datasets/emnist-letters-test.csv");
    EXPECT_EQ(data.GetNumLines(), 14800);
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
    data.LoadFile("../datasets/emnist-letters-train.csv");
    EXPECT_EQ(data.GetNumLines(), 88800);
    s21::CSVReader::DataFormat element;
    int j = 0;
    while (buffer_data.IsOpen() || buffer_data.GetSize() > 0) {
        element = buffer_data.TakeElement();
        ++j;
    }
    EXPECT_EQ(element.first, 12);
    EXPECT_EQ(j, data.GetNumLines());
}


TEST(ReadFile, ReadFullDataWithBigDates) {
    s21::CSVReader data;
    s21::Buffer<s21::CSVReader::DataFormat>& buffer_data = data.GetBuffer();
    // unsigned int num_of_lines = data.LoadFile("../datasets/large_data/emnist-letters-train.csv");
    // EXPECT_EQ(num_of_lines, 88800);
    data.LoadFile("../datasets/emnist-letters-train.csv");
    EXPECT_EQ(data.GetNumLines(), 88800);
    s21::CSVReader::DataFormat element;
    int j = 0;
    while (buffer_data.IsOpen() || buffer_data.GetSize() > 0) {
        element = buffer_data.TakeElement();
        for (std::size_t i = 0; i < element.second.size(); ++i)
            for (std::size_t k = 0; k < element.second.size(); ++k);

        ++j;
    }
    EXPECT_EQ(element.first, 12);
    EXPECT_EQ(j, data.GetNumLines());
}