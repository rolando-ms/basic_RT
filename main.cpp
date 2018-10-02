#include <iostream>
#include <fstream>
//#include <string>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitablelist.h"
//#include "float.h"
#include "values.h"
#include "camera.h"
//#include <stdlib.h>


// Rejection method. Pick a point in unit cube (x,y,x) in [-1,1).
// Reject point and try again if it is outside sphere.
vec3 random_in_unit_sphere(){
    vec3 p;
    do{
        p = 2.0*vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    } while(p.squared_length() >= 1.0);
    return p;
}


vec3 color(const ray& r, hitable *world){
//    float t = hit_sphere(vec3(0,0,-1),0.5,r);
    hit_record rec;
    // If ray hits the sphere
    if (world->hit(r, 0.0, MAXFLOAT, rec)){
        // Vector from surface hit to center of image plane
        //vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
        // Positive normalized unit vector (same trick used with 0<=t<=1)
        //return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*color(ray(rec.p, target-rec.p), world);
    }
    else{
        // If doesn't hits the sphere (just show background)
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        // Linear interpolation
        return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
    }
}

int main() {
    // Image Dimensions
    int nx = 200;
    int ny = 100;
    int ns = 1;
    std::ofstream ofs;
    ofs.open("file.ppm");
    // PPM header: P6 = PPM format; width; height; 8bits
    ofs << "P6\n" << std::to_string(nx) << " " << std::to_string(ny) << "\n255\n";
    // Righ hand coordinate system (x+ = right; y+ = up; z+ = towards user)
    hitable *list[2];
    list[0] = new sphere(vec3(0,0,-1),0.5);
    list[1] = new sphere(vec3(0,-100.5,-1),100);
    hitable *world = new hitable_list(list,2);
    camera cam;
    for(int j = ny-1; j>=0; j--){
        for(int i = 0; i<nx; i++){
            vec3 col(0,0,0);//Color initialization
            for(int s=0; s < ns; s++){
                float u = float(i) / float(nx);
                float v = float(j) / float(ny);
                ray r = cam.get_ray(u,v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r,world);
            }
            col /= float(ns);// Mean of all samples around pixel (i,j)
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            ofs << static_cast<char>(ir) << static_cast<char>(ig) << static_cast<char>(ib);
        }
    }
    ofs.close();
}