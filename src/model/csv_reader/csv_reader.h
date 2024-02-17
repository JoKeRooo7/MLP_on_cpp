#ifndef CPP7_MLP_2_MODEL_READER_CSV_READER_H_
#define CPP7_MLP_2_MODEL_READER_CSV_READER_H_

#include "../buffer/buffer_data.h"

#include <string>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <sstream>


namespace s21 {


class CSVReader {
    public:
        using UInt = unsigned int;
        using USInt = unsigned short int;
        using DataFormat = std::pair<USInt, std::vector<float>>;

        CSVReader() = default;
        CSVReader(std::string file_name);
        ~CSVReader();

        UInt GetNumLines();
        void LoadFile(const std::string& file_name);
        Buffer<DataFormat>& GetBuffer();

    private:
        UInt num_of_line_ = 0;
        USInt response_time_ = 5;
        Buffer<DataFormat> buffer_;

        std::mutex buffer_mutex_;
        std::condition_variable buffer_cv_;
        std::thread num_line_thread_;
        std::thread read_thread_;

        void CheckExtension(const std::string& file_name);
        void CheckOpenFile(const std::string &file_name);
        void ProcessReadLine(const std::string &file_name);
        void ProcessReadFile(const std::string &file_name);
        void CheckSeparator(std::istringstream &iss);
};


}  // namespace s21


#endif  // CPP7_MLP_2_MODEL_READER_CSV_READER_H_
