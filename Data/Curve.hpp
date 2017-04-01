//
//  Curve.h
//  Broadway_test
//
//  Created by Manuel Deneu on 10/10/14.
//  Copyright (c) 2014 Manuel Deneu. All rights reserved.
//

#ifndef __CLCurve__
#define __CLCurve__

#include <vector>

typedef enum
{
    PointMoveTo  = 0,
    PointLineTo  = 1,
    PointCurve   = 2,
    PointControl = 3

} PointType;

typedef enum
{
    CurveMoveTo  = 0,
    CurveLineTo  = 1,
    CurveCubicTo = 2,
    CurveQuadTo  = 3
    
} CurveType;



template <typename T>
class Curve //: public Object
{
public:
    
    static Curve* makeMoveTo(T toX , T toY)
    {
        Curve *c = new Curve( CurveMoveTo);
        c->addPoint( PointMoveTo , toX , toY );
        
        return c;
    }
    
    static Curve* makeLineTo(T toX , T toY)
    {
        Curve *c = new Curve( CurveLineTo);
        c->addPoint( PointLineTo , toX , toY );
        
        return c;
    }
    
    static Curve* makeQuadTo(T cpX , T cpY , T toX , T toY)
    {
        Curve *c = new Curve( CurveQuadTo );
        c->addPoint( PointControl , cpX , cpY );
        c->addPoint( PointCurve   , toX , toY );
        
        return c;
    }
    
    static Curve* makeCubicTo( T cp1X , T cp1Y , T cp2X , T cp2Y , T toX , T toY)
    {
        Curve *c = new Curve( CurveCubicTo );
        c->addPoint( PointControl , cp1X , cp1Y );
        c->addPoint( PointControl , cp2X , cp2Y );
        c->addPoint( PointCurve   , toX , toY );
        
        return c;
    }

    
    
    /* **** **** **** **** **** **** **** **** **** **** */
    class CurvePoint
    {
        friend class Curve;
        
    public:

        CurvePoint(PointType type, T x , T y):
            m_x    ( x ),
            m_y    ( y ),
            m_type ( type )
        {}
        
        ~CurvePoint()
        {}
        
        T getX() const
        {
            return m_x;
        }
        
        T getY() const
        {
            return m_y;
        }
        
        PointType getType() const
        {
            return m_type;
        }
        
    protected:
        T m_x;
        T m_y;
        
        PointType m_type;
    
    };
    /* **** **** **** **** **** **** **** **** **** **** */


    Curve( CurveType type) :
        m_curveType( type )
    {
//        className = "Curve";
    }
    
    ~Curve()
    {
        m_points.clear();
    }
    
    unsigned long addPoint( PointType type , T x , T y)
    {
        m_points.push_back ( CurvePoint(type , x , y) );
        
        return getNumPoints();
    }
    
    size_t getNumPoints() const noexcept
    {
        return m_points.size();
    }
    
    CurvePoint getPointAt( size_t index) const
    {
        return m_points.at( index );
    }
    
    CurveType getCurveType() const noexcept
    {
        return m_curveType;
    }
    
protected:
    CurveType m_curveType;
    std::vector< CurvePoint > m_points;
};

typedef Curve<float> Curve_float;

#endif /* defined(__CLCurve__) */
