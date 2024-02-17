#include "input_neuron.h"

#include <vector>
#include <stdexcept>


namespace s21 {


InputNeuron::InputNeuron(float *input_value) : output_(input_value) {}

void InputNeuron::SetOutput(float *input_value) {
    output_ = input_value; 
}

void InputNeuron::SetDelta([[maybe_unused]] float nums) {
    throw std::runtime_error("You cant set delta in input neorun");
}

void InputNeuron::ComputeOutput() {
    throw std::runtime_error("You cant calculate output in inpur neorun");
}

float InputNeuron::MultDeltaOnWeight([[maybe_unused]] std::size_t index) { 
    return 0.0;
}

float InputNeuron::GetOutput() const { 
    if (output_ == nullptr) {
        throw std::invalid_argument("Empty value in input neuron");
    }
    return *output_; 
}

std::vector<float>& InputNeuron::GetWeight() {
    throw std::runtime_error("Input layer dont have weight");
    static std::vector<float> empty_vector;
    return empty_vector;
}


} // namespace s21
