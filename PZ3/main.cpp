#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <cmath>
#include <filesystem>
#include <sstream>

struct PGMImage {
    int width;
    int height;
    int maxVal;
    std::vector<std::vector<int>> pixels;
    
    PGMImage(int w, int h) : width(w), height(h), maxVal(255) {
        pixels.resize(h, std::vector<int>(w, 0));
    }
    
    PGMImage(const PGMImage& other) : width(other.width), height(other.height), maxVal(other.maxVal) {
        pixels.resize(height, std::vector<int>(width, 0));
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                pixels[i][j] = other.pixels[i][j];
            }
        }
    }
    
    PGMImage& operator=(const PGMImage& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            maxVal = other.maxVal;
            pixels = other.pixels;
        }
        return *this;
    }
};

// Функция для пропуска комментариев
void skipComments(std::ifstream& file) {
    char c;
    file >> std::ws;
    while (file.peek() == '#') {
        std::string comment;
        std::getline(file, comment);
    }
}

// Чтение PGM (поддержка P2 и P5)
PGMImage readPGM(const std::string& filename) {
    std::ifstream file;
    
    // Сначала пытаемся определить формат
    file.open(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string magic;
    file >> magic;
    std::cout << "Reading: " << filename << " (Format: " << magic << ")" << std::endl;
    
    if (magic != "P2" && magic != "P5") {
        throw std::runtime_error("Unsupported PGM format. Only P2 and P5 supported");
    }
    
    skipComments(file);
    
    int width, height, maxVal;
    file >> width >> height >> maxVal;
    
    std::cout << "Size: " << width << "x" << height << ", MaxVal: " << maxVal << std::endl;
    
    PGMImage image(width, height);
    image.maxVal = maxVal;
    
    file.get(); // Пропускаем пробел перед данными
    
    if (magic == "P2") {
        // ASCII формат
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (!(file >> image.pixels[i][j])) {
                    throw std::runtime_error("Error reading ASCII pixel data");
                }
            }
        }
    } else if (magic == "P5") {
        // Бинарный формат
        file.close();
        file.open(filename, std::ios::binary);
        
        // Читаем заново до данных
        std::string line;
        for (int i = 0; i < 3; i++) {
            std::getline(file, line);
        }
        
        // Читаем бинарные данные
        std::vector<unsigned char> buffer(width * height);
        file.read(reinterpret_cast<char*>(buffer.data()), width * height);
        
        if (file.gcount() != width * height) {
            throw std::runtime_error("Error reading binary pixel data");
        }
        
        // Конвертируем в матрицу пикселей
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                image.pixels[i][j] = buffer[i * width + j];
            }
        }
    }
    
    file.close();
    return image;
}

// Запись PGM (поддержка P2 и P5)
void writePGM(const PGMImage& image, const std::string& filename, bool binary = false) {
    std::ofstream file;
    
    if (binary) {
        file.open(filename, std::ios::binary);
    } else {
        file.open(filename);
    }
    
    if (!file) {
        throw std::runtime_error("Cannot create file: " + filename);
    }
    
    if (binary) {
        // P5 бинарный формат
        file << "P5\n";
        file << image.width << " " << image.height << "\n";
        file << image.maxVal << "\n";
        
        // Конвертируем матрицу в бинарные данные
        std::vector<unsigned char> buffer(image.width * image.height);
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                buffer[i * image.width + j] = static_cast<unsigned char>(image.pixels[i][j]);
            }
        }
        
        file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    } else {
        // P2 ASCII формат
        file << "P2\n";
        file << image.width << " " << image.height << "\n";
        file << image.maxVal << "\n";
        
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                file << image.pixels[i][j];
                if (j < image.width - 1) file << " ";
            }
            file << "\n";
        }
    }
    
    file.close();
    std::cout << "Saved: " << filename << (binary ? " (P5 binary)" : " (P2 ASCII)") << std::endl;
}

void createTestImage() {
    PGMImage test(100, 100);
    
    // Создаем тестовое изображение с градиентом
    for (int i = 0; i < test.height; i++) {
        for (int j = 0; j < test.width; j++) {
            int value = (i * 255 / test.height + j * 255 / test.width) / 2;
            test.pixels[i][j] = value;
        }
    }
    
    writePGM(test, "images/test_image.pgm", false); // ASCII
    writePGM(test, "images/test_image_binary.pgm", true); // Binary
    std::cout << "Created test images in both P2 and P5 formats" << std::endl;
}

void addSaltPepperNoise(PGMImage& image, double noiseLevel) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    int noisePixels = 0;
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            if (dis(gen) < noiseLevel) {
                image.pixels[i][j] = (dis(gen) < 0.5) ? 0 : 255;
                noisePixels++;
            }
        }
    }
    std::cout << "Added salt-pepper noise: " << noisePixels << " pixels affected" << std::endl;
}

