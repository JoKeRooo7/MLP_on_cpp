#include "MPL-model.h"

#include <fstream> // file
#include <sstream> // work with string

// #include "buffer/buffer_data.h"
// #include "csv_reader/csv_reader.h"

namespace s21 {

// void MLPModel::StartTrainGraphModel(std::string dataset) {
//     Buffer<CSVReader::DataFormat> &data_buffer = file_reader_.GetBuffer();
//     data.LoadFile(dataset);
//     std::vector
//     // while (buffer.IsOpen() || b) {

//     // }
// }


void MLPModel::LoadFile(const std::string& file_name) {
    CheckExtension(file_name);
    CheckOpenFile(file_name);
    buffer_.Clear();
    ProcessReadLine(file_name);
    LearningProcess(file_name);
}


void MLPModel::CheckExtension(const std::string &file_name) {
    size_t dot_position = file_name.find_last_of(".");
    if (dot_position == std::string::npos) {
        throw std::invalid_argument("No file extension found");
    }

    std::string extension = file_name.substr(dot_position);
    if (extension != ".csv") {
        throw std::invalid_argument("Not .csv");
    }
}

void MLPModel::CheckOpenFile(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    file.close();
}

// void MLPModel::ProcessReadLine(const std::string &file_name) {
//     std::ifstream file(file_name);
//     // if (!file.is_open()) {
//     //     throw std::runtime_error("Failed to open file");
//     // }
//     num_of_line_ = 0;
//     std::string line;
//     while (std::getline(file, line)) {
//         ++num_of_line_;
//     }
// }

void MLPModel::LearningProcess(const std::string &file_name) {
    std::ifstream file(file_name);
    std::string line;
    std::size_t result;
    std::vector<float> data_;
    float temp_value;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> result;
        CheckSeparator(iss);
        while (iss >> temp_value) {
            data_.push_back(temp_value/255);
            CheckSeparator(iss);
        }
        graph_model_.Train(data_, result);
        data_.clear()
    }
}

void MLPModel::CheckSeparator(std::istringstream &iss) {
    if (iss.peek() == ',') {
        iss.ignore();
    }
}
// void CSVReader::ProcessReadFile(const std::string &file_name) {
//     std::ifstream file(file_name);
//     // if (!file.is_open()) {
//     //     throw std::runtime_error("Failed to open file");
//     // }
//     std::string line;
//     float temp_value;
//     DataFormat string_data;
//     while (std::getline(file, line)) {
//         std::istringstream iss(line);
//         iss >> string_data.first;
//         CheckSeparator(iss);
//         while (iss >> temp_value) {
//             string_data.second.push_back(temp_value/255);
//             CheckSeparator(iss);
//         }
//         std::unique_lock<std::mutex> lock(buffer_mutex_);
//         if (!buffer_cv_.wait_for(lock, std::chrono::seconds(response_time_), [this] { 
//                 return buffer_.GetSize() < buffer_.GetMaxBufferSize(); })) {
//             // std::cerr << "close" << std::endl;
//             return;
//         }
//         buffer_.SetData(string_data);
//         string_data.second.clear();
//     }
//     buffer_.Close();
// }



}  // namespace s21
