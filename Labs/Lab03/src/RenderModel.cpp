#include <iostream>

#include "RenderModel.h"

#include "GLUtils.h"

#include "ObjModel.h"

#include "GLUtils.h"



using namespace std;

namespace TAPP {

   
    void RenderModel::hover(double  x, double y, int mods){
        
        
    }
    void RenderModel::grab(double x, double y, int b, int mods /* 0 left, 1 right, 2 middle*/){
        
        
    }
    
    
    void RenderModel::drag(double x, double y, int mods) {
        
        
    }
    
    
    void RenderModel::resize(double x, double y){
        
        
    }
    
    void RenderModel::load_geometry(){
        
        
        std::string path =  "assets/sp.obj";
        Load(m_obj, path.c_str());
        std::vector<float> vertices, normals;
        for(int i=0;i<m_obj.vertex.size();++i){
            for(int j=0;j<3;++j){
                vertices.push_back(m_obj.vertex[i][j]);
                normals.push_back(m_obj.normal[i][j]);
            }
        }
        
        cout<<"Mesh has: "<<vertices.size()/3<<": vertices!"<<endl;
        
        std::vector<unsigned int> indices;
        for(int i=0;i<m_obj.faces.size();++i){
            if(m_obj.faces[i].size()!=3){
                cout<<"Error: not a triangular mesh!"<<endl;
                return;
            }
            for(int j=0;j<3;++j){
                indices.push_back(m_obj.faces[i][j]);
            }
        }
        
        cout<<"Mesh has: "<<indices.size()/3<<": faces!"<<endl;

        
        // 0 - create the vertex array object
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        
        // create the vertex buffer object -- first entry in the renderer
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
        
        glGenBuffers(1, &m_NBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_NBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(normals), &normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        
        
        // element array buffer
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);


       // glBindBuffer(GL_ARRAY_BUFFER, 0);
        //glBindVertexArray(0);
    }



    
    void RenderModel::init(){
        is_error();
        
        load_geometry();
        // Create and compile our GLSL program from the shaders
        string vsh1 = "assets/Phong.vertexshader.glsl";
        string fsh1 = "assets/Phong.fragmentshader.glsl";
        
        programID = LoadShaders( vsh1.c_str(), fsh1.c_str());
       
        
       
        if(is_error(true)){
            cout<<"Err 00"<<endl;
        }
        
       
       
        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(programID, "MVP");
        ViewMatrixID = glGetUniformLocation(programID, "V");
        ModelMatrixID = glGetUniformLocation(programID, "M");
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
        dcID = glGetUniformLocation(programID, "diffuse_color");
        
        
        if(is_error()){
            cout<<"Err B"<<endl;
        }
        
    }
    
    
    void RenderModel::release(){
        
    //    cout<<"Do I ger hre! 34"<<endl;
        
        /*
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &uvbuffer);
        glDeleteBuffers(1, &normalbuffer);
        glDeleteProgram(programID);
        glDeleteTextures(1, &Texture);
        glDeleteVertexArrays(1, &VertexArrayID);
         */
    }
    

void RenderModel::render(){
    
  //  render_general(0);

   render_general(0);

}



    void RenderModel::render_general(int mode){
        if(is_error()){
            cout<<"Err B1"<<endl;
        }
        
        // Get a handle for our "LightPosition" uniform
        glUseProgram(programID);
        
    //    cout<<"render"<<endl;
        
        if(is_error()){
            cout<<"Err B2"<<endl;
        }
        
        glm::mat4 mm(1.0f);
        glm::mat4 MVP = m_ProjMatrix * m_ViewMatrix;
        
#if 0
        std::cout<<"X "<<endl;
        for (int i = 0; i<4; ++i)
            for (int j = 0; j<4; ++j)
                std::cout << m_ProjMatrix[i][j] << " ";
        std::cout << std::endl;
#endif
        
        if(is_error()){
            cout<<"Err B3"<<endl;
        }
        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &m_ViewMatrix[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &mm[0][0]);
        
        glm::vec3 lightPos = glm::vec3(4, 4, 4);
        //	glm::vec3 lightPos = glm::vec3(0,0,0);
        
        
        if(is_error()){
            cout<<"Err B4"<<endl;
        }
        
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
        
        glm::vec3 dc = glm::vec3(1, 0, 0);
        if(mode==1)
            dc=glm::vec3(0, 0, 1);
        
        
        glUniform3f(dcID, dc.x, dc.y, dc.z);
        
      
       
        if(is_error()){
            cout<<"Err 3"<<endl;
        }
       
        
       // glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
       // glEnable(GL_DEPTH_TEST);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        
    }
    void RenderModel::render_pick_select(PickDataback& ) { // to see if we selected this object
        
        
        
        
    }
    
    
    
    void RenderModel::render_pick_detail(PickDataback& pd){ // to see if we selected a certain primitive
        
        // this is wrong
        glm::vec3 origin = pd.origin;
        
      //  cout<<"O: "<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<" "<<endl;
        
        
        glm::vec3 dir = pd.dir;
        
        float b_u, b_v, b_w, b_z; //bary coordiante
        
        for (int i = 0; i < m_obj.faces.size(); i++)
        {
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec2> textures;
            for (int j = 0; j < m_obj.faces[i].size(); j++)
            {
                TPoint P = m_obj.vertex[m_obj.faces[i][j]];
                TVector txt = m_obj.texture[m_obj.txfaces[i][j]];
                glm::vec2 uv(txt[0], txt[1]);
                glm::vec3 vertex(P[0], P[1], P[2]);
                vertices.push_back(vertex);
                textures.push_back(uv);
            }
            
            //		for(int k = 0;k<3;k++){
            //		vertices[k] = convert(vertices[k]);
            //		}
            glm::vec2 barytemp;
            glm::vec3 bary;
            float distance;
            //   std::cout<<"Do I get here?"<<std::endl;
            
            // Hack
            bool hit = glm::intersectRayTriangle(origin, dir, vertices[0], vertices[1], vertices[2], barytemp, distance);
            
            bary[0] = barytemp[0];
            bary[1] = barytemp[1];
            bary[2] = 0;
            
            
            pd.bHit = 0;
            
            if (hit)
            {
                
                pd.bHit = 1;
                
                std::vector<glm::vec2>  uvs;
                uvs = textures;
                
                glm::vec2 p_uv = uvs[0]*(1 - bary.x - bary.y)  + uvs[1]*bary.x + uvs[2]*bary.y;
                glm::vec2 tmp;
                tmp[0] = (1 - bary.x - bary.y) * uvs[0][0] + bary.x*uvs[1][0]+bary.y*uvs[2][0];
                tmp[1] = (1 - bary.x - bary.y) * uvs[0][1] + bary.x*uvs[1][1]+bary.y*uvs[2][1];
                
                
                // HACK
                int ww = 0;//txt_width;
                int hh = 0;//txt_height;
                
                pd.P2d[0] = p_uv[0]* ww;
                pd.P2d[1] = (1-p_uv[1])*hh;
                
          //      printf("P_UV tmp: %f,%f\n", p_uv[0]* ww, (1-p_uv[1])*hh);
           //     printf("P_UV: %f,%f\n", p_uv[0],p_uv[1]);
                
                glm::vec3 cartesian = vertices[0] * (1 - bary.x - bary.y)
                + vertices[1] * bary.x + vertices[2] * bary.y;
                
                pd.P3d = cartesian;
            }
        }

    }// end of picking function
    
}
