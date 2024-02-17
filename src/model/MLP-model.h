#ifndef CPP7_MLP_2_MODEL_MLP_MODEL_H_
#define CPP7_MLP_2_MODEL_MLP_MODEL_H_

#include "csv_reader/csv_reader.h"
#include "perceptron/graph_model/perceptron.h"

#include <vector>
#include <string>
#include <sstream>

namespace s21 {

class MLPModel {
    public:
        // MLPModel();

        

        // void StartTrainGraphModel(std::string detaset);
        // void 
    private:
        Perceptron graph_model_;
        CSVReader file_reader_;

        void LoadFile(const std::string& file_name);
        void CheckExtension(const std::string& file_name);
        void CheckOpenFile(const std::string &file_name);

        void ProcessReadLine(const std::string &file_name);
        void LearningProcess(const std::string &file_name);
        void CheckSeparator(std::istringstream &iss);
};

}  // namespace s21

#endif  // CPP7_MLP_2_MODEL_MLP_MODEL_H_
