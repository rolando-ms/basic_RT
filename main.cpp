#include <iostream>
#include <fstream>

struct Sample{
    char r,g,b;
};

int main() {
    //std::cout << "Hello, World!" << std::endl;
    //return 0;
    //std::ofstream file("file.ppm",std::ios::binary);
    //file.write("P3 ",3);
    //file.write("200 ",4);
    //file.write("100 ",4);
    //file.write("255 ",4);
    std::ofstream ofs;
    ofs.open("file.ppm");
    ofs << "P6\n" << "200" << " " << "100" << "\n255\n";

    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny-1; j>=0; j--){
        for(int i = 0; i<nx; i++){
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            std::cout << ir << " " << ig << " " << ib << "\n";
            ofs << (char)ir << (char)ig << (char)ib;
            //Sample s;
            //s.r = (char)ir;
            //s.g = (char)ig;
            //s.b = (char)ib;
            //file.write(reinterpret_cast<char*>(&s), sizeof(Sample));
        }
    }
    ofs.close();
}