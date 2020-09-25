#pragma once
#include "MyLine.h"
class MyTriangle : public MyLine
{
public:
	DECLARE_SERIAL(MyTriangle)
	MyTriangle(void) {};
	MyTriangle(CPoint p1, CPoint p2, COLORREF c, COLORREF bgc) :MyLine(start, end, c, bgc) {}
	~MyTriangle(void) {};


	virtual void draw(CDC* dc) const{}
	void innerDraw(CDC* dc) const {
		CPoint pts[3];
		pts[0].x = start.x;
		pts[0].y = start.y;

		pts[1].x = end.x;
		pts[1].y = start.y;

		pts[2].x = end.x;
		pts[2].y = end.y;

		dc->Polygon(pts, 3);

	}


	virtual void Serialize(CArchive& archive)
	{
		MyLine::Serialize(archive);
	}
};
