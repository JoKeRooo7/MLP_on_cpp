#ifndef CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_H_
#define CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_H_


#include "settings.h"
#include "layers/struct_layers.h"
#include "layers/neuron_layer.h"

#include <memory>
#include <vector>


namespace s21 {

class Perceptron {
    public:
        using UInt = unsigned short int;
        Perceptron(PerceptronSettings &settings);

        NeuronLayer& GetOutputLayer();
        void SetInputLayer(std::vector<float> &input_layer);
        void Train(std::vector<float> &input_layer, std::size_t output);

    private:
        std::vector<std::shared_ptr<AbstractLayer>> layers_;
    
        void Connections();
        void UpdateOtherDelta();
        void UpdateWeights();
};

} //  namespace s21


#endif  // CPP7_MLP_2_MODEL_PERCEPTRON_GRAPH_MODEL_PERCEPTRON_H_
