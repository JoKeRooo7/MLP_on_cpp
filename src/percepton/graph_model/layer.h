#ifndef CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_LAYER_H_
#define CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_LAYER_H_

#include "neuron.h"
#include <vector>

namespace s21 {

class Layer {
    public:
        using UInt = unsigned int; 
        Layer(UInt num_neurons, UInt num_input_in_neuron);

        void ComputeOutputs(const std::vector<float>& inputs);
        void UpdateWeights(const std::vector<float>& delta_weights);

    private:
        std::vector<Neuron> neurons_;
};


Layer::Layer(UInt num_neurons, UInt num_input_in_neuron) {
    neurons_.reserve(num_neurons);
    for (UInt i = 0; i < num_neurons; ++i) {
        Neuron new_neuron(num_input_in_neuron);
        neurons_.emplace_back(new_neuron);
    }
}

void Layer::ComputeOutputs(const std::vector<float>& inputs) {
    unsigned int index = 0;
    while(index < neurons_.size()) {
        neurons_[index++].ComputeOutput(inputs);
    }
}

void Layer::UpdateWeight(const std::vector<float>& delta_weights) {
    unsigned int index = 0;
    while(index < neurons_.size()) {
        neurons_[index].UpdateWeight(index, delta_weight[index++]);
    }
}


}  // namespace s21

#endif  // CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_LAYER_H_
