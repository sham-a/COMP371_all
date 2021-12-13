#ifndef VSPHERE_H
#define VSPHERE_H
#include <GL/glew.h>

#include "RUIObject.h"
#include <vector>

#ifdef RUNONMAC
//#include <OpenGL/gl.h>
#else

//#include <GL/gl.h>
#endif

#include "ObjModel.h"



namespace TAPP {
    
    class RenderModel :public RUIObject {
    public:
        
        RenderModel()
        :RUIObject(){
        
    }
    
        GLuint MatrixID;
        GLuint ViewMatrixID;
        GLuint ModelMatrixID;
        GLuint LightID;
        
        GLuint vertexbuffer;
        GLuint VertexArrayID;
        GLuint programID;
        
        GLuint Texture;
        GLuint TextureID;
        GLuint uvbuffer;
        GLuint normalbuffer;
        
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        
        int txt_width, txt_height;
        
        std::string m_image_name;
        
        ObjModel m_obj;
        
        virtual void init();
        virtual void release();
        virtual void hover(double  x, double y, int mods);
        virtual void grab(double x, double y, int b, int mods /* 0 left, 1 right, 2 middle*/);
        virtual void drag(double x, double y, int mods) ;
        virtual void resize(double x, double y);
        
        virtual void render() ;
        virtual void render_pick_select(PickDataback& ) ; // to see if we selected this object
        virtual void render_pick_detail(PickDataback& ); // to see if we selected a certain primitive
    
};


}
#endif // TOGLAPP_H
