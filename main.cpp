#include <iostream>
#include "neuron.hpp"

int main(){
    Network<2, 3, 2> net{0.01f};

    for(size_t i = 0; i < 3 ; i++){
        for(size_t j = 0; j < 2; j++){
            std::cout << net.hidden_weights.m_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    for(size_t i = 0; i < 2 ; i++){
        for(size_t j = 0; j < 3; j++){
            std::cout << net.output_weights.m_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}