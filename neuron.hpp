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

    Matrix<outputs, 1> predict(const std::array<double, inputs>& input_data){         // forward propogation
        Matrix<inputs, 1> input_matrix;
        for(size_t i = 0; i < inputs ; i++){
            input_matrix.m_matrix[i][0] = input_data[i];
        }

        Matrix<hiddens, 1> hidden_inputs =  hidden_weights * input_matrix;
        Matrix<hiddens, 1> hidden_outputs = hidden_inputs.apply_sigmoid();
        Matrix<outputs, 1> final_inputs =   output_weights * hidden_outputs;
        Matrix<outputs, 1> final_outputs =  final_inputs.apply_sigmoid();

        return final_outputs;
    }

    void train(const std::array<double, inputs>& input_data, const std::array<double, outputs>& target_data){

        Matrix<inputs, 1> input_matrix;
        for(size_t i = 0; i < inputs ; i++){
            input_matrix.m_matrix[i][0] = input_data[i];
        }

        Matrix<hiddens, 1> hidden_inputs =  hidden_weights * input_matrix;
        Matrix<hiddens, 1> hidden_outputs = hidden_inputs.apply_sigmoid();
        Matrix<outputs, 1> final_inputs =   output_weights * hidden_outputs;
        Matrix<outputs, 1> final_outputs =  final_inputs.apply_sigmoid();

        Matrix<outputs, 1> target_matrix;
        for(size_t i = 0; i < outputs; i++){
            target_matrix.m_matrix[i][0] = target_data[i];
        }

        Matrix<outputs, 1> output_errors = target_matrix - final_outputs;              //error calculation
        Matrix<hiddens, 1> hidden_errors = output_weights.transpose() * output_errors;

        output_weights = output_weights +   ((output_errors % apply_sigmoid_prime(final_outputs))
                                            * hidden_outputs.transpose()).scale(learning_rate);           // backpropogate
        hidden_weights = hidden_weights +   ((hidden_errors % apply_sigmoid_prime(hidden_outputs))         
                                            * input_matrix.transpose()).scale(learning_rate);
    }
};


#endif