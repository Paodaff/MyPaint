#pragma once

#include "Figure.h"

class MyEllipse : public Figure {
public:
	DECLARE_SERIAL(MyEllipse)

	MyEllipse() {}

	MyEllipse(const CPoint& start, const CPoint& end, COLORREF c,COLORREF bgc) :Figure(start, end, c, bgc){
	}
	virtual void draw(CDC* dc) const {}
	//void Draw(CDC* dc) const {
	//	CPen pen(PS_SOLID, 2, getCol());
	//	CBrush brush(getBg());
	//	CBrush* old = dc->SelectObject(&brush);
	//	CPen* oldPen = dc->SelectObject(&pen);
	//	innerDraw(dc);
	//	dc->SelectObject(oldPen);
	//	dc->SelectObject(old);
	//}

	void innerDraw(CDC* dc) const {
		dc->Ellipse(start.x, start.y, end.x, end.y);
	}


	virtual void Serialize(CArchive& archive)
	{
		Figure::Serialize(archive);
	}
};