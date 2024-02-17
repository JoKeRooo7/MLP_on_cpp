#ifndef CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_NEIRON_H_
#define CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_NEIRON_H_

#include <cmath> // exp
#include <vector>
#include <cstddef> // size_t
#include <stdlib.h> // rand()

namespace s21 {


class Neuron {
    public:
        using UInt = unsigned int; 
        Neuron() = default;
        Neuron(unsigned int num_inputs);
        Neuron(unsigned int num_inputs, float k_alpha, float eta);

        float GetOutput() const;
        float ComputeOutput(const std::vector<float>& inputs);
        void UpdateWeight(UInt index, float error, float prev_output);
        std::vector<float>& GetWeight();

    private:
        float output_;
        float k_alpha_ = 0.1;  // α - коэффициент инерциальности(сглаживание);
        float eta_ = 0.001;  // η - скорость движения (шаг);
        std::vector<float> weights_;
        std::vector<float> prev_weights_;
        std::vector<float> delta_prev_weights_;

        float Sigmoid(float x);
};


Neuron::Neuron(unsigned int num_inputs) {
    weights_.resize(num_inputs);
    prev_weights_.resize(num_inputs);
    delta_prev_weights_.resize(num_inputs);
    for(unsigned int i = 0; i < num_inputs; ++мi) {
       weights_[i]= ((float)std::rand() / RAND_MAX) * 0.2 - 0.1;
       prev_weights_[i] = 0.0;
       delta_prev_weights_[i] = 0.0;
    }
    
}

Neuron::Neuron(unsigned int num_inputs, float k_alpha, float eta) : Neuron(num_inputs) {
    k_alpha_ = k_alpha;
    eta_ = eta;
}

float Neuron::GetOutput() const {
    return output_;
}

std::vector<float>& Neuron::GetWeight() {
    return weights_;
}

float Neuron::ComputeOutput(const std::vector<float>& inputs) {
    // empty == 0.5? not throw in inputs
    float sum = 0.0;
    for (std::size_t i = 0; i < weights_.size(); ++i) {
        sum += weights_[i] * inputs[i];
    }
    output_ = Sigmoid(sum);
    return output_;
}

void Neuron::UpdateWeight(UInt index, float error, float prev_output) {
    float delta_weight = k_alpha_ * delta_prev_weights_[index];
    delta_weight += (1 - k_alpha_) * eta_ * error * prev_output;
    delta_prev_weights_[index] = delta_weight;
    float temp = weights_[index];
    weights_[index] = prev_weights_[index] * delta_weight;
    prev_weights_[index] = temp;
}

float Neuron::Sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
}


}  // namespace s21

#endif  // CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_NEIRON_H_
