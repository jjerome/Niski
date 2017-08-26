#include "Utils/Rectangle.h"

using namespace Niski::Utils;

Rect2D::Rect2D(int inTop, int inLeft, int inBottom, int inRight) : top(inTop), left(inLeft), bottom(inBottom), right(inRight)
{}

Rect2D::Rect2D(const Rect2D& rect) : top(rect.top), left(rect.left), bottom(rect.bottom), right(rect.right)
{}

Rect2D::Rect2D(RECT rect) : top(rect.top), left(rect.left), bottom(rect.bottom), right(rect.right)
{}

Rect2D::~Rect2D(void)
{}

RECT Rect2D::toWin32Rect(void)
{
	RECT rect;
	rect.top = top;
	rect.left = left;
	rect.bottom = bottom;
	rect.right = right;

	return rect;
}