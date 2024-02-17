#include "input_layer.h"

#include <memory> // std::make_shared
#include <vector>
#include <cstddef>
#include <stdexcept> 


namespace s21 {

InputLayer::InputLayer(std::size_t size) {
    neurons_.reserve(size);
    for (UInt i = 0; i < size; ++i) {
        std::shared_ptr<InputNeuron> new_neuron = std::make_shared<InputNeuron>(nullptr);
        neurons_.emplace_back(new_neuron);
    }
}

std::size_t InputLayer::size() const {
    return neurons_.size();
}

AbstractNeuron* InputLayer::operator[](UInt i) {
    return neurons_[i].get();
}

void InputLayer::ConnectTo([[maybe_unused]]AbstractLayer* prev_layer) {
    throw std::runtime_error("no access in the input layer");
}

void InputLayer::CalculateAndSetDelta([[maybe_unused]]AbstractLayer* child_layer) {
    throw std::runtime_error("no access in the input layer");
}

void InputLayer::UpdateWeights() {
    throw std::runtime_error("no access in the input layer");
}

void InputLayer::ComputeOutputs() {
    throw std::runtime_error("The input data is already ready");
}

}  // namespace s21
