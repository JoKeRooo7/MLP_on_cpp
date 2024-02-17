#ifndef CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_NEURON_H_
#define CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_NEURON_H_

#include "struct_neurons.h"

#include <vector>

namespace s21 {

class Neuron : public AbstractNeuron {
    public:
        Neuron(float k_alpha, float eta);

        virtual float GetOutput() const override;
        virtual void ComputeOutput() override;

        float GetDelta();
        std::vector<float>& GetWeight() override;
        
        virtual void SetDelta(float delta_weight) override;
        void Connect(AbstractNeuron* element);
        void UpdateWeight();
        virtual float MultDeltaOnWeight(std::size_t i) override;
        void SetOutput(float *input_value) override;

    private:
        float eta_;
        float output_;
        float k_alpha_;
        float delta_weight_ = 0.0; // error 
        std::vector<float> weights_;
        std::vector<float> prev_weights_;
        std::vector<float> delta_prev_weights_;
        std::vector<AbstractNeuron*> input_links_;

        float Sigmoid(float x);

};


}  // namespace s21

#endif  // CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_NEURON_H_
