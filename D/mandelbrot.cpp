#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <thread>
#include <chrono>

struct Color {
    int r, g, b;
};

int getMandelbrotValue(const std::complex<double>& c, int max_iter) {
    std::complex<double> z = 0;
    int i = 0;
    while (i < max_iter && std::abs(z) < 2.0) {
        z = z * z + c;
        i++;
    }
    return i;
}

void render_slice(std::vector<Color>* pixels, int width, int height,
                  double x_min, double x_max, double y_min, double y_max,
                  int max_iter, int start_row, int end_row) {
    for (int y = start_row; y < end_row; ++y) {
        for (int x = 0; x < width; ++x) {
            double real = x_min + (x / (double)width) * (x_max - x_min);
            double imag = y_min + (y / (double)height) * (y_max - y_min);
            std::complex<double> c(real, imag);

            int value = getMandelbrotValue(c, max_iter);

            int color_val = 255 * (1.0 - (double)value / max_iter);
            if (value == max_iter) color_val = 0;

            (*pixels)[y * width + x] = {color_val, color_val, color_val};
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 9) {
        std::cerr << "Usage: " << argv[0] << " <width> <height> <x_min> <x_max> <y_min> <y_max> <max_iter> <output.ppm>" << std::endl;
        return 1;
    }

    const int width = std::stoi(argv[1]);
    const int height = std::stoi(argv[2]);
    const double x_min = std::stod(argv[3]);
    const double x_max = std::stod(argv[4]);
    const double y_min = std::stod(argv[5]);
    const double y_max = std::stod(argv[6]);
    const int max_iter = std::stoi(argv[7]);
    const std::string filename = argv[8];

    std::vector<Color> pixels(width * height);

    const int num_threads = 8;
    std::vector<std::thread> threads;
    int rows_per_thread = height / num_threads;

    std::cout << "Starting render with " << num_threads << " threads..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        int start_row = i * rows_per_thread;
        int end_row = (i == num_threads - 1) ? height : (i + 1) * rows_per_thread;
        
        threads.emplace_back(render_slice, &pixels, width, height, x_min, x_max,
                             y_min, y_max, max_iter, start_row, end_row);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    std::cout << "Render finished in " << diff.count() << " seconds." << std::endl;

    std::ofstream ofs(filename, std::ios::out | std::ios::binary);
    if (!ofs) {
        std::cerr << "Error: Could not open output file." << std::endl;
        return 1;
    }
    
    ofs << "P3\n";
    ofs << width << " " << height << "\n";
    ofs << "255\n"; //

    for (const auto& p : pixels) {
        ofs << p.r << " " << p.g << " " << p.b << "\n";
    }

    ofs.close();
    std::cout << "Image saved to " << filename << std::endl;

    return 0;
}  