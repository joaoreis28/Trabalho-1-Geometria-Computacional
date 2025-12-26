#ifndef WURFEL_H
#define WURFEL_H

#include <Types.h>

namespace Bib {

   

    int left2(CGL::Point2 p, CGL::Point2 q, CGL::Point2 r);
    int right2(CGL::Point2 p, CGL::Point2 q, CGL::Point2 r);
    int collinear2(CGL::Point2 p, CGL::Point2 q, CGL::Point2 r);

    int left3(CGL::Point3 p, CGL::Point3 q, CGL::Point3 r);
    int right3(CGL::Point3 p, CGL::Point3 q, CGL::Point3 r);
    int collinear3(CGL::Point3 p, CGL::Point3 q, CGL::Point3 r);

    int intersecPropria2(CGL::Segment2 s, CGL::Segment2 t);
    int intersecImpropria2(CGL::Segment2 s, CGL::Segment2 t);
    int noMeio(int a, int b, int c);
    int noSegmento(CGL::Point2 a, CGL::Point2 b, CGL::Point2 c);
    
    int intersecPropria3(CGL::Segment3 s, CGL::Segment3 t);
    
    CGL::Point2 pontoInter2(CGL::Segment2 s, CGL:: Segment2 t);


    int pontoEmPoligono(CGL::Point2 ponto, CGL::Polygon2 poligono, int nVertices);

    int sentidoAntiHorario(CGL::Polygon2 p, int nVertices);
    
    double areaPoligono(CGL::Polygon2 poligono, int nVertices);
    bool dentroTriangulo(CGL::Point2 p, CGL::Point2 t1, CGL::Point2 t2, CGL::Point2 t3);
    bool diagonalie(int i, int j, CGL::Polygon2 P, int nVertices );


bool Incone(int i, int j , CGL::Polygon2 P, int nVertices );
    


    bool diagonal (int i, int j, int nVertices, CGL::Polygon2 P);
        void triangular(int nVertices, CGL::Polygon2& P);
    void ClipEar(int i, int n, CGL::Polygon2& P);


    void ClipEar2(int idx, CGL::Polygon2 &P);
    void triangulate_n2(CGL::Polygon2 &P);

    void ClipEar3(int idx, int &n, CGL::Polygon2 &P);
void triangular3(int &nVertices, CGL::Polygon2 &P);



    

} 

#endif // WURFEL_H