#include <iostream>

#include "RenderModel.h"

#include "GLUtils.h"

#include "ObjParser.h"

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
    
    
    void RenderModel::init(){
        
      
        
        is_error();
        
        glGenVertexArrays(1, &VertexArrayID);
        
        if(is_error(true)){
            cout<<"Err 00"<<endl;
        }
        
        glBindVertexArray(VertexArrayID);
        
       
        
        
        if(is_error(true)){
            cout<<"Err 0"<<endl;
        }

        
        // Create and compile our GLSL program from the shaders
        string vsh1 =  "StandardShading.vertexshader";
        string fsh1 = "StandardShading.fragmentshader";
        
        programID = LoadShaders( vsh1.c_str(), fsh1.c_str());
       
       
        if(is_error()){
            cout<<"Err A"<<endl;
        }
        
        // C u ntil here
       // std::cout << "Sphere360 draw()" << std::endl;
        
        // Load the texture
        string s2 =  m_image_name;
        
        Texture = loadBMP_custom(s2.c_str(), txt_width, txt_height);
        
      //  cout<<"Debug A"<<endl;
        
        //cout<<"Texture size: "<<txt_width<<" "<<txt_height<<endl;
        
        // Get a handle for our "myTextureSampler" uniform
        TextureID = glGetUniformLocation(programID, "myTextureSampler");
        
        // Read our .obj file
        
        std::string s1 =  "sp_txt_inv.obj";
        
        cout<<"Loading model "<<s1<<endl;
        
        bool res = loadOBJT(s1.c_str(), vertices, uvs, normals, m_obj, txt_width, txt_height);
        
        if(!res){
            cout<<"Error in loading the sphere object!"<<endl;
        }
        
        
     //   std::cout << vertices.size() << std::endl;
        
        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(programID, "MVP");
        ViewMatrixID = glGetUniformLocation(programID, "V");
        ModelMatrixID = glGetUniformLocation(programID, "M");
        
        
        if(is_error()){
            cout<<"Err B"<<endl;
        }
        
        // Get a handle for our "LightPosition" uniform
        glUseProgram(programID);
        LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
        
        
        
        // Load it into a VBO
        
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        
        
        glGenBuffers(1, &uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
        
        
        glGenBuffers(1, &normalbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
        
        
        if(is_error()){
            cout<<"Err C"<<endl;
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
    
    void RenderModel::render() {
        
        is_error();
        
    //    cout<<"render"<<endl;
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        
        glBindVertexArray(VertexArrayID);
        
        if(is_error(true)){
            cout<<"Err U0"<<endl;
        }
        
        
        glUseProgram(programID);

        
        if(is_error()){
            cout<<"Err U"<<endl;
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
        
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &m_ViewMatrix[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &mm[0][0]);
        
        glm::vec3 lightPos = glm::vec3(4, 4, 4);
        //	glm::vec3 lightPos = glm::vec3(0,0,0);
        
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
        
        
        if(is_error()){
            cout<<"Err D"<<endl;
        }
        
        
        
        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        
        if(is_error()){
            cout<<"Err E"<<endl;
        }
        
        if(Texture)
            glBindTexture(GL_TEXTURE_2D, Texture);
        
        if(is_error()){
            cout<<"Err E1"<<endl;
        }
        
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID, 0);
        
        if(is_error()){
            cout<<"Err E2"<<endl;
        }
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        
        if(is_error(true)){
            cout<<"Err E2.1"<<endl;
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        
        
        
        if(is_error(true)){
            cout<<"Err E2.2"<<endl;
        }
        
        glVertexAttribPointer(
                              0,                  // attribute
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        if(is_error(true)){
            cout<<"Err E3"<<endl;
        }
        
        // 2nd attribute buffer : UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
                              1,                                // attribute
                              2,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        
        
        if(is_error(true)){
            cout<<"Err E4"<<endl;
        }
        
        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                              2,                                // attribute
                              3,                                // size
                              GL_FLOAT,                         // type
                              GL_FALSE,                         // normalized?
                              0,                                // stride
                              (void*)0                          // array buffer offset
                              );
        
        
        if(is_error(true)){
            cout<<"Err F"<<endl;
        }
        
        // Draw the triangles !
        //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glDrawArrays(GL_LINES, 0, vertices.size());
        //  std::cout<<vertices.size()<<std::endl;
        
        if(is_error(true)){
            cout<<"Err G"<<endl;
            std::cout<<vertices.size()<<std::endl;
        }
        
//        glDisableVertexAttribArray(0);
 //       glDisableVertexAttribArray(1);
  //      glDisableVertexAttribArray(2);
        
        
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
                
                int ww = txt_width;
                int hh = txt_height;
                
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