PGMImage medianFilter(const PGMImage& image, int kernelSize) {
    PGMImage result(image.width, image.height);
    result.maxVal = image.maxVal;
    
    int offset = kernelSize / 2;
    
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            std::vector<int> neighbors;
            
            for (int ki = -offset; ki <= offset; ki++) {
                for (int kj = -offset; kj <= offset; kj++) {
                    int ni = i + ki;
                    int nj = j + kj;
                    
                    int actual_i = std::max(0, std::min(image.height - 1, ni));
                    int actual_j = std::max(0, std::min(image.width - 1, nj));
                    
                    neighbors.push_back(image.pixels[actual_i][actual_j]);
                }
            }
            
            std::sort(neighbors.begin(), neighbors.end());
            result.pixels[i][j] = neighbors[neighbors.size() / 2];
        }
    }
    
    std::cout << "Applied median filter with kernel size " << kernelSize << std::endl;
    return result;
}

PGMImage meanFilter(const PGMImage& image, int kernelSize) {
    PGMImage result(image.width, image.height);
    result.maxVal = image.maxVal;
    
    int offset = kernelSize / 2;
    
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            int sum = 0;
            int count = 0;
            
            for (int ki = -offset; ki <= offset; ki++) {
                for (int kj = -offset; kj <= offset; kj++) {
                    int ni = i + ki;
                    int nj = j + kj;
                    
                    if (ni >= 0 && ni < image.height && nj >= 0 && nj < image.width) {
                        sum += image.pixels[ni][nj];
                        count++;
                    }
                }
            }
            
            result.pixels[i][j] = (count > 0) ? (sum / count) : image.pixels[i][j];
        }
    }
    
    std::cout << "Applied mean filter with kernel size " << kernelSize << std::endl;
    return result;
}

PGMImage gaussianFilter(const PGMImage& image, int kernelSize, double sigma) {
    PGMImage result(image.width, image.height);
    result.maxVal = image.maxVal;
    
    int offset = kernelSize / 2;
    
    std::vector<std::vector<double>> kernel = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    
    if (kernelSize == 5) {
        kernel = {
            {1, 4, 6, 4, 1},
            {4, 16, 24, 16, 4},
            {6, 24, 36, 24, 6},
            {4, 16, 24, 16, 4},
            {1, 4, 6, 4, 1}
        };
    }
    
    double sum = 0;
    for (const auto& row : kernel) {
        for (double val : row) {
            sum += val;
        }
    }
    for (auto& row : kernel) {
        for (double& val : row) {
            val /= sum;
        }
    }
    
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            double weightedSum = 0.0;
            
            for (int ki = -offset; ki <= offset; ki++) {
                for (int kj = -offset; kj <= offset; kj++) {
                    int ni = i + ki;
                    int nj = j + kj;
                    
                    if (ni >= 0 && ni < image.height && nj >= 0 && nj < image.width) {
                        double weight = kernel[ki + offset][kj + offset];
                        weightedSum += image.pixels[ni][nj] * weight;
                    } else {
                        int bounded_i = std::max(0, std::min(image.height - 1, ni));
                        int bounded_j = std::max(0, std::min(image.width - 1, nj));
                        double weight = kernel[ki + offset][kj + offset];
                        weightedSum += image.pixels[bounded_i][bounded_j] * weight;
                    }
                }
            }
            
            result.pixels[i][j] = static_cast<int>(std::round(weightedSum));
        }
    }
    
    std::cout << "Applied gaussian filter with kernel size " << kernelSize << std::endl;
    return result;
}

double calculatePSNR(const PGMImage& original, const PGMImage& filtered) {
    double mse = 0.0;
    int totalPixels = original.width * original.height;
    
    for (int i = 0; i < original.height; i++) {
        for (int j = 0; j < original.width; j++) {
            double diff = original.pixels[i][j] - filtered.pixels[i][j];
            mse += diff * diff;
        }
    }
    
    mse /= totalPixels;
    
    if (mse == 0) {
        return 100.0;
    }
    
    double psnr = 20 * log10(255.0 / sqrt(mse));
    return psnr;
}

double calculateSimilarity(const PGMImage& original, const PGMImage& filtered) {
    int matchingPixels = 0;
    int totalPixels = original.width * original.height;
    
    for (int i = 0; i < original.height; i++) {
        for (int j = 0; j < original.width; j++) {
            if (std::abs(original.pixels[i][j] - filtered.pixels[i][j]) <= 5) {
                matchingPixels++;
            }
        }
    }
    
    return (static_cast<double>(matchingPixels) / totalPixels) * 100.0;
}

