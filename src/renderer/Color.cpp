#include "utils/Color.h"
#include "math/Math.h"

using namespace Niski::Utils;

Color::Color(int32_t inR, int32_t inG, int32_t inB, int32_t inA) : r(inR), g(inG), b(inB), a(inA)
{}

Color::Color(Colors color)
{
	//
	// All colors are fully opaque
	a = 255;

	switch(color)
	{
	case Color::black:
		r = 0;
		g = 0;
		b = 0;
		break;

	case Color::blue:
		r = 0;
		g = 0;
		b = 255;
		break;

	case Color::red:
		r = 255;
		g = 0;
		b = 0;
		break;

	case Color::green:
		r = 0;
		g = 255;
		b = 0;
		break;

	case Color::white:
	default:
		r = 255;
		g = 255;
		b = 255;
		break;
	}
}

Color::~Color(void)
{}

void Color::clamp(void)
{
	Niski::Math::clamp(r, 0, 255);
	Niski::Math::clamp(g, 0, 255);
	Niski::Math::clamp(b, 0, 255);
	Niski::Math::clamp(a, 0, 255);
}