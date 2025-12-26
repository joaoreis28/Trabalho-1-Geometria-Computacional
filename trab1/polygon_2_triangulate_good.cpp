#include <Types.h>
#include <IO.h>
#include <Partition.h>
#include <CGAL/draw_surface_mesh.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <Wurfel.h>

using Aresta =  CGL::Mesh::Edge_index;
using Point = CGL::Mesh::Point;

double qualidade_from_points(CGL::Point3 p1, CGL::Point3 p2, CGL::Point3 p3)
{

    
    double a_sq = CGAL::squared_distance(p1, p2);
    double b_sq = CGAL::squared_distance(p2, p3);
    double c_sq = CGAL::squared_distance(p3, p1);

    std::vector<CGL::Point3> triangulo;
    triangulo.push_back(p1);
    triangulo.push_back(p2);
    triangulo.push_back(p3);

    double a = CGAL::squared_distance(p1,p2);
    double b = CGAL::squared_distance(p2,p3);
    double c = CGAL::squared_distance(p3,p1);


    double area = 0.0;

        
    for(int i = 0 ; i < 3; i++)
    {
        CGL::Point3 p1 = triangulo[i];
        CGL::Point3 p2 = triangulo[(i + 1) % 3];
        area += (p1.x() * p2.y()) - (p1.y() * p2.x());

    }

    area = area /2.0;
    if(area < 0) area = area * -1;

    double numerator = 4.0 * std::sqrt(3.0) * area;
    double denominator = a + b + c;

     

    return (numerator / denominator);
}




double qualidade(CGL::Mesh &mesh, CGL::Mesh::Face_index f)
{
    CGL::Mesh::Halfedge_index h = mesh.halfedge(f);

    CGL::Mesh::Vertex_index v1_idx = mesh.source(h);
    CGL::Mesh::Vertex_index v2_idx = mesh.source(mesh.next(h));
    CGL::Mesh::Vertex_index v3_idx = mesh.source(mesh.next(mesh.next(h)));


    CGL::Point3 p1 = mesh.point(v1_idx);
    CGL::Point3 p2 = mesh.point(v2_idx);
    CGL::Point3 p3 = mesh.point(v3_idx);

    std::vector<CGL::Point3> triangulo;
    triangulo.push_back(p1);
    triangulo.push_back(p2);
    triangulo.push_back(p3);

    double a = CGAL::squared_distance(p1,p2);
    double b = CGAL::squared_distance(p2,p3);
    double c = CGAL::squared_distance(p3,p1);


    double area = 0.0;

        
    for(int i = 0 ; i < 3; i++)
    {
        CGL::Point3 p1 = triangulo[i];
        CGL::Point3 p2 = triangulo[(i + 1) % 3];
        area += (p1.x() * p2.y()) - (p1.y() * p2.x());

    }

    area = area /2.0;

    double numerator = 4.0 * std::sqrt(3.0) * area;
    double denominator = a + b + c;

     

    return (numerator / denominator);
}





void MelhorarMalha(CGL::Mesh &mesh)
{
    bool melhoria_global = true;
    int iteracoes = 0;

    while(melhoria_global)
    {
        iteracoes++;
        melhoria_global = false;

        for(CGL::Mesh::Edge_index e : mesh.edges())
        {
            if(CGAL::is_border(e, mesh))
            {
                continue;
            }

            CGL::Mesh::Halfedge_index h1 = mesh.halfedge(e, 0);
            CGL::Mesh::Halfedge_index h2 = mesh.halfedge(e, 1);

            CGL::Mesh::Face_index f1 = mesh.face(h1);
            CGL::Mesh::Face_index f2 = mesh.face(h2);

            CGL::Mesh::Vertex_index v_shared1 = mesh.source(h1);
            CGL::Mesh::Vertex_index v_shared2 = mesh.target(h1);

            CGL::Mesh::Vertex_index v_opposite1 = mesh.target(mesh.next(h1));
            CGL::Mesh::Vertex_index v_opposite2 = mesh.target(mesh.next(h2));

           
            CGL::Point3 p_s1 = mesh.point(v_shared1);
            CGL::Point3 p_s2 = mesh.point(v_shared2);
            CGL::Point3 p_o1 = mesh.point(v_opposite1);
            CGL::Point3 p_o2 = mesh.point(v_opposite2);

            
            bool lados_opostos1 = Bib::left3(p_s1, p_s2, p_o1) ^ Bib::left3(p_s1, p_s2, p_o2);

            bool lados_opostos2 = Bib::left3(p_o1, p_o2, p_s1) ^ Bib::left3(p_o1, p_o2, p_s2);

            
            if (!(lados_opostos1 && lados_opostos2)) // testar se o quadrilatero é convexo
            {
                std::cout<< "Deu ruim : ";
                std:: cout << p_s1 << " " << p_s2 << " " << p_o1 << " " << p_o2 << std::endl;

                continue; 
            }

            std:: cout << p_s1 << " " << p_s2 << " " << p_o1 << " " << p_o2 << std::endl;
            double qualidade_antes = qualidade(mesh, f1) + qualidade(mesh, f2);
            // std::cout << " Qualidade antes: " << qualidade_antes << std::endl;
            // std::cout << " Qualidade f1 antes: " << qualidade(mesh, f1) << std::endl;
            // std::cout << " Qualidade f2 antes: " << qualidade(mesh, f2) << std::endl;

            std::cout << "*******************************" << std::endl;

            double qualidade_depois = qualidade_from_points(p_s1, p_o1, p_o2) + qualidade_from_points(p_s2, p_o2, p_o1);
            // std::cout << " Qualidade depois: " << qualidade_depois << std::endl;
            // std::cout << " Qualidade f1 depois: " << qualidade_from_points(p_s1, p_o1, p_o2) << std::endl;
            // std::cout << " Qualidade f2 depois: " << qualidade_from_points(p_s2, p_o2, p_o1)<< std::endl;
            // std::cout << "*******************************" << std::endl;

            if(qualidade_depois > qualidade_antes)
            {
                CGL::Mesh::Halfedge_index h3 = mesh.next(h1);
                CGL::Mesh::Halfedge_index h4 = mesh.opposite(h1);
                h4 = mesh.next(h4);

                CGAL::Euler::join_face(h1, mesh);
                CGAL::Euler::split_face(h3, h4, mesh);

                melhoria_global = true; 
            }
        }
    }
    std::cout << "Otimizacao concluida em " << iteracoes << " iteracoes." << std::endl;
}



int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " input.obj" << std::endl;
        return EXIT_FAILURE;
    }

    CGL::Mesh polygon = CGL::read_mesh(argv[1]);


    //CGL::print_mesh(polygon);

    CGAL::draw(polygon);
    CGL::polygon_2_triangulate_naive(polygon);    
    CGAL::draw(polygon);

    //CGL::print_mesh(polygon);

   

    MelhorarMalha(polygon);
    CGAL::draw(polygon);

    return EXIT_SUCCESS;
}

