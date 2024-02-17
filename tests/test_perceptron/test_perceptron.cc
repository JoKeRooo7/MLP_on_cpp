#include <queue>
#include <stdexcept>
#include <gtest/gtest.h>


#include "../../src/model/perceptron/graph_model/settings.h"
#include "../../src/model/perceptron/graph_model/perceptron.h"

TEST(Perceptron, TestCreating1) {
    s21::PerceptronSettings __settings__;
    EXPECT_NO_THROW(s21::Perceptron my_perceptron(__settings__));
}

TEST(Perceptron, TestCreating2) {
    s21::PerceptronSettings __settings__;
    __settings__.num_hiden_layers = 3;
    __settings__.size_hidden_layers.push_back(300);
    __settings__.size_hidden_layers.push_back(500);
    __settings__.size_hidden_layers.push_back(300);
    EXPECT_NO_THROW(s21::Perceptron my_perceptron(__settings__));
}
