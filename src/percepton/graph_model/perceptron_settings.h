#ifndef CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_
#define CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_

namespace s21 {

struct PeceptronSettings {
    using UInt = unsigned short int;

    UInt size_input_layer = 784;
    UInt size_output_layer = 25;
    UInt num_hiden_layers = 0;
    UInt mum_epochs = 3;

    float eta = 0.001; // η - скорость движения (шаг);

    std::vector<UInt> size_layers;
    // std::vector<float> size_layers;
};

}  // namespace s21


#endif  // CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_
