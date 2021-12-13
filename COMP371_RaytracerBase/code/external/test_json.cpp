



#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#include "json.hpp"
#include "simpleppm.h"

#include <sstream>

using namespace std;
using namespace nlohmann;



bool test_parse_geometry(json& j){
    cout<<"Geometry: "<<endl;
    int gc = 0;
    for (auto itr = j["geometry"].begin(); itr!= j["geometry"].end(); itr++){
        
        int count = 0;
        std::string type;
        for (auto itr2 =(*itr)["type"].begin(); itr2!= (*itr)["type"].end(); itr2++){
            type = (*itr2).get<std::string>();
            ++count;
        }
        if(count!=1){
            cout<<"No type specified or more than one types specified"<<endl;
            cout<<"Type is a mandatory variable"<<endl;
            return false;
        } else {
            cout<<gc<<") "<<type;
        }
        
        cout<<"center:";
        for (auto itr2 =(*itr)["center"].begin(); itr2!= (*itr)["center"].end(); itr2++){
            cout<<" "<<(*itr2).get<float>();
        }
        cout<<endl;
        
        ++gc;
    }
    
}

int test_json(json& j){
    
    
    
    // 1 - parse geometry
    test_parse_geometry(j);
    
    
    return 0;
}

