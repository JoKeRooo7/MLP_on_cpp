#ifndef CPP7_MLP_1_READER_CSV_READER_H_
#define CPP7_MLP_1_READER_CSV_READER_H_


#include "../buffer/buffer_data.h"

#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <chrono> // timer
#include <condition_variable>


#include <fstream> // file
#include <sstream> // string tools
#include <stdexcept> // throw



namespace s21 {


class CSVReader {
    public:
        using UInt = unsigned int;
        using USInt = unsigned short int;
        using DataFormat = std::pair<USInt, std::vector<float>>;

        CSVReader() = default;
        CSVReader(std::string file_name);
        ~CSVReader();

        void LoadFile(const std::string& file_name);
        Buffer<DataFormat>& GetBuffer();

    private:
        USInt response_time_ = 5;
        Buffer<DataFormat> buffer_;

        std::mutex buffer_mutex_;
        std::condition_variable buffer_cv_;
        std::thread read_thread_;

        void CheckExtension(const std::string& file_name);
        void ProcessReadFile(const std::string &file_name);
        void CheckSeparator(std::istringstream &iss);
};


CSVReader::CSVReader(std::string file_name) {
    LoadFile(file_name);
}

CSVReader::~CSVReader() {
    if (read_thread_.joinable()) {
        read_thread_.join();
    }
    buffer_.Close();
}

// typename CSVReader::UInt CSVReader::GetNumLines() {
//     return num_of_line_;
// }

// typename CSVReader::UInt
void CSVReader::LoadFile(const std::string& file_name) {
    CheckExtension(file_name);
    buffer_.Clear();
    // num_of_line_ = 0;
    // std::ifstream file(file_name);
    // if (!file.is_open()) {
    //     throw std::runtime_error("Failed to open file");
    // }
    // num_of_line_ = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    read_thread_ = std::thread(&CSVReader::ProcessReadFile, this, std::ref(file_name));
    // return num_of_line_;
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

void CSVReader::ProcessReadFile(const std::string &file_name) {
    std::ifstream file(file_name);
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


}  // namespace s21


#endif  // CPP7_MLP_1_READER_CSV_READER_H_
