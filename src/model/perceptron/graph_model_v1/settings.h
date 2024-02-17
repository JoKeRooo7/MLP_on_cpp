#ifndef CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_SETTINGS_H_
#define CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_SETTINGS_H_

namespace s21 {

// struct LearningSettings {
//     float eta = 0.001; // η - скорость движения (шаг);
//     float k_alpha = 0.1; // α - коэффициент инерциальности для сглаживания резких скачков при перемещении по поверхности целевой функции
// };

struct PerceptronSettings {
    using UInt = unsigned short int;

    UInt size_input_layer = 784;
    UInt size_output_layer = 28;
    UInt num_hiden_layers = 0;
    UInt mum_epochs = 3;

    std::vector<UInt> size_layers;
    // std::vector<float> size_layers;
};

}  // namespace s21


#endif  // CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_SETTINGS_H_
