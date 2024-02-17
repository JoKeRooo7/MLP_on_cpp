#ifndef CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_INPUT_NEURON_H_
#define CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_INPUT_NEURON_H_

#include "struct_neurons.h"

#include <vector>

namespace s21 {

class InputNeuron : public AbstractNeuron {
    public:
        InputNeuron(float *input_value);

        void SetOutput(float *input_value) override;
        void SetDelta(float nums) override;
        void ComputeOutput() override;
        float MultDeltaOnWeight(std::size_t index) override;
        float GetOutput() const override;
        std::vector<float>& GetWeight() override;


    private:
        float *output_;
};

} //  namespace s21

#endif // CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_INPUT_NEURON_H_
