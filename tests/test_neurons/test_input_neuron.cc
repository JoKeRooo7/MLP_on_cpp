#include <cmath>
#include <stdexcept>
#include <gtest/gtest.h>

#include "../../src/model/perceptron/graph_model/layers/neurons/input_neuron.h"


const float kEpsilon = 1e-5;


TEST(InputNeuron, TestCreatingConstructor) {
    s21::InputNeuron my_neuron(nullptr);
}

TEST(InputNeuron, GetEmptyValue) {
    float *empty = nullptr;
    s21::InputNeuron my_neuron(empty);
    EXPECT_THROW(my_neuron.GetOutput(), std::invalid_argument);
}

TEST(InputNeuron, TestGetOutput) {
    float output = 0.5;
    s21::InputNeuron my_neuron(&output);
    EXPECT_NEAR(my_neuron.GetOutput(), output, kEpsilon);
}

TEST(InputNeuron, TestSetOutput1) {
    float output = 0.5;
    s21::InputNeuron my_neuron(nullptr);
    my_neuron.SetOutput(&output);
    EXPECT_NEAR(my_neuron.GetOutput(), output, kEpsilon);
}

TEST(InputNeuron, TestSetOutput2) {
    float output = 0.5;
    float output_two = 0.01;
    s21::InputNeuron my_neuron(&output);
    my_neuron.SetOutput(&output_two);
    EXPECT_NEAR(my_neuron.GetOutput(), output_two, kEpsilon);
}

TEST(InputNeuron, TestForbiddenFunctions1) {
    s21::InputNeuron my_neuron(nullptr);
    EXPECT_THROW(my_neuron.SetDelta(0.5), std::runtime_error);
}

TEST(InputNeuron, TestForbiddenFunctions2) {
    s21::InputNeuron my_neuron(nullptr);
    EXPECT_THROW(my_neuron.ComputeOutput(), std::runtime_error);
}
