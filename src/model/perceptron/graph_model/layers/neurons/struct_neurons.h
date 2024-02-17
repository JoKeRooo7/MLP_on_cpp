#ifndef CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_STRUCT_NEIRONS_H_
#define CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_STRUCT_NEIRONS_H_

#include <vector>
#include <cstddef>

namespace s21 {

class AbstractNeuron {
    public:
        using UInt = unsigned int;
        virtual void ComputeOutput() = 0;
        virtual void SetOutput(float *input_value) = 0;
        virtual void SetDelta(float nums) = 0;
        virtual float GetOutput() const = 0;
        virtual float MultDeltaOnWeight(std::size_t index) = 0;
        virtual std::vector<float>& GetWeight() = 0;
};

}  // namespace s21 

#endif // CPP7_MLP_2_PERCEPTRON_GRAPH_MODEL_LAYERS_NEURONS_STRUCT_NEIRONS_H_
