#include "pch.h"
#include "MyRectangle.h"
#include "MyCircle.h"
#include "MyEllipse.h"
#include "Figure.h"

#include "MyLine.h"
#include "MyTriangle.h"



IMPLEMENT_SERIAL(MyRectangle, MyLine, 1)

IMPLEMENT_SERIAL(MyEllipse, Figure, 1)

IMPLEMENT_SERIAL(MyCircle, MyEllipse, 1)

IMPLEMENT_SERIAL(MyTriangle, MyLine, 1)

IMPLEMENT_SERIAL(MyLine, Figure, 1)


