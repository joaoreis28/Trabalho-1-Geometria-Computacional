
#include "Wurfel.h"

#include <iostream>
#include <algorithm> 
namespace Bib {

    

    int left2(CGL::Point2 p, CGL::Point2 q, CGL::Point2 r)
    {
        return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()) > 0;
    }

    int leftOn2(CGL::Point2 p, CGL::Point2 q, CGL::Point2 r)
    {
        return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()) >= 0;
    }

    int right2(CGL::Point2 p, CGL::Point2 q, CGL::Point2 r)
    {
        return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()) < 0;
    }

    int collinear2(CGL::Point2 p, CGL::Point2 q, CGL::Point2 r)
    {
        return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()) == 0;
    }

   
    int left3(CGL::Point3 p, CGL::Point3 q, CGL::Point3 r)
    {
        return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()) > 0;
    }

    int right3(CGL::Point3 p, CGL::Point3 q, CGL::Point3 r)
    {
        return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()) < 0;
    }

    int collinear3(CGL::Point3 p, CGL::Point3 q, CGL::Point3 r)
    {
        return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()) == 0;
    }

    int intersecPropria3(CGL::Segment3 s, CGL::Segment3 t)
    {
        if (collinear3(s[0], s[1], t[0]) || collinear3(s[0], s[1], t[1]) || collinear3(t[0], t[1], s[0]) || collinear3(t[0], t[1], s[1])) return 0;
        int a = left3(s[0], s[1], t[0]) xor left3(s[0], s[1], t[1]);
        int b = left3(t[0], t[1], s[0]) xor left3(t[0], t[1], s[1]);
        return a && b;
    }

    int intersecPropria2(CGL::Segment2 s, CGL::Segment2 t)
    {
        if (collinear2(s[0], s[1], t[0]) || collinear2(s[0], s[1], t[1]) || collinear2(t[0], t[1], s[0]) || collinear2(t[0], t[1], s[1])) return 0;
        int a = left2(s[0], s[1], t[0]) xor left2(s[0], s[1], t[1]);
        int b = left2(t[0], t[1], s[0]) xor left2(t[0], t[1], s[1]);
        return a && b;
    }

    int noMeio(int a, int b, int c)
    {
        return (std::min(a, b) <= c) && (c <= std::max(a, b));
    }

    int noSegmento(CGL::Point2 a, CGL::Point2 b, CGL::Point2 c)
    {
        return collinear2(a, b, c) && noMeio(a.x(), b.x(), c.x()) && noMeio(a.y(), b.y(), c.y());
    }

    int intersecImpropria2(CGL::Segment2 s, CGL::Segment2 t)
    {
        if (s[0] == t[0] || s[0] == t[1] || s[1] == t[0] || s[1] == t[1]) return 1;
        if (noSegmento(s[0], s[1], t[0]) || noSegmento(s[0], s[1], t[1]) || noSegmento(t[0], t[1], s[0]) || noSegmento(t[0], t[1], s[1])) return 1;
        return 0;
    }

    CGL::Point2 pontoInter2(CGL::Segment2 s, CGL:: Segment2 t)
    {
        // at + u = int
        //s[1].x() - t[1].x() = (s[0].x() - t[0].x()) * -1;

        double a1 = s[1].x() - s[0].x();
        double b1 = (t[1].x() -t[0].x()) * -1;
        double c1 = t[0].x() - s[0].x();
        //std::cout << a1 << " " << b1 << " " << c1 << "\n";

        double a2 = s[1].y() - s[0].y();
        double b2 = (t[1].y() -t[0].y()) * -1;
        double c2 = t[0].y() - s[0].y();
        //std::cout << a2 << " " << b2 << " " << c2 << "\n";


        double determinante = a1 * b2 - a2 * b1;
        double det_x = c1 * b2 - c2 * b1;
        double det_y = a1 * c2 - a2 * c1;

    
        double x = det_x / determinante;
        double y = det_y / determinante;

        double px = s[0].x() + (s[1].x() - s[0].x()) * x; 
        double py = t[0].y() + (t[1].y() - t[0].y()) * y; 

        return CGL::Point2(px,py);

    }

    
    
    int pontoEmPoligono(CGL::Point2 ponto, CGL::Polygon2 poligono, int nVertices)
    {
        
        for(int i = 0, j =nVertices; i < nVertices; j = i++) //i atual  j anterior
        {
            CGL::Point2 p1 = poligono[i];
            CGL::Point2 p2 = poligono[j];




        }
    }
    

    int sentidoAntiHorario(CGL::Polygon2 p, int nVertices)
    {
        double area = areaPoligono(p, nVertices);
        if(area >  0) return 1;
        else return 0;
    }

    double areaPoligono(CGL::Polygon2 poligono, int nVertices)
    {
        double soma = 0.0;

        // frmuula shoelace
        for(int i = 0 ; i < nVertices; i++)
        {
            CGL::Point2 p1 = poligono[i];
            CGL::Point2 p2 = poligono[(i + 1) % nVertices];
            soma += (p1.x() * p2.y()) - (p1.y() * p2.x());

        }

        return soma/2.0;
    }




    bool dentroTriangulo(CGL::Point2 p, CGL::Point2 t1, CGL::Point2 t2, CGL::Point2 t3)
    {
        bool left1 = Bib::left2(t1, t2, p);
        bool left2 = Bib::left2(t2, t3, p);
        bool left3 = Bib::left2(t3, t1, p);

        return left1 and left2 and left3;
    }




    bool diagonalie(int i, int j , CGL::Polygon2 P, int nVertices ) // testa se o P[i]-P[j] é uma diagonal de P
                                                                    // Não testa se a diagonal é interna ou externa, nem se já é uma aresta de P, é uma bosta isso
    {
        int k, k1;
        for(k =0 ; k < nVertices; k++)
        {
            k1 = (k +1) % nVertices;
            if (!( 
                (k == i ) || (k1 == i) ||
                (k == j)  || (k1 == j)
            ))
            {
                CGL::Segment2 s1 (P[i], P[j]);
                CGL::Segment2 s2 (P[k], P[k + 1]);
                //std::cout << Bib::intersecPropria2(s1, s2) << " : " << Bib::intersecImpropria2(s1, s2) << std::endl;

                if(Bib::intersecPropria2(s1, s2) || Bib::intersecImpropria2(s1, s2))
                    return false;
                
                    

            }
                

        }
        return true;
    }


    bool Incone(int i, int j , CGL::Polygon2 P, int nVertices )
    {
        int i1, in1; 
        i1 = (i + 1) % nVertices;
        in1 = (i + nVertices - 1) % nVertices;


        if(Bib::leftOn2(P[in1], P[i], P[i1]) ) // teste se P[i] é convexo
            return Bib::left2(P[i], P[j], P[in1]) && Bib::left2(P[j], P[i], P[i1]);
        else
            return !(Bib::leftOn2(P[i], P[j], P[i1])    &&   Bib::leftOn2(P[j], P[i], P[in1]));
    }


    bool diagonal (int i, int j, int nVertices, CGL::Polygon2 P)
    {
        return Bib::Incone(i, j, P, nVertices) && Bib::diagonalie(i, j, P, nVertices); // faz sentido chamar In cone primeiro
    }




   



    void ClipEar(int i, int n, CGL::Polygon2& P)
    {
        int k;
        for(k = i ; k < n-1 ;k++)
            P[k] = P[k + 1];
    }


    void triangular(int nVertices, CGL::Polygon2& P) // Complexidade O(n^3) 
    {
        int i, i1, i2;

        if(nVertices > 3)
        {
            for(i = 0; i < nVertices; i++)
            {
                i1 = (i + 1) % nVertices;
                i2 = (i + 2) % nVertices;
                if(Bib::diagonal(i, i2, nVertices, P))
                {
                    std::cout << P[i] << ":";
                    std::cout << P[i2] << std:: endl;
                    
                    Bib::ClipEar(i1, nVertices, P);
                    Bib::triangular(nVertices- 1, P);
                    break;
                }

            }
        }
    }



