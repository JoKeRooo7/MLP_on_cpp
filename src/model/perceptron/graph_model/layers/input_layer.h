#ifndef CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_INPUT_LAYER_H_
#define CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_INPUT_LAYER_H_

#include "struct_layers.h"
#include "neurons/struct_neurons.h"
#include "neurons/input_neuron.h"

#include <cstddef> // std::size_t
#include <vector>
#include <memory> // std::shared_ptr


namespace s21 {

class InputLayer : public AbstractLayer {
    public:
        InputLayer(std::size_t size);

        std::size_t size() const override;
        AbstractNeuron* operator[](UInt i) override;
        
        void ConnectTo([[maybe_unused]]AbstractLayer* prev_layer) override;
        void CalculateAndSetDelta([[maybe_unused]]AbstractLayer* child_layer) override;
        void UpdateWeights() override;
        void ComputeOutputs() override;

    private:
        std::vector<std::shared_ptr<InputNeuron>> neurons_;
};



} // namespace s21

#endif //  CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_INPUT_LAYER_H_
