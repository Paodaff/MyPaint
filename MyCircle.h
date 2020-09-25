#pragma once

#include "MyEllipse.h"

class MyCircle : public MyEllipse {
public:
	DECLARE_SERIAL(MyCircle)

	MyCircle(){}

	MyCircle(const CPoint& start, const CPoint& end, COLORREF c, COLORREF bgc) :MyEllipse(start, end, c, bgc) {}

	virtual void draw(CDC* dc) const {}
	//void draw(CDC* dc) const{
	//	CPen pen(PS_SOLID, 3, getCol());
	//	CBrush brush(getBg());
	//	CBrush* oldB = dc->SelectObject(&brush);
	//	CPen* old = dc->SelectObject(&pen);
	//	innerDraw(dc);
	//	dc->SelectObject(oldB);
	//	dc->SelectObject(old);
	//}

	void innerDraw(CDC* dc) const {
		int value;
		if (abs(start.x - end.x) < abs(start.y - end.y))
			value = (start.x - end.x);
		else
			value = (start.y - end.y);
		dc->Ellipse(start.x, start.y, start.x-value, start.y-value);
	}


	virtual void Serialize(CArchive& archive)
	{
		Figure::Serialize(archive);
	}
};