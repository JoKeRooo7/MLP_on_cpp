#ifndef CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_NEURON_LAYER_H_
#define CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_NEURON_LAYER_H_

#include "struct_layers.h"
#include "neurons/struct_neurons.h"
#include "neurons/neuron.h"

#include <cstddef>
#include <vector>
#include <memory> // std::shared_ptr

namespace s21 {

class NeuronLayer : public AbstractLayer {
    public:
        NeuronLayer(std::size_t size, float k_alpha, float eta);

        std::size_t size() const override;
        AbstractNeuron* operator[](UInt i) override;
        void ConnectTo(AbstractLayer* prev_layer) override;
        void UpdateWeights() override;
        void CalculateAndSetDelta(AbstractLayer*  child_layer) override;
        void ComputeOutputs() override;
        float CalcTotalSum(AbstractLayer*  child_layer, std::size_t i);


    private:
        std::vector<std::shared_ptr<Neuron>> neurons_;
};

}  // namespace s21

#endif  // CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_NEURON_LAYER_H_
