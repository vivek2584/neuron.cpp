#include "loader.hpp"
#include "neuron.hpp"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int main() {
    constexpr int num_train_samples = 1000;
    constexpr float learning_rate = 0.1f;
    constexpr int epochs = 10;

    int image_count = 0;
    int label_count = 0;

    auto raw_images = load_mnist_images("mnist_dataset/train-images-idx3-ubyte", image_count);
    auto raw_labels = load_mnist_labels("mnist_dataset/train-labels-idx1-ubyte", label_count);

    if (image_count != label_count) {
        std::cerr << "Image and label count mismatch!\n";
        return 1;
    }

    if (image_count < num_train_samples) {
        std::cerr << "Not enough data in MNIST files.\n";
        return 1;
    }

    std::vector<std::array<double, 784>> train_images(num_train_samples);
    std::vector<std::array<double, 10>> train_labels(num_train_samples);

    for (int i = 0; i < num_train_samples; ++i) {
        for (int j = 0; j < 784; ++j) {
            train_images[i][j] = static_cast<double>(raw_images[i][j]) / 255.0;
        }
        train_labels[i].fill(0.0);
        train_labels[i][raw_labels[i]] = 1.0;
    }

    Network<784, 64, 10> network(learning_rate);

    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (int i = 0; i < num_train_samples; ++i) {
            network.train(train_images[i], train_labels[i]);
        }
        std::cout << "Epoch " << epoch + 1 << " complete.\n";
    }

    std::cout << "Training complete on " << num_train_samples << " samples.\n";

    auto prediction = network.predict(train_images[0]);

    int test_samples = 10;
    std::cout << "\nTesting on " << test_samples << " samples:\n";

    for (int i = 0; i < test_samples; ++i) {
        auto prediction = network.predict(train_images[i]);

        int expected = std::distance(train_labels[i].begin(), std::max_element(train_labels[i].begin(), train_labels[i].end()));

        int predicted = 0;
        double max_val = prediction.m_matrix[0][0];
        for (int j = 1; j < 10; ++j){
            if (prediction.m_matrix[j][0] > max_val){
                max_val = prediction.m_matrix[j][0];
                predicted = j;
            }
        }
        std::cout << "Sample " << i << " - Expected: " << expected << ", Predicted: " << predicted << "\n";
    }

    return 0;
}
