#pragma once

#include "framework.h"

class Figure : public CObject
{
protected:
	CPoint start;
	CPoint end;
	COLORREF bgColor, Color;
public:

	Figure() {}

	Figure(const CPoint& start, const CPoint& end, COLORREF c, COLORREF bgc)  {
		this->start = start;
		this->end = end;
		this->bgColor = bgc;
		this->Color = c;
	}

	void setStart(const CPoint& start) {
		this->start = start;
	}

	void setEnd(const CPoint& end) {
		this->end = end;
	}
	CPoint GetStart() { return this->start; }
	CPoint GetEnd() { return this->end; }
	virtual void Draw(CDC* dc) const// = 0;
	{
		CPen pen(PS_SOLID, 2, getCol());
		CBrush brush(getBg());
		CBrush* old = dc->SelectObject(&brush);
		CPen* oldPen = dc->SelectObject(&pen);
		innerDraw(dc);
		dc->SelectObject(oldPen);
		dc->SelectObject(old);
	}
	virtual void innerDraw(CDC* dc) const = 0;

	COLORREF getCol() const { return Color; }
	COLORREF getBg() const { return bgColor; }
	void setBg(COLORREF bgc) { bgColor = bgc; }

	virtual ~Figure() {}

	virtual void Redefine(CPoint p1, CPoint p2) { start = p1; end = p2; }

	virtual bool isInside(const CPoint& P) const {
		return (start.x <= P.x && P.x <= end.x || start.x >= P.x && P.x >= end.x) &&
			(start.y <= P.y && P.y <= end.y || start.y >= P.y && P.y >= end.y);
	}

	virtual void Shift(int dx, int dy) {
		start = start + CPoint(dx, dy);
		end = end + CPoint(dx, dy);
	}
	virtual void Resize(int k) {

		//start.x = start.x - k;
		//start.y = start.y + k;
		//end.x = end.x + k;
		//end.y = end.y - k;
		start = start - CPoint(k, k);
		end = end + CPoint(k, k);
	}
	virtual void Serialize(CArchive& archive)
	{
		CObject::Serialize(archive);
		
		if (archive.IsStoring()) {
			archive << start << end << bgColor;
		}
		else {
			archive >> start>> end >> bgColor;
		}
	}
};
