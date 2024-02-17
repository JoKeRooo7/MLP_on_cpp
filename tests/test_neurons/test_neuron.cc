#include <cmath>
#include <vector>
#include <stdexcept>
#include <gtest/gtest.h>

#include "../../src/model/perceptron/graph_model/layers/neurons/neuron.h"

const float kEta = 1.e-3;
const float kAlpha = 1.3-1;
const float kEpsilon = 1e-5;


TEST(Neuron, TestCreatingConstructor) {
    s21::Neuron my_neuron(kAlpha, kEta);
}

TEST(Neuron, TestGetOutput) {
    s21::Neuron my_neuron(kAlpha, kEta);
    EXPECT_NEAR(my_neuron.GetOutput(), 0, kEpsilon);
}

TEST(Neuron, TestEmptyComputeOutput) {
    s21::Neuron my_neuron(kAlpha, kEta);
    my_neuron.ComputeOutput();
    EXPECT_NEAR(my_neuron.GetOutput(), 0.5, kEpsilon);
}

TEST(Neuron, TestConnect1) {
    s21::Neuron main_neuron(kAlpha, kEta);
    s21::Neuron child_neuron(kAlpha, kEta);
    s21::Neuron parent_neuron(kAlpha, kEta);
   
    main_neuron.Connect(&parent_neuron);
    child_neuron.Connect(&main_neuron);
    EXPECT_EQ(main_neuron.GetWeight().size(), 1);
    EXPECT_EQ(child_neuron.GetWeight().size(), 1);
    EXPECT_EQ(parent_neuron.GetWeight().size(), 0);
}

TEST(Neuron, TestConnect2) {
    s21::Neuron main_neuron(kAlpha, kEta);
    s21::Neuron parent_neuron_one(kAlpha, kEta);
    s21::Neuron parent_neuron_two(kAlpha, kEta);
    s21::Neuron parent_neuron_three(kAlpha, kEta);
    
    main_neuron.Connect(&parent_neuron_one);
    main_neuron.Connect(&parent_neuron_two);
    main_neuron.Connect(&parent_neuron_three);
    EXPECT_EQ(main_neuron.GetWeight().size(), 3);
}


TEST(Neuron, TestGetSetDelta) {
    float delta = 0.1134;
    s21::Neuron main_neuron(kAlpha, kEta);
    EXPECT_NEAR(main_neuron.GetDelta(), 0.0, kEpsilon);
    main_neuron.SetDelta(delta);
    EXPECT_NEAR(main_neuron.GetDelta(), delta, kEpsilon);
}

TEST(Neuron, TestForbiddenFunctions1) {
    s21::Neuron main_neuron(kAlpha, kEta);
    float num = 0.1;
    EXPECT_THROW(main_neuron.SetOutput(&num), std::runtime_error);
}
