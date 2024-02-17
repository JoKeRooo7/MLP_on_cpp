#include <cmath>
#include <stdexcept>
#include <gtest/gtest.h>

#include "../../../src/perceptron/graph_model/neuron.h"

const float kEta = 1.e-3;
const float kAlpha = 1.3-1;
const float kEpsilon = 1e-5;

TEST(Neuron, TestCreatingFirstConstructor) {
    s21::Neuron my_neuron(0);
}

TEST(Neuron, Test2CreatingSecondConstructor) {
    s21::Neuron my_neuron(0, kAlpha, kEpsilon);
}

TEST(Neuron, TestGetOutput) {
    s21::Neuron my_neuron(0, kAlpha, kEpsilon);
    EXPECT_NEAR(my_neuron.GetOutput(), 0, kEpsilon);
}

TEST(Neuron, TestEmptyComputeOutput) {
    s21::Neuron my_neuron(0, kAlpha, kEpsilon);
    std::vector<float> empty_vector;
    my_neuron.ComputeOutput(empty_vector);
    EXPECT_NEAR(my_neuron.GetOutput(), 0.5, kEpsilon);
}

TEST(Neuron, TestThrityComputeOutput) {
    s21::Neuron my_neuron(3, kAlpha, kEpsilon);
    std::vector<float> inputs;
    inputs.push_back(0.02);
    inputs.push_back(0.3);
    inputs.push_back(0.005);
    std::vector<float> neuron_weights = my_neuron.GetWeight();
    float need_sum = 0.0;
    need_sum += neuron_weights[0] * inputs[0];
    need_sum += neuron_weights[1] * inputs[1];
    need_sum += neuron_weights[2] * inputs[2];
    need_sum = (1 / (1 + std::exp(-need_sum)));
    EXPECT_NEAR(my_neuron.ComputeOutput(inputs), need_sum, kEpsilon);
}

TEST(Neuron, TestFiveComputeOutput) {
    s21::Neuron my_neuron(5, kAlpha, kEpsilon);
    std::vector<float> inputs;
    inputs.push_back(0.02);
    inputs.push_back(0.3);
    inputs.push_back(0.005);
    inputs.push_back(0.033);
    inputs.push_back(0.333);
    std::vector<float> neuron_weights = my_neuron.GetWeight();
    float need_sum = 0.0;
    need_sum += neuron_weights[0] * inputs[0];
    need_sum += neuron_weights[1] * inputs[1];
    need_sum += neuron_weights[2] * inputs[2];
    need_sum += neuron_weights[3] * inputs[3];
    need_sum += neuron_weights[4] * inputs[4];
    need_sum = (1 / (1 + std::exp(-need_sum)));
    EXPECT_NEAR(my_neuron.ComputeOutput(inputs), need_sum, kEpsilon);
}


TEST(Neuron, UpdateWeight) {
    s21::Neuron my_neuron(5, kAlpha, kEpsilon);
    std::vector<float> inputs;
    std::vector<float> neuron_weights = my_neuron.GetWeight();
    float need_sum = 0.0;
    need_sum += neuron_weights[0] * inputs[0];
    need_sum += neuron_weights[1] * inputs[1];
    need_sum += neuron_weights[2] * inputs[2];
    need_sum += neuron_weights[3] * inputs[3];
    need_sum += neuron_weights[4] * inputs[4];
    need_sum = (1 / (1 + std::exp(-need_sum)));
    EXPECT_NEAR(my_neuron.ComputeOutput(inputs), need_sum, kEpsilon);
}


