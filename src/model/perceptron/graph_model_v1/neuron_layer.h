#ifndef CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_NEURON_LAYER_H_
#define CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_NEURON_LAYER_H_

#include "neuron.h"
#include <vector>

namespace s21 {

class NeuronLayer {
    public:
        using UInt = unsigned int; 
        NeuronLayer(UInt num_neurons, UInt num_input_in_neuron);

        Neuron &operator[](int i);
        std::size_t size();
        std::vector<float> ComputeOutputs(const std::vector<float>& inputs);
        std::vector<float> CalcError(const std::vector<float>& errors, NeuronLayer& next_layer);
        void UpdateWeights(const std::vector<float>& errors, NeuronLayer& next_layer);
        void UpdateWeights(const std::vector<float>& errors, const std::vector<float>& input_layer);

    private:
        std::vector<Neuron> neurons_;

        float CalcTotalError(const std::size_t &index, const std::vector<float>& errors,  NeuronLayer& next_layer);
};


NeuronLayer::NeuronLayer(UInt num_neurons, UInt num_input_in_neuron) {
    neurons_.reserve(num_neurons);
    for (UInt i = 0; i < num_neurons; ++i) {
        Neuron new_neuron(num_input_in_neuron);
        neurons_.emplace_back(new_neuron);
    }
}

Neuron& NeuronLayer::operator[](int i) {
    return neurons_[i];
}

std::size_t NeuronLayer::size() {
    return neurons_.size();
}

std::vector<float> NeuronLayer::ComputeOutputs(const std::vector<float>& inputs) {
    std::vector<float> vector_outputs;
    vector_outputs.reserve(inputs.size());
    unsigned int index = 0;
    while(index < neurons_.size()) {
        vector_outputs.emplace_back(neurons_[index++].ComputeOutput(inputs));
    }
    return vector_outputs;
}

// delta _{j}=o_{j}(1-o_{j})\sum _{k\in Children(j)}\delta _{k}w_{j,k}}.
std::vector<float> NeuronLayer::CalcError(const std::vector<float>& errors,  NeuronLayer& next_layer) {
    float total_error;
    float new_error;
    std::vector<float> new_errors;
    new_errors.reserve(neurons_.size());
    for (std::size_t i = 0; i < neurons_.size(); ++i) {
        Neuron& neuron = neurons_[i];
        total_error = CalcTotalError(i, errors, next_layer);
        new_error = neuron.GetOutput() * (1 - neuron.GetOutput());
        new_errors.emplace_back(new_error * total_error);
    }
    return new_errors;
}

// sum_{k \in Children(j)} \delta_k w_{jk}
float NeuronLayer::CalcTotalError(const std::size_t &index, const std::vector<float>& errors,  NeuronLayer& next_layer) {
    float total_sum = 0.0;
    for (std::size_t i = 0; i < next_layer.size(); ++i) {
        total_sum = errors[i] * next_layer[i].GetWeight()[index];
    }
    return total_sum;
}

// Delta w_{ij}(n)=\alpha \Delta w_{ij} (n-1) + (1-\alpha)\eta \delta_j o_i`$
// `w_{ij}(n) = w_{ij}(n-1) - \Delta w_{ij}(n)`$,
void NeuronLayer::UpdateWeights(const std::vector<float>& errors, NeuronLayer& next_layer) {
    for (std::size_t i = 0; i < neurons_.size(); ++i) {
        Neuron& neuron = neurons_[i];
        for (std::size_t j = 0; j < next_layer.size(); ++j) {
            Neuron& next_neuron = next_layer[j];
            next_neuron.UpdateWeight(j, errors[j], neuron.GetOutput());
        }
    }
}

void NeuronLayer::UpdateWeights(const std::vector<float>& errors, const std::vector<float>& input_layer) {
    for (std::size_t i = 0; i < neurons_.size(); ++i) {
        for (std::size_t j = 0; j < input_layer.size(); ++j) {
            neurons_[j].UpdateWeight(j, errors[j], input_layer[i]);
        }
    }
}


}  // namespace s21

#endif  // CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_NEURON_LAYER_H_
