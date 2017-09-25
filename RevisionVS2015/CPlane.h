//CPlane.h, header file for CPlane class

//system includes---
//------------------

#ifndef _CPlane_h_
#define _CPlane_h_

// header files---------
#include "CVector.h"
//----------------------

//defines---------------
#define SMALL_VAL 0.00001f // a very small value 
// floating point equality check, within the bounds of a very small differance
#define FEQUALS(N1, N2) ( fabs(N1 - (N2)) < SMALL_VAL) ? true : false
//----------------------

// plane class
class CPlane              
{
	public:
		CPlane(){ planeConstant = 0.0f;} // constructor

		// VECTOR, MATRIX, QUAT REVISION
		// constructor (presumes the normal is normalised)
		CPlane(const CVector& normal, const CVector& pointOnSurface)
		{
			planeNormal = normal;
			CalculatePlaneConstant(pointOnSurface);
		}

		// VECTOR, MATRIX, QUAT REVISION
		// constructor
		CPlane(CVector * triangleVertices)
		{
			planeNormal.crossProduct(&triangleVertices[0], &triangleVertices[1], 
									&triangleVertices[2]);
			planeNormal.normalise();
			CalculatePlaneConstant(triangleVertices[0]);
		}

		// VECTOR, MATRIX, QUAT REVISION
		void CalculatePlaneConstant(CVector pointOnPlane)
		{
			// use the plane equation to find the distance/planeConstant (Ax + By + Cz + D = 0)
			// D = -(Ax + By + Cz)
			planeConstant = -(planeNormal.dotProduct(pointOnPlane));
		}

		// VECTOR, MATRIX, QUAT REVISION
		CVector CalculatePointOnPlane()
		{
			return planeNormal *= -planeConstant;
		}

		// VECTOR, MATRIX, QUAT REVISION
		// normalise the plane
		void normalise()
		{
			float magnitude = planeNormal.getMagnitude(); // get normals magnitude

			planeNormal /= magnitude; // normalise plane normal
			planeConstant /= magnitude; // normalise plane constant
		}

		// is this plane the same as another plane
		bool operator==(const CPlane &p)
		{
			double	x = planeNormal.x, px = p.planeNormal.x,
					y = planeNormal.y, py = p.planeNormal.y,
					z = planeNormal.z, pz = p.planeNormal.z;

			return( ( FEQUALS(x, px) ) &&
					( FEQUALS(y, py) ) &&
					( FEQUALS(z, pz) ) );
		}

		// is this a different plane to another plane
		bool operator!=(const CPlane &p)
		{
			return((!( (*this) == p )));
		}	
	
		// copy constructor
		CPlane(const CPlane& aPlane)
		{
			*this = aPlane;
		}
	
		// make plane the same as another plane
		CPlane& operator=(const CPlane *p)
		{
			planeNormal = p->planeNormal;			
			planeConstant = p->planeConstant;
			return(*this);
		}

		// VECTOR, MATRIX, QUAT REVISION
		// this returns the point on a plane which a line segment intersects
		bool planeIntersectionPoint(const CVector& startLine, const CVector& endLine, CVector& intersectionPoint)
		{
			// using the plane equation: Ax + By + Cz + D = 0, get the distance the start of the line is from the plane
			float startDist = planeNormal.dotProduct(startLine) + planeConstant;
			// using the plane equation: Ax + By + Cz + D = 0, get the distance the end of the line is from the plane
			float endDist = planeNormal.dotProduct(endLine) + planeConstant;

			if (startDist * endDist <= 0.0f) // start and end of line are on opposite sides of the plane
			{				
				CVector unitLine = (endLine - startLine).normalise(); // get the normalalised line vector
				CVector adjacentSideNormal = startDist > 0.0f ? -planeNormal : planeNormal;

				// below, think of startDist & adjacentSideNormal and hypotenuseLength & unitLine representing the direction and magnitude of two sides of a triangle. 
				// cosineOfAngle is the cosine of the angle between those two sides. startDist & adjacentSideNormal would be the adjacent side, dist & unitLine
				// would be the hypotenuse, therefore hypotenuseLength is calculated through CAH - cosine(angle) = adjacent/hypotenuse, so hypotenuse = adjacent/cosine(angle)

				float cosineOfAngle = adjacentSideNormal.dotProduct(unitLine); // dot product gives us cosine(angle)
				float hypotenuseLength = startDist / (0 == cosineOfAngle ? 1.0f : cosineOfAngle); // hypotenuse = adjacent/cosine(angle)
				intersectionPoint = startLine + unitLine * hypotenuseLength; // return the intersection point
				return true;
			}
			return false;
		}

		CVector planeNormal;		
		float planeConstant;
};

#endif