void ClipEar2(int idx, CGL::Polygon2 &P) {
    int n = (int)P.size();
    if (idx < 0 || idx >= n) return;
    for (int k = idx; k < n - 1; ++k) P[k] = P[k + 1];
    //P.pop_back();
}

void triangulate_n2(CGL::Polygon2 &P) {
    int n = (int)P.size();
    if (n < 3) return;

    std::vector<bool> ear(n, false);

    for (int i = 0; i < n; ++i) {
        int j = (i + 2) % n;
        ear[i] = Bib::diagonal(i, j, n, P);
    }

    while (P.size() > 3) {
        n = (int)P.size();

        int i = -1;
        for (int k = 0; k < n; ++k) {
            if (ear[k]) { i = k; break; }
        }
        if (i == -1) {
            std::cerr << "Erro: nenhum ear encontrado -- polígono pode não ser simples.\n";
            return;
        }

        // rotaciona para trazer o ear para a posição 0 (facilita índices)
        std::rotate(P.begin(), P.begin() + i, P.end());
        std::rotate(ear.begin(), ear.begin() + i, ear.end());
        // agora o ear está em ear[0], o vértice a remover é index 1, e o segundo ponto do diagonal é index 2

        // imprime a diagonal (P[0], P[2]) como parte da triangulação
        std::cout << "Diagonal: ";
        std::cout << P[0] << "  --  " << P[2] << "\n";

        // remove o vértice central da orelha (índice 1)
        ClipEar2(1, P);
        ear.erase(ear.begin() + 1); // manter ear vector consistente com P
        n = (int)P.size();

        // atualiza as ear flags que podem ter sido afetadas: as duas posições
        // vizinhas da remoção são indices 0 e 1 (se existirem)
        if (n >= 3) {
            ear[0] = Bib::diagonal(0, (0 + 2) % n, n, P);
            ear[1 % n] = Bib::diagonal(1 % n, (1 + 2) % n, n, P);
        }
        // loop continua até sobrar 3 vértices
    }

    // Opcional: imprimir o último triângulo (restantes 3 vértices)
    if (P.size() == 3) {
        std::cout << "Triângulo final: " << P[0] << " " << P[1] << " " << P[2] << "\n";
    }
}







