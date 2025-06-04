#pragma once
#include "../Common.h"

class Collision {
public:
	//2D‹éŒ`‚Ì“–‚½‚è”»’è
	static bool IsHitRect2D(int x1, int y1, int x_wight1, int y_hight1, int x2, int y2, int x_wight2, int y_hight2);

	//2D‰~Œ`‚Ì“–‚½‚è”»’è
	static bool IsHitCircle2D(int CircleX, int CirecleY, int CircleR, int Circle2X, int Circle2Y, int Circle2R);

	//3D‹éŒ`‚Ì“–‚½‚è”»’è
	static bool IsHitRect3D(VECTOR ACenterPos, VECTOR ASize, VECTOR BCenterPos, VECTOR BSize, bool isYLanding = true);

	//3D‹…‚Ì“–‚½‚è”»’è
	static bool IsHitCircle3D(VECTOR object1, float object1radus, VECTOR object2, float object2radius);
};
