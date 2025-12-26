/**
 * @file DrawSegments3.h  
 * @brief Segments drawing.
 *
 * Defines a class and function to draw a vector of 3D segments using CGAL basic viewer.
 *
 * \author Ricardo Dutra da Silva
 */


#ifndef DRAW_SEGMENTS_2_H
#define DRAW_SEGMENTS_2_H


#include<Types.h>
#include<CGAL/Qt/Basic_viewer_qt.h>
#include<CGAL/Qt/init_ogl_context.h>


namespace CGL
{

/**
 * @brief Segments viewer.
 *
 * Extends CGAL basic viewer to draw a vector of segments. 
 */ 
class SimpleSegments2ViewerQt : public CGAL::Basic_viewer_qt
{
    typedef Basic_viewer_qt Base; /**< CGAL basic viewer. */

    protected:
    std::vector<CGL::Segment2> s2; /**< Segments vector. */

    public:
    /** 
     * The constructor. 
     *
     * @param parent Qt Widget.
     * @param seg2 Vector of Segment3.
     * @param title Window title.
     */
    SimpleSegments2ViewerQt(QWidget* parent, std::vector<CGL::Segment2> seg2,  const char* title);

    protected:
    /** 
     * Add edges to the viewer. 
     * @param seg Segment2.
     */
    void compute_edge(CGL::Segment2& seg);
    
    /** 
     * Add vertices to the viewer. 
     * @param seg Segment2.
     */
    void compute_vertex(CGL::Segment2& seg);
    
    /** 
     * Add all elements. 
     */
    void compute_elements();

    /** 
     * Delegate events to base class. 
     *
     * @param e Event.
     * @return None.
     */
    virtual void keyPressEvent(QKeyEvent* e);
};


/**
 * @ingroup cgldraw
 * @brief Draw segments.
 *
 * Function to draw a list of 3D segments.
 *
 * @param s2 a lists of segments given as a vector<Segment2>.
 */
void draw(std::vector<CGL::Segment2> &s2);

}

#endif /* DRAW_SEGMENTS_2_H */
