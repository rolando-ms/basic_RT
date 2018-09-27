#include <iostream>
#include <fstream>
//#include <string>
#include "vec3.h"
#include "ray.h"


// Function that checks if a ray is hitting a sphere according to
// the solution of dot((p-c),(p-c)) = r^2 : p=o+t*d
// -> t^2*dot(d,d) + 2*t*dot(t,o-c) + dot((o-c),(o-c)) = r^2
// If discriminant > 0 -> 2 real solutions (ray hits the sphere twice)
// if discriminant = 0 -> 1 real solution (ray hits sphere on surface)
// if discriminant < 0 -> No real solutions (No hit)
float hit_sphere(const vec3& center, float radius, const ray& r){
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0){
        return -1.0;
    }
    else{
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}


vec3 color(const ray& r){
    float t = hit_sphere(vec3(0,0,-1),0.5,r);
    if (t > 0.0){
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
    }
//    if (hit_sphere(vec3(0,0,-1), 0.5, r))
//        return vec3(1,0,0);
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    // Linear interpolation
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
}

int main() {
    // Image Dimensions
    int nx = 200;
    int ny = 100;
    std::ofstream ofs;
    ofs.open("file.ppm");
    // PPM header: P6 = PPM format; width; height; 8bits
    ofs << "P6\n" << std::to_string(nx) << " " << std::to_string(ny) << "\n255\n";
    // Righ hand coordinate system (x+ = right; y+ = up; z+ = towards user)
    vec3 lower_left_corner(-2.0,-1.0,-1.0);
    vec3 horizontal(4.0,0.0,0.0);
    vec3 vertical(0.0,2.0,0.0);
    vec3 origin(0.0,0.0,0.0);
    for(int j = ny-1; j>=0; j--){
        for(int i = 0; i<nx; i++){
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
//            float b = 0.2;
            vec3 col = color(r);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            ofs << static_cast<char>(ir) << static_cast<char>(ig) << static_cast<char>(ib);
        }
    }
    ofs.close();
}