#include <cmath>
#include <vector>
#include <stdexcept>
#include <gtest/gtest.h>

#include "../../src/model/perceptron/graph_model/layers/input_layer.h"
#include "../../src/model/perceptron/graph_model/layers/neuron_layer.h"

float Sigmoid(float x) {
            return 1 / (1 + std::exp(-x));
}

const float kEta = 1.e-3;
const float kAlpha = 1.3-1;
const float kEpsilon = 1e-5;

TEST(NeuronLayer, TestConstructor) {
    std::size_t size = 3;
    s21::NeuronLayer my_layer(size, kAlpha, kEta);
    EXPECT_EQ(my_layer.size(), size);
}

TEST(NeuronLayer, TestConnection1) {
    std::size_t size = 3;
    s21::InputLayer input_layer(size);
    s21::NeuronLayer my_layer(size, kAlpha, kEta);

    my_layer.ConnectTo(&input_layer);
    EXPECT_NEAR(my_layer[0] -> GetOutput(), 0.0, kEpsilon);
}

TEST(NeuronLayer, TestConnectionAndComputeOutput1) {
    std::size_t size = 3;
    s21::InputLayer input_layer(size);
    s21::NeuronLayer my_layer(size, kAlpha, kEta);

    my_layer.ConnectTo(&input_layer);
    EXPECT_THROW(my_layer[0] -> ComputeOutput(), std::invalid_argument);
    // EXPECT_NEAR(my_layer[0] -> GetOutput(), 0.0, kEpsilon);
    // EXPECT_NEAR(my_layer[1] -> GetOutput(), 0.0, kEpsilon);
}


TEST(NeuronLayer, TestConnectionAndComputeOutput2) {
    std::size_t size = 3;
    s21::InputLayer input_layer(size);
    s21::NeuronLayer my_layer(size, kAlpha, kEta);
    float value_f, value_s, value_th;
    value_f = value_s = value_th = 0.05;
    input_layer[0] -> SetOutput(&value_f);
    input_layer[1] -> SetOutput(&value_s);
    input_layer[2] -> SetOutput(&value_th);

    my_layer.ConnectTo(&input_layer);
    my_layer[0] -> ComputeOutput();

    std::vector<float> &weight_f_neuron = my_layer[0] -> GetWeight(); 
    float result = value_f * weight_f_neuron[0];
    result += value_s * weight_f_neuron[1];
    result += value_th * weight_f_neuron[2];
    result = Sigmoid(result);

    EXPECT_NEAR(my_layer[0] -> GetOutput(), result, kEpsilon);
}

TEST(NeuronLayer, TestUpdateWeight) {
    std::size_t size = 3;
    s21::NeuronLayer my_layer(size, kAlpha, kEta);

    EXPECT_NO_THROW(my_layer.UpdateWeights());
}

TEST(NeuronLayer, CalcTotalSum1) {
    std::size_t size = 3;
    s21::NeuronLayer my_layer(size, kAlpha, kEta);
    s21::NeuronLayer child_layer(size, kAlpha, kEta);

    EXPECT_THROW(my_layer.CalcTotalSum(&child_layer, 0), std::invalid_argument);
    
}

TEST(NeuronLayer, CalcTotalSum2) {
    std::size_t size = 3;
    s21::NeuronLayer my_layer(size, kAlpha, kEta);
    s21::NeuronLayer child_layer(size, kAlpha, kEta);

    child_layer.ConnectTo(&my_layer);

    EXPECT_NEAR(my_layer.CalcTotalSum(&child_layer, 0), 0.0, kEpsilon);
}

TEST(NeuronLayer, CalcTotalSum3) {
    std::size_t size = 3;
    s21::NeuronLayer my_layer(size, kAlpha, kEta);
    s21::NeuronLayer child_layer(size, kAlpha, kEta);

    child_layer.ConnectTo(&my_layer);

    EXPECT_NEAR(my_layer.CalcTotalSum(&child_layer, 0), 0.0, kEpsilon);
}

TEST(NeuronLayer, CalculateAndSetDelta) {
    std::size_t size = 3;
    s21::NeuronLayer my_layer(size, kAlpha, kEta);
    s21::NeuronLayer child_layer(size, kAlpha, kEta);

    child_layer.ConnectTo(&my_layer);

    EXPECT_NO_THROW(my_layer.CalculateAndSetDelta(&child_layer));
}


