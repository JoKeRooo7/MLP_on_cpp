#ifndef CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_SETTINGS_H_
#define CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_SETTINGS_H_

namespace s21 {

struct PerceptronSettings {
    using UInt = unsigned short int;

    UInt size_input_layer = 784;
    UInt size_output_layer = 28;
    UInt num_hiden_layers = 0;
    UInt num_epochs = 3;

    float k_alpha = 0.1;
    float eta = 0.001;

    std::vector<UInt> size_hidden_layers;
};

}  // namespace s21


#endif  // CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_SETTINGS_H_
