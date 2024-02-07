#ifndef CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_
#define CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_


#include "perceptron_settings.h"
#include "Layer.h"

#include <vector>

namespace s21 {


class Percepton {
    public:
        using UInt = unsigned short int;
        Percepton(PeceptronSettings &settings);

        Layer& GetOutputLayer();
        void SetInputLayer(const std::vector<float> &input); 
        void Train(const std::vector<float> &input, UInt need_value);

    private:
        std::vector<float> input_layer_;
        std::vector<Layer> other_layers_;
};

Percepton::Percepton(PeceptronSettings &settings) {
    input_layer_.reserve(settings.size_input_layer);
    other_layer_.reserve(settings.num_hiden_layers + 1);
    UInt size_layer = settings.size_input_layer;
    for (UInt i = 0; i < settings.num_hiden_layers; ++i) {
        Layer new_layer(settings.size_layers[i], size_layer);
        other_layer_.emplace_back(new_layer);
        size_layer = settings.size_layers[i];
    }
    Layer output_layer(settings.output_layer, size_layer)
    other_layer_.emplace_back(output_layer)
}


Layer& Percepton::GetOutputLayer() {
    return layers.back();
}

void Percepton::SetInputLayer(const std::vector<float> &input) {
    
}

void Percepton::Train(const std::vector<float> &input, UInt need_value) {
    
}




} //  namespace s21


#endif  // CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_
