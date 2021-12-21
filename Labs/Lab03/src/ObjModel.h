#ifndef _T_OBJ_MODEL_H_
#define _T_OBJ_MODEL_H_

#include "TTuple.h"
#include <vector>
#include <iostream>
#include <fstream>

//#include "Movie.h"

class ObjModel {
    
  public:


  /// construction part
  void optimize();

    ObjModel();
    ObjModel(const ObjModel&);

    ObjModel& operator=(const ObjModel&);
    void copy(const ObjModel& m);
    virtual ~ObjModel();

    void reverse_facet(int);
    void reverse_all();
    void reverse_smart();
    
    bool operator==(const ObjModel&);

    std::vector<TPoint> vertex;
    std::vector<std::vector<int> > vfacets;

    // tangent and bitangent are not computed yet
    std::vector<TVector> normal, fnormal, tangent,  bitangent, texture;


    // the actual face arrays
    std::vector< std::vector<int> > faces, nfaces, txfaces, tgfaces, btgfaces;
    std::vector<std::string> sfaces;

    // methods
    int AddVertex(TPoint P);
    int AddTexture(TVector Tx);
    int AddNormal(TVector N);
    int AddTangent(TVector Tg);
    int AddFace(int N, int* face, std::string mat, int* nf=0, int*txf=0, int* tgf=0, int *btgf=0);
   
    int AssertValid();

    /// QUERY functions

    // query functions
    int QTexture()const;
    int QNormals()const;
    int QTangents()const;
    int QBitangents()const;

    /// Transformation functions

    void Subdivide();

    // Normalize the model: make it out of triangles
    int Normalize();


    // object manipulation functions
    int SubstractConsistent(double displacement);

    // center the model
    int CenterObject(TPoint P);
    int CenterObject();

    // bounding box and centroids
    TPoint P1, P2, C;
    void ComputeBoundingBox();

    // generate normals using face averaging
    int GenerateNormals(int bAlways = 0);


    TVector ComputeFaceNormals(int face);
    void ComputeAllFaceNormals();
    
    int EliminateEmptyVertices();


    int Triangulate();

    // UI 
    int GenerateObjModel(std::ostream& f);
    
    void add_spherical_coordinates(double radius, double width, double height);
   

  private:
    int AddGeneric(int N, int* f, std::vector< std::vector<int> >& vec);

  public:
    
    std::string matlib;

    


    void dumpampl(const char* fname);

    void RotateLeft();


   public:
    int NormalizeFacetIndex();
    int AbsFacetIndex();
};
    

// external function
void SaveAs(ObjModel& obj, const char* file);
void Load(ObjModel& obj, const char* file);

std::ostream& operator<<(std::ostream& o, ObjModel& m);
std::istream& operator>>(std::istream& in, ObjModel&m);


#endif // _T_OBJ_MODEL_H_


