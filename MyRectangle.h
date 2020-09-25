#pragma once

#include "MyLine.h"

class MyRectangle: public MyLine
{
public:
	DECLARE_SERIAL(MyRectangle)

	MyRectangle(){}

	MyRectangle(const CPoint& start, const CPoint& end, COLORREF c, COLORREF bgc):MyLine(start,end, c, bgc) {}

	virtual void draw(CDC* dc) const {
		//CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
		//CBrush brush(getCol());
		//CBrush* old = dc->SelectObject(&brush);
		//CPen* oldPen = dc->SelectObject(&pen);
		//innerDraw(dc);
		//dc->SelectObject(oldPen);
		//dc->SelectObject(old);
		////CPen pen(PS_SOLID, 3, getCol());
		//CBrush brush(getBg());
		//CBrush* oldB = dc->SelectObject(&brush);
		////CPen* old = dc->SelectObject(&pen);
		//innerDraw(dc);
		//dc->SelectObject(oldB);
		////dc->SelectObject(old);
	}
	void innerDraw(CDC* dc) const {
		dc->Rectangle(start.x, start.y, end.x, end.y);
	}



	virtual void Serialize(CArchive& archive)
	{
		MyLine::Serialize(archive);
	}
};
