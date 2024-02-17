#ifndef CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_
#define CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_


#include "settings.h"
#include "neuron_layer.h"

#include <vector>

namespace s21 {


class Perceptron {
    public:
        using UInt = unsigned short int;
        Perceptron(PerceptronSettings &settings);

        NeuronLayer& GetOutputLayer();
        std::vector<float> SetInputLayer(const std::vector<float> &input_layer);
        void Train(const std::vector<float> &input_layer, UInt output_res);

    private:
        std::vector<NeuronLayer> layers_;

        void UpdateWeights(std::vector<float> &errors, const std::vector<float> &input_layer);

};

Perceptron::Perceptron(PeceptronSettings &settings) {
    layers_.reserve(settings.num_hiden_layers + 1);
    UInt size_layer = settings.size_input_layer;
    for (UInt i = 0; i < settings.num_hiden_layers; ++i) {
        NeuronLayer new_layer(settings.size_layers[i], size_layer);
        layers_.emplace_back(new_layer);
        size_layer = settings.size_layers[i];
    }
    NeuronLayer output_layer(settings.size_output_layer, size_layer);
    layers_.emplace_back(output_layer);
}


NeuronLayer& Perceptron::GetOutputLayer() {
    return layers_.back();
}

std::vector<float> Perceptron::SetInputLayer(const std::vector<float> &input_layer) {
    std::vector<float> temp_output = layers_[0].ComputeOutputs(input_layer);
    for (UInt i = 1; i < layers_.size(); ++i) {
        temp_output = layers_[i].ComputeOutputs(temp_output);
    }
    return temp_output;
}

void Perceptron::Train(const std::vector<float> &input_layer, UInt output_res) {
    std::vector<float> output = SetInputLayer(input_layer);
    std::vector<float> errors;
    float delta;
    errors.reserve(output.size());
    for (UInt k = 0; k < output.size(); ++k) {
        if (k == output_res - 1) {
            delta = -output[k] * (1 - output[k]) * (1.0 - output[k]);
        } else {
            delta = -output[k] * (1 - output[k]) * (0.0 - output[k]);
        }
        errors.emplace_back(delta);
    }
    UpdateWeights(errors, input_layer);
}

void Perceptron::UpdateWeights(std::vector<float> &errors, const std::vector<float> &input_layer) {
    for (int l = layers_.size() - 2; l >= 0; --l) {
        layers_[l].UpdateWeights(errors, layers_[l + 1]);
        errors = layers_[l].CalcError(errors, layers_[l + 1]);
    }
    layers_[0].UpdateWeights(errors, input_layer);
}


} //  namespace s21


#endif  // CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_SETTINGS_H_
