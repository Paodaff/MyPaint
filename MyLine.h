#pragma once

#include "Figure.h"

class MyLine : public Figure {
public:
	DECLARE_SERIAL(MyLine)

	MyLine() {}

	MyLine(const CPoint& start, const CPoint& end, COLORREF c, COLORREF bgc) :Figure(start, end, c, bgc) {
	}
	virtual void draw(CDC* dc) const {}
//	virtual void Draw(CDC* dc) const {
		//CPen pen(PS_SOLID, 2, getCol());
		//CBrush brush(getBg());
		//CBrush* old = dc->SelectObject(&brush);
		//CPen* oldPen = dc->SelectObject(&pen);
		//innerDraw(dc);
		//dc->SelectObject(oldPen);
		//dc->SelectObject(old);
		//CPen pen(PS_SOLID, 3, getCol());
		//CPen* old = dc->SelectObject(&pen);
		//
		//innerDraw(dc);
		//dc->SelectObject(old);
//	}
	void innerDraw(CDC* dc) const {
		dc->MoveTo(start.x, start.y);
		dc->LineTo(end.x, end.y);;
	}

	virtual void Serialize(CArchive& archive)
	{
		Figure::Serialize(archive);
	}
};