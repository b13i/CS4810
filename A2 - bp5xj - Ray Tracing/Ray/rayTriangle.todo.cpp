#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){
    Point3D t0 = v[0]->position;
    Point3D t1 = v[1]->position;
    Point3D t2 = v[2]->position;

    Point3D line1 = t1 - t0;
    Point3D line2 = t2 - t0;

    plane.normal = line1.crossProduct(line2).unit();
}
double RayTriangle::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
    initialize();

    Point3D p0 = ray.position;
    Point3D V = ray.direction.unit();

    if ( V.dot( plane.normal ) == 0 )  return -1.0;  // Ray parallel to triangle plane 

    double t = -(plane.evaluate( p0 )) / ( V.dot( plane.normal ) );

    if ( t < 0.0 )  return -1.0;  // Triangle behind ray
    Point3D p = p0 + V*t;

    RayVertex t1, t2;
    for ( int i = 0; i < 2; i++ ) {
        t1 = *v[ i ];
        t2 = *v[ i+1 ];

        v1 = t1.position - p0;
        v2 = t2.position - p0;

        Point3D n1 = v2.crossProduct( v1 ).unit();

        if ( ((p-p0).dot(n1)) < 0 ) {  // Check if p within lines
            return -1.0;
        }
    }
    t1 = *v[ 2 ];
    t2 = *v[ 0 ];
    v1 = t1.position - p0;
    v2 = t2.position - p0;
    Point3D n3 = v2.crossProduct( v1 ).unit();
    if ( ((p-p0).dot(n3)) < 0 ) {  // Check if p within lines
        return -1.0;
    }

    iInfo.material = material;
    iInfo.iCoordinate = p;  
    iInfo.normal = plane.normal;
    iInfo.texCoordinate; 

	return t;
}
BoundingBox3D RayTriangle::setBoundingBox(void){
    Point3D pList[3];
    pList[0] = v[0]->position;
    pList[1] = v[1]->position;
    pList[2] = v[2]->position;

    return BoundingBox3D( pList, 3 );
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
