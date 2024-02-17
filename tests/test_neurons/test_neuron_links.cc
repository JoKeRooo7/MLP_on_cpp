#include <cmath>
#include <vector>
#include <stdexcept>
#include <gtest/gtest.h>

#include "../../src/model/perceptron/graph_model/layers/neurons/neuron.h"
#include "../../src/model/perceptron/graph_model/layers/neurons/input_neuron.h"


class LinearNeuronSystem : public :: testing::Test {
    public:
        LinearNeuronSystem() : num(0.25), input_data(&num), hidden_neuron(kAlpha, kEta), output(kAlpha, kEta) {}
    protected:
        float num;
        const float kEta = 1.e-3;
        const float kAlpha = 1.3-1;
        const float kEpsilon = 1e-5;
        s21::InputNeuron input_data;
        s21::Neuron hidden_neuron;
        s21::Neuron output;

        float Sigmoid(float x) {
            return 1 / (1 + std::exp(-x));
        }

        void SetUp() override {
            hidden_neuron.Connect(&input_data);
            output.Connect(&hidden_neuron);
        }
};

class VolumeNeuronSystem : public :: testing::Test {
    public:
        VolumeNeuronSystem()
          : num(0.25),
            input_data_one(&num),
            input_data_two(&num),
            hidden_neuron_one(kAlpha, kEta),
            hidden_neuron_two(kAlpha, kEta),
            output_neuron_one(kAlpha, kEta),
            output_neuron_two(kAlpha, kEta) {
        }
    protected:
            float num;
            const float kEta = 1.e-3;
            const float kAlpha = 1.3-1;
            const float kEpsilon = 1e-5;
            s21::InputNeuron input_data_one;
            s21::InputNeuron input_data_two;
            s21::Neuron hidden_neuron_one;
            s21::Neuron hidden_neuron_two;
            s21::Neuron output_neuron_one;
            s21::Neuron output_neuron_two;

        void SetUp() override {
            hidden_neuron_one.Connect(&input_data_one);
            hidden_neuron_one.Connect(&input_data_two);
            hidden_neuron_two.Connect(&input_data_one);
            hidden_neuron_two.Connect(&input_data_two);
            output_neuron_one.Connect(&hidden_neuron_one);
            output_neuron_two.Connect(&hidden_neuron_two);
        }
};


TEST_F(LinearNeuronSystem, TestComputeOutput) {
    std::vector<float> &weigth_hidden_neuron = hidden_neuron.GetWeight();
    std::vector<float> &weigth_output_neuron = output.GetWeight();
    hidden_neuron.ComputeOutput();
    output.ComputeOutput();

    num = Sigmoid(weigth_hidden_neuron[0] * num);
    EXPECT_NEAR(num, hidden_neuron.GetOutput(), kEpsilon);
    num = Sigmoid(weigth_output_neuron[0] * num);
    EXPECT_NEAR(num, output.GetOutput(), kEpsilon);
}

