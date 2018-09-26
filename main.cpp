#include <iostream>
#include <fstream>
#include <string>
#include "vec3.h"

int main() {
    // Image Dimensions
    int nx = 200;
    int ny = 100;
    std::ofstream ofs;
    ofs.open("file.ppm");
    // PPM header: P6 = PPM format; width; height; 8bits
    ofs << "P6\n" << std::to_string(nx) << " " << std::to_string(ny) << "\n255\n";
    for(int j = ny-1; j>=0; j--){
        for(int i = 0; i<nx; i++){
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            ofs << static_cast<char>(ir) << static_cast<char>(ig) << static_cast<char>(ib);
        }
    }
    ofs.close();
}