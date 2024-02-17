#include <cmath>
#include <stdexcept>
#include <gtest/gtest.h>

#include "../../src/model/perceptron/graph_model/layers/input_layer.h"
#include "../../src/model/perceptron/graph_model/layers/neuron_layer.h"

const float kEta = 1.e-3;
const float kAlpha = 1.3-1;
const float kEpsilon = 1e-5;

TEST(InputLayer, TestCreatingEmptyLayer) {
    // std::size_t input = 0;
    // s21::InputLayer my_layer(input);
    s21::InputLayer my_layer(0);
}

TEST(InputLayer, TestCreatingConstructor) {
    std::size_t input = 4;
    s21::InputLayer my_layer(input);

    EXPECT_EQ(my_layer.size(), input);
}

TEST(InputLayer, TestGetValue) {
    std::size_t input = 4;
    s21::InputLayer my_layer(input);

    EXPECT_THROW(my_layer[0] -> GetOutput(), std::invalid_argument);
}

TEST(InputLayer, TestSetGetValue) {
    std::size_t input = 4;
    s21::InputLayer my_layer(input);
    float value = 0.5;
    my_layer[0] -> SetOutput(&value);

    EXPECT_NEAR(my_layer[0] -> GetOutput(), value, kEpsilon);
}

TEST(InputLayer, TestForbiddenFunctions1) {
    std::size_t input = 4;
    s21::InputLayer my_layer(input);
    s21::InputLayer new_layer(input);
    s21::NeuronLayer old_layer(input, kAlpha, kEta);

    EXPECT_THROW(my_layer.ConnectTo(&new_layer), std::runtime_error);
    EXPECT_THROW(my_layer.ConnectTo(&old_layer), std::runtime_error);
}

TEST(InputLayer, TestForbiddenFunctions2) {
    std::size_t input = 4;
    s21::InputLayer my_layer(input);
    s21::InputLayer new_layer(input);
    s21::NeuronLayer old_layer(input, kAlpha, kEta);

    EXPECT_THROW(my_layer.CalculateAndSetDelta(&new_layer), std::runtime_error);
    EXPECT_THROW(my_layer.CalculateAndSetDelta(&old_layer), std::runtime_error);
}

TEST(InputLayer, TestForbiddenFunctions3) {
    std::size_t input = 4;
    s21::InputLayer my_layer(input);

    EXPECT_THROW(my_layer.UpdateWeights(), std::runtime_error);
}