// Функция для определения формата файла
bool isBinaryPGM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;
    
    std::string magic;
    file >> magic;
    file.close();
    
    return (magic == "P5");
}

// Обработка всех изображений в папке
void processAllImages() {
    std::cout << "=== Processing All Images in 'images' folder ===" << std::endl;
    
    std::vector<std::string> imageFiles;
    
    // Ищем все PGM файлы в папке images
    for (const auto& entry : std::filesystem::directory_iterator("images")) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (entry.path().extension() == ".pgm") {
                imageFiles.push_back(entry.path().string());
            }
        }
    }
    
    if (imageFiles.empty()) {
        std::cout << "No PGM files found in 'images' folder. Creating test images..." << std::endl;
        createTestImage();
        // Добавляем оба тестовых файла
        imageFiles.push_back("images/test_image.pgm");
        imageFiles.push_back("images/test_image_binary.pgm");
    }
    
    std::cout << "Found " << imageFiles.size() << " PGM file(s)" << std::endl;
    
    // Параметры тестирования
    std::vector<double> noiseLevels = {0.01, 0.05, 0.1};
    std::vector<std::pair<std::string, int>> filters = {
        {"median_3", 3},
        {"median_5", 5},
        {"mean_3", 3},
        {"mean_5", 5},
        {"gaussian_3", 3}
    };
    
    // CSV файл для результатов
    std::ofstream csvFile("results/denoising_results.csv");
    csvFile << "Image,Format,NoiseLevel,Filter,PSNR,Similarity%\n";
    
    // Обрабатываем каждое изображение
    for (const auto& imagePath : imageFiles) {
        std::string filename = std::filesystem::path(imagePath).filename().string();
        std::string basename = std::filesystem::path(imagePath).stem().string();
        std::string format = isBinaryPGM(imagePath) ? "P5" : "P2";
        
        std::cout << "\n--- Processing: " << filename << " (" << format << ") ---" << std::endl;
        
        try {
            PGMImage original = readPGM(imagePath);
            
            for (double noiseLevel : noiseLevels) {
                std::cout << "\nAdding noise level: " << noiseLevel << std::endl;
                
                // Создаем зашумленную версию
                PGMImage noisy = original;
                addSaltPepperNoise(noisy, noiseLevel);
                
                std::string noisyFilename = "results/" + basename + "_noisy_" + 
                                          std::to_string(int(noiseLevel * 100)) + ".pgm";
                // Сохраняем в том же формате, что и исходное
                writePGM(noisy, noisyFilename, format == "P5");
                
                // Применяем все фильтры
                for (const auto& filter : filters) {
                    std::cout << "Applying filter: " << filter.first << std::endl;
                    
                    PGMImage filtered(original.width, original.height);
                    
                    if (filter.first.find("median") != std::string::npos) {
                        filtered = medianFilter(noisy, filter.second);
                    } else if (filter.first.find("mean") != std::string::npos) {
                        filtered = meanFilter(noisy, filter.second);
                    } else if (filter.first.find("gaussian") != std::string::npos) {
                        filtered = gaussianFilter(noisy, filter.second, 1.0);
                    }
                    
                    // Сохраняем результат в том же формате
                    std::string resultFilename = "results/" + basename + "_" + 
                                               std::to_string(int(noiseLevel * 100)) + "_" +
                                               filter.first + ".pgm";
                    writePGM(filtered, resultFilename, format == "P5");
                    
                    // Вычисляем метрики
                    double psnr = calculatePSNR(original, filtered);
                    double similarity = calculateSimilarity(original, filtered);
                    
                    // Записываем в CSV
                    csvFile << filename << "," 
                           << format << ","
                           << noiseLevel << ","
                           << filter.first << ","
                           << psnr << ","
                           << similarity << "\n";
                    
                    std::cout << "Results - PSNR: " << psnr << ", Similarity: " << similarity << "%" << std::endl;
                }
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error processing " << filename << ": " << e.what() << std::endl;
        }
    }
    
    csvFile.close();
    std::cout << "\n=== All images processed! Results saved to results/denoising_results.csv ===" << std::endl;
}

int main() {
    // Создаем папки если их нет
    std::filesystem::create_directories("images");
    std::filesystem::create_directories("results");
    
    std::cout << "=== Image Denoising Program ===" << std::endl;
    std::cout << "Supports both P2 (ASCII) and P5 (binary) PGM formats" << std::endl;
    std::cout << "Place your PGM images in the 'images' folder" << std::endl;
    std::cout << "Results will be saved to the 'results' folder" << std::endl;
    std::cout << "=================================" << std::endl;
    
    // Запускаем обработку всех изображений
    processAllImages();
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    std::cout << "Check the 'results' folder for output images and CSV report." << std::endl;
    
    return 0;
}