void ClipEar3(int idx, int &n, CGL::Polygon2 &P) {
    if (idx < 0 || idx >= n) return; // proteção
    for (int k = idx; k < n - 1; ++k) {
        P[k] = P[k + 1]; // shift left
    }
    // Não chamamos pop_back(), apenas reduzimos n
    --n;
}

// Versão recursiva (sem alterar assinatura do livro exceto passar P por referência e n por referência)
void triangular3(int &nVertices, CGL::Polygon2 &P) {
    if (nVertices <= 3) {
        // opcional: imprimir triângulo final
        if (nVertices == 3) {
            std::cout << "Triângulo final: " << P[0] << " " << P[1] << " " << P[2] << "\n";
        }
        return;
    }

    for (int i = 0; i < nVertices; ++i) {
        int i1 = (i + 1) % nVertices;
        int i2 = (i + 2) % nVertices;

        // Bib::diagonal deve receber nVertices para considerar só P[0..nVertices-1]
        if (Bib::diagonal(i, i2, nVertices, P)) {
            // imprime diagonal encontrada
            std::cout << P[i] << '\t' << P[i2] << '\n';

            // remove o vértice central da orelha (i1) e decrementa nVertices
            Bib::ClipEar3(i1, nVertices, P); // usamos a versão que altera nVertices

            // chama recursivamente com novo nVertices
            Bib::triangular(nVertices, P);
            break;
        }
    }
}

} 





