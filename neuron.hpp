#ifndef NEURON_HPP
#define NEURON_HPP

#include <random>
#include <cmath>
#include "matrix.hpp"

template<size_t inputs, size_t hiddens, size_t outputs>
struct Network{

    Matrix<hiddens, inputs> hidden_weights;
    Matrix<outputs, hiddens> output_weights;
    float learning_rate;

    Network(float rate) : learning_rate(rate){
        std::random_device rd;
        std::mt19937 gen(rd());
        float min = -1/(std::sqrt(static_cast<float>(inputs)));
        float max = +1/(std::sqrt(static_cast<float>(inputs)));
        std::uniform_real_distribution<float> distr(min, max);
        
        for(size_t i = 0; i < hiddens ; i++){
            for(size_t j = 0; j < inputs; j++){
                hidden_weights.m_matrix[i][j] = distr(gen);
            }
        }

        for(size_t i = 0; i < outputs ; i++){
            for(size_t j = 0; j < hiddens; j++){
                output_weights.m_matrix[i][j] = distr(gen);
            }
        }
    }

};


#endif