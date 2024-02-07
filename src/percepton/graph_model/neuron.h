#ifndef CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_NEIRON_H_
#define CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_NEIRON_H_

#include <cmath> // exp
#include <vector>
#include <cstddef> // size_t
#include <stdlib.h> // rand()


namespace s21 {

float Sigmoid(float x) {
    return 1 / (1 + std::exp(-x));
}

class Neuron {
    public:
        Neuron(unsigned int num_inputs);
    
        float GetOutput() const;
        float ComputeOutput(const std::vector<float>& inputs);
        void UpdateWeight(unsigned int index, float error_weight);

    private:
        float output_;
        // связь с каждым узлом предыдущего члена
        std::vector<float> weights_;
};

Neuron::Neuron(unsigned int num_inputs) {
    weights_.resize(num_inputs);
    for (unsigned int i = 0; i < num_inputs; ++i) {
       weights_[i]= ((float)std::rand() / std::RAND_MAX) * 0.2 - 0.1; // В диапазоне [-0.1, 0.1]
    }
}

float Neuron::GetOutput() const {
    return output_;
}

float Neuron::ComputeOutput(const std::vector<float>& inputs) {
    float sum = 0.0;
    for (std::size_t i = 0; i < weights_.size() ++i) {
        sum += weights_[i] * inputs[i];
    }
    output_ = Sigmoid(sum);
    return output_;
}

void Neuron::UpdateWeight(unsigned int index, float delta_weight) {
    weights_[index] += delta_weight;
}

}  // namespace s21

#endif  // CPP7_MLP_1_PERCEPTRON_GRAPH_MODEL_NEIRON_H_
