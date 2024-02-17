#include <memory>
#include <vector>
#include <stdexcept>

#include "layers/struct_layers.h"
#include "layers/neuron_layer.h"
#include "layers/input_layer.h"
#include "perceptron.h"


namespace s21 {

NeuronLayer& Perceptron::GetOutputLayer() {
    AbstractLayer* abstract_layer = layers_.back().get();
    NeuronLayer* neuron_layer = dynamic_cast<NeuronLayer*>(abstract_layer);
    if (!neuron_layer) {
        throw std::runtime_error("Empty output layer");
    } else {
       return *neuron_layer;
    }
}

Perceptron::Perceptron(PerceptronSettings &settings) {
    layers_.reserve(2 + settings.num_hiden_layers);
    layers_.emplace_back(std::make_shared<InputLayer>(settings.size_input_layer));
    for (UInt i = 0; i < settings.num_hiden_layers; ++i) {
        if (i >= settings.size_hidden_layers.size()) {
            throw std::runtime_error("Dont have size in hidden layer");
        }
        layers_.emplace_back(std::make_shared<NeuronLayer>(settings.size_hidden_layers[0], settings.k_alpha, settings.eta));
    }
    layers_.emplace_back(std::make_shared<NeuronLayer>(settings.size_output_layer, settings.k_alpha, settings.eta));
    Connections();
}

void Perceptron::Connections() {
    for (std::size_t i = 1; i < layers_.size(); ++i) {
        layers_[i] -> ConnectTo(layers_[i - 1].get());
    }
}

void Perceptron::SetInputLayer(std::vector<float> &input_layer) {
    if (input_layer.size() != layers_[0] -> size()) {
        throw std::invalid_argument("Not valid dates");
    }
    for (UInt i = 0; i < layers_[0] -> size(); ++i) {
            (*layers_[0])[i] -> SetOutput(&input_layer[i]);
    }
    for (std::size_t i = 1; i < layers_.size(); ++i) {
        layers_[i] -> ComputeOutputs();
    }
}

void Perceptron::Train(std::vector<float> &input_layer, std::size_t output) {
    SetInputLayer(input_layer);
    float delta;
    float out_neuron;
    NeuronLayer& out_layer = GetOutputLayer();
    for (std::size_t k = 0; k < out_layer.size(); ++k) {
        out_neuron = out_layer[k] -> GetOutput();
        if (k == output - 1) {
            delta = -out_neuron * (1 - out_neuron) * (1.0 - out_neuron);
        } else {
            delta = -out_neuron * (1 - out_neuron) * (0.0 - out_neuron);
        }
        out_layer[k] -> SetDelta(delta);
    }
    UpdateOtherDelta();
    UpdateWeights();
}


void Perceptron::UpdateOtherDelta() {
    for (int l = layers_.size() - 2; l >= 0; --l) {
        layers_[l] -> CalculateAndSetDelta(&(*layers_[l + 1]));
    }
}

void Perceptron::UpdateWeights() {
    // if l == 1, W{0,1}
    for (UInt l = 1; l < layers_.size(); ++l) {
        layers_[l] -> UpdateWeights();
    }
}


}  // namespace s21