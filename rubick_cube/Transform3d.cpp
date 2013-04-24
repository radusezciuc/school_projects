#pragma once
#include "Transform3d.h"
#include "Support3d.h"

void Transform3d::translate(Point3d *pct, float tx, float ty, float tz){

	pct->x = pct->x + tx;
	pct->y = pct->y + ty;
	pct->z = pct->z + tz;
}

void Transform3d::rotateX(Point3d *pct, float angleInRadians){
	
	float auxy = pct->y;
	pct->y = auxy * cos(angleInRadians) - pct->z * sin(angleInRadians);
	pct->z = auxy * sin(angleInRadians) + pct->z * cos(angleInRadians);

}

void Transform3d::rotateY(Point3d *pct, float angleInRadians){
	
	float auxx = pct->x;
	pct->x = auxx * cos(angleInRadians) - pct->z * sin(angleInRadians);
	pct->z = auxx * sin(angleInRadians) + pct->z * cos(angleInRadians);

}
void Transform3d::rotateZ(Point3d *pct, float angleInRadians){

	float auxx = pct->x;
	pct->x = auxx * cos(angleInRadians) - pct->y * sin(angleInRadians);
	pct->y = auxx * sin(angleInRadians) + pct->y * cos(angleInRadians);
	
}

void Transform3d::rotateXRelativeToAnotherPoint(Point3d *pct, Point3d *ref, float angleInRadians){

	pct->translate(-ref->x,-ref->y,-ref->z);
	pct->rotateXRelativeToOrigin(angleInRadians);
	pct->translate(ref->x,ref->y,ref->z);
	
}
void Transform3d::rotateYRelativeToAnotherPoint(Point3d *pct, Point3d *ref, float angleInRadians){

	pct->translate(-ref->x,-ref->y,-ref->z);
	pct->rotateYRelativeToOrigin(angleInRadians);
	pct->translate(ref->x,ref->y,ref->z);
	
	
}
void Transform3d::rotateZRelativeToAnotherPoint(Point3d *pct, Point3d *ref, float angleInRadians){

	pct->translate(-ref->x,-ref->y,-ref->z);
	pct->rotateZRelativeToOrigin(angleInRadians);
	pct->translate(ref->x,ref->y,ref->z);
	
}
void Transform3d::scale(Point3d *pct, float sx, float sy, float sz){

	pct->x = pct->x * sx;
	pct->y = pct->y * sy;
	pct->z = pct->z * sz;
	
}
void Transform3d::scaleRelativeToAnotherPoint(Point3d *pct, Point3d *ref, float sx, float sy, float sz){

	pct->translate(-ref->x,-ref->y,-ref->z);
	pct->scale(sx,sy,sz);
	pct->translate(ref->x,ref->y,ref->z);
	
}