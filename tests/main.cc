
#include "../src/reader/csv_reader.h"


int main() {
    s21::CSVReader data;
    s21::Buffer<s21::CSVReader::DataFormat>& buffer_data = data.GetBuffer();
    data.LoadFile("../datasets/large_data/emnist-letters-test.csv");
    s21::CSVReader::DataFormat element;
    // while(buffer_data.CheckEnd() != true) {
    std::cout << buffer_data.GetSize() << std::endl;
    if (buffer_data.GetSize() > 0) {
        element = buffer_data.TakeElement();
    }
    while(buffer_data.CheckEnd() != true) {
        if (buffer_data.GetSize() > 0) {
            std::cout << "-start: " << buffer_data.GetSize() << std::endl;
            element = buffer_data.TakeElement();
            std::cout << element.first << ": " << element.second[0] << " ... " << std::endl;
            std::cout << "-end: " << buffer_data.GetSize() << std::endl;
        }
    }
}