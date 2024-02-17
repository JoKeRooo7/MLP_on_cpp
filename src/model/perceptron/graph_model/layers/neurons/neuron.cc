#include "neuron.h"

#include <cmath> // exp
#include <vector>
#include <cstddef> // size_t
#include <stdlib.h> // rand()
#include <stdexcept>


namespace s21 {

Neuron::Neuron(float k_alpha, float eta) : eta_(eta), k_alpha_(k_alpha) {};

float Neuron::GetOutput() const {
    return output_;
}

void Neuron::ComputeOutput() {
    // empty == 0.5? becose not throw in inputs
    float sum = 0.0;
    for (std::size_t i = 0; i < input_links_.size(); ++i) {
        sum += weights_[i] * input_links_[i] -> GetOutput();
    }
    output_ = Sigmoid(sum);
}

float Neuron::GetDelta() {
    return delta_weight_;
}

std::vector<float>& Neuron::GetWeight() {
    return weights_;
}

void Neuron::SetDelta(float delta_weight) {
    delta_weight_ = delta_weight;
}


void Neuron::Connect(AbstractNeuron* element) {
    float weight = ((float)std::rand() / RAND_MAX) * 0.02 - 0.01;
    input_links_.push_back(element);
    weights_.push_back(weight);
    prev_weights_.push_back(0.0);
    delta_prev_weights_.push_back(0.0);
}


void Neuron::UpdateWeight() {
    float d_weight;
    float temp;
    for (std::size_t i = 0; i < input_links_.size(); ++i) {
        d_weight = k_alpha_ * delta_prev_weights_[i];
        d_weight += (1 - k_alpha_) * eta_ * delta_weight_ * input_links_[i] -> GetOutput();
        temp = weights_[i];
        weights_[i] = prev_weights_[i] * d_weight;
        prev_weights_[i] = temp;
        delta_prev_weights_[i] = d_weight;
    }
}

float Neuron::MultDeltaOnWeight(std::size_t i) {
    if (i >= weights_.size()) {
        throw std::invalid_argument("You can't take a weight that doesn't exist.");
    }
    return delta_weight_ * weights_[i];
}

void Neuron::SetOutput([[maybe_unused]] float *input_value) {
    throw std::runtime_error("You cant set output in normal layer");
}

float Neuron::Sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
}


}  // namespace s21