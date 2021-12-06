

using namespace std;

#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#include "json.hpp"
#include "simpleppm.h"



int print_eigen(Eigen::Matrix3d m)
{
    // Eigen Matrices do have rule to print them with std::cout
    std::cout << m << std::endl;
    return 0;
}

int test_eigen()
{
    
    
    Eigen::Matrix3d test; //3 by 3 double precision matrix initialization

    // Let's make it a symmetric matrix
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            test(i,j) = (i+1)*(1+j);
    }

    // Print
    print_eigen(test);

    return 0;
}


int test_save_ppm(){
    int dimx = 800;
    int dimy = 600;
    
    int w = 100;
    
    std::vector<double> buffer(3*dimx*dimy);
    for(int j=0;j<dimy;++j){
        for(int i=0;i<dimx;++i){
            if(((i+j)/w)%2==0){
                buffer[3*j*dimx+3*i+0]=1;
                buffer[3*j*dimx+3*i+1]=1;
                buffer[3*j*dimx+3*i+2]=0;
            } else {
                buffer[3*j*dimx+3*i+0]=0;
                buffer[3*j*dimx+3*i+1]=1;
                buffer[3*j*dimx+3*i+2]=1;
            }
        }
    }
               
             
    save_ppm("test.ppm", buffer, dimx, dimy);
    
    return 0;
}


int test_all(){
    test_eigen();
    test_save_ppm();
    return 0;
}
