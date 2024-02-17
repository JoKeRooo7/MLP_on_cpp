#include "neuron_layer.h"

#include <cstddef>
#include <vector>
#include <memory> // std::make_shared

namespace s21 {

NeuronLayer::NeuronLayer(std::size_t size, float k_alpha, float eta) {
    neurons_.reserve(size);
    for (UInt i = 0; i < size; ++i) {
        std::shared_ptr<Neuron> new_neuron = std::make_shared<Neuron>(k_alpha, eta);
        neurons_.emplace_back(new_neuron);
    }
}

std::size_t NeuronLayer::size() const {
    return neurons_.size();
}

AbstractNeuron* NeuronLayer::operator[](UInt i) {
    return neurons_[i].get();
}

void NeuronLayer::ConnectTo(AbstractLayer* prev_layer) {
    for (UInt i = 0; i < neurons_.size(); ++i) {
        for (UInt j = 0; j < prev_layer -> size(); ++j) {
            neurons_[i] -> Connect((*prev_layer)[j]);
        }
    }
}

void NeuronLayer::ComputeOutputs() {
    for (UInt i = 0; i < neurons_.size(); ++i) {
        neurons_[i] -> ComputeOutput();
    }
}

void NeuronLayer::CalculateAndSetDelta(AbstractLayer*  child_layer) {
    float delta;
    float out_neuron;
    for (std::size_t i = 0; i < neurons_.size(); ++i) {
        out_neuron = neurons_[i] -> GetOutput();
        delta = out_neuron * (1 - out_neuron) * CalcTotalSum(child_layer, i);
        neurons_[i] -> SetDelta(delta);
    }
}

float NeuronLayer::CalcTotalSum(AbstractLayer*  child_layer, std::size_t i) {
    float total_sum = 0.0;
    for (std::size_t j = 0; j < child_layer -> size(); ++j) {
        total_sum += (*child_layer)[j] -> MultDeltaOnWeight(i);
    }
    return total_sum;
}

void NeuronLayer::UpdateWeights() {
    for (std::size_t j = 0; j < neurons_.size(); ++j) {
        neurons_[j] -> UpdateWeight();
    }
}


}  // namespace s21
