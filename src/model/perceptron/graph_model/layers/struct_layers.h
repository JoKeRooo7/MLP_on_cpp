#ifndef CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_STRUCT_LAYERS_H_
#define CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_STRUCT_LAYERS_H_

#include "neurons/struct_neurons.h"
#include <cstddef>

namespace s21 {

class AbstractLayer {
    public:
        using UInt = unsigned int;

        virtual std::size_t size() const = 0;
        virtual AbstractNeuron* operator[](UInt i) = 0;
        virtual void ConnectTo(AbstractLayer* prev_layer) = 0;
        virtual void CalculateAndSetDelta(AbstractLayer* child_layer) = 0;
        virtual void UpdateWeights() = 0;
        virtual void ComputeOutputs() = 0;
};

}  // namespace s21

#endif  // CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYER_STRUCT_LAYERS_H_
