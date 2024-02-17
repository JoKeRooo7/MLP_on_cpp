#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <chrono> // timer
#include <condition_variable>

#include <fstream> // file
#include <sstream> // string tools
#include <stdexcept> // throw

#include "csv_reader.h"


namespace s21 {

CSVReader::CSVReader(std::string file_name) {
    LoadFile(file_name);
}

CSVReader::~CSVReader() {
    if (num_line_thread_.joinable()) {
        num_line_thread_.join();
    }
    if (read_thread_.joinable()) {
        read_thread_.join();
    }
    num_of_line_ = 0;
    buffer_.Close();
}

typename CSVReader::UInt CSVReader::GetNumLines() {
    if (num_line_thread_.joinable()) {
        num_line_thread_.join();
    }
    return num_of_line_;
}

void CSVReader::LoadFile(const std::string& file_name) {
    CheckExtension(file_name);
    CheckOpenFile(file_name);
    buffer_.Clear();
    num_line_thread_ = std::thread(&CSVReader::ProcessReadLine, this, std::ref(file_name));
    read_thread_ = std::thread(&CSVReader::ProcessReadFile, this, std::ref(file_name));
}

Buffer<typename CSVReader::DataFormat>& CSVReader::GetBuffer() { 
    return buffer_;
}

void CSVReader::CheckExtension(const std::string &file_name) {
    size_t dot_position = file_name.find_last_of(".");
    if (dot_position == std::string::npos) {
        throw std::invalid_argument("No file extension found");
    }

    std::string extension = file_name.substr(dot_position);
    if (extension != ".csv") {
        throw std::invalid_argument("Not .csv");
    }
}

void CSVReader::CheckOpenFile(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    file.close();
}

void CSVReader::ProcessReadLine(const std::string &file_name) {
    std::ifstream file(file_name);
    // if (!file.is_open()) {
    //     throw std::runtime_error("Failed to open file");
    // }
    num_of_line_ = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++num_of_line_;
    }
}

void CSVReader::ProcessReadFile(const std::string &file_name) {
    std::ifstream file(file_name);
    // if (!file.is_open()) {
    //     throw std::runtime_error("Failed to open file");
    // }
    std::string line;
    float temp_value;
    DataFormat string_data;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> string_data.first;
        CheckSeparator(iss);
        while (iss >> temp_value) {
            string_data.second.push_back(temp_value/255);
            CheckSeparator(iss);
        }
        std::unique_lock<std::mutex> lock(buffer_mutex_);
        if (!buffer_cv_.wait_for(lock, std::chrono::seconds(response_time_), [this] { 
                return buffer_.GetSize() < buffer_.GetMaxBufferSize(); })) {
            // std::cerr << "close" << std::endl;
            return;
        }
        buffer_.SetData(string_data);
        string_data.second.clear();
    }
    buffer_.Close();
}

void CSVReader::CheckSeparator(std::istringstream &iss) {
    if (iss.peek() == ',') {
        iss.ignore();
    }
}

} // namespace s21
