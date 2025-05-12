#ifndef LOADER_HPP
#define LOADER_HPP

#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <array>

inline int32_t read_int32(std::ifstream& stream) {
    int32_t value = 0;
    stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    return __builtin_bswap32(value);
}

inline std::vector<std::array<uint8_t, 784>> load_mnist_images(const std::string& filepath, int& count) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open image file.");

    int32_t magic = read_int32(file);
    if (magic != 2051) throw std::runtime_error("Invalid image file (wrong magic number).");

    count = read_int32(file);
    int rows = read_int32(file);
    int cols = read_int32(file);
    if (rows != 28 || cols != 28) throw std::runtime_error("Expected 28x28 images.");

    std::vector<std::array<uint8_t, 784>> images(count);
    for (int i = 0; i < count; ++i) {
        file.read(reinterpret_cast<char*>(images[i].data()), 784);
    }

    return images;
}

inline std::vector<uint8_t> load_mnist_labels(const std::string& filepath, int& count) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open label file.");

    int32_t magic = read_int32(file);
    if (magic != 2049) throw std::runtime_error("Invalid label file (wrong magic number).");

    count = read_int32(file);
    std::vector<uint8_t> labels(count);
    file.read(reinterpret_cast<char*>(labels.data()), count);

    return labels;
}

#endif
