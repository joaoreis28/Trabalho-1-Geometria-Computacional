/**
 * @file DrawSegments3.cpp  
 * @brief Segments drawing.
 *
 * Implements a class and function to draw a vector of 3D segments using CGAL basic viewer.
 *
 * @author Ricardo Dutra da Silva
 */


#include <DrawSegments2.h>


CGL::SimpleSegments2ViewerQt::SimpleSegments2ViewerQt(QWidget* parent, std::vector<CGL::Segment2> seg2, const char* title = "Basic Segs2 Viewer") :
    //First draw: vertices, edges, faces, multi-color, no inverse normal
    Base(parent, title, true, true, false, false, true),
    s2(seg2)
{
    compute_elements();
}


void CGL::SimpleSegments2ViewerQt::compute_edge(CGL::Segment2& seg)
{
    add_segment(seg.source(), seg.target(), CGAL::IO::blue());
}


void CGL::SimpleSegments2ViewerQt::compute_vertex(CGL::Segment2& seg)
{
    add_point(seg.source(), CGAL::IO::red());
    add_point(seg.target(),CGAL::IO::red());
}


void CGL::SimpleSegments2ViewerQt::compute_elements()
{
    clear();
    for (auto itor = s2.begin(); itor != s2.end(); ++itor)
    {
        compute_vertex(*itor);
        compute_edge(*itor);
    }
}
    

void CGL::SimpleSegments2ViewerQt::keyPressEvent(QKeyEvent* e)
{
    Base::keyPressEvent(e);
}


void CGL::draw(std::vector<CGL::Segment2> &s2)
{
    CGAL::Qt::init_ogl_context(3, 3);
    int argc = 1;
    const char* argv[2] = { "segs3_viewer","\0" };
    QApplication app(argc, const_cast<char**>(argv));
    
    SimpleSegments2ViewerQt mainwindow(app.activeWindow(), s2, "Viewer");
    mainwindow.show();
    app.exec();
}
