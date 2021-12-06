

using namespace std;

#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#include "external/json.hpp"
#include "external/simpleppm.h"

int test_all();
    
int main(int argc, char* argv[])
{
    if(argc!=3){
        cout<<"Invalid number of arguments"<<endl;
        cout<<"Usage: ./raytracer [scene] [output]"<<endl;
        cout<<"Run sanity checks"<<endl;
        
        test_all();
        
    } else {
        cout<<"OK"<<endl;
    }
  
    
    
    return 0;
}

