#include "renderer/VertexBuffer2D.h"
#include "utils/Assert.h"

using namespace Niski::Renderer;

const int32_t VertexBuffer2D::FVF = int32_t(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

VertexBuffer2D::VertexBuffer2D(void) : color_(255, 255, 255, 255), vertexCount_(0), primitiveType_(invalidPrimitiveType)
{}

VertexBuffer2D::~VertexBuffer2D(void)
{}

//
// Just a helper function. 
void VertexBuffer2D::pushVertex(int32_t x, int32_t y, float u, float v)
{
	pushVertex(float(x), float(y), u, v);
}

void VertexBuffer2D::pushVertex(float x, float y, float u /* = 0.0f */, float v /* = 0.0f */)
{
	VertexFormat2D vertex;
	vertex.x = x - 0.5f;
	vertex.y = y - 0.5f;
	vertex.z = 0.5f;
	vertex.color = D3DCOLOR_ARGB(color_.a, color_.r, color_.g , color_.b);
	vertex.u = u;
	vertex.v = v;
	vertex.rhw = 1.0f;

	if(vertexCount_ <= maxVerts)
	{
		vertices_[vertexCount_] = vertex;

		vertexCount_++;
	}
	else
	{
		Niski::Utils::Assert(false, "Our vertex buffer overflowed!", __FILE__, __FUNCSIG__, __LINE__);
	}
}

void VertexBuffer2D::pushVertex(double x, double y, float u /* = 0.0f */, float v /* = 0.0f */)
{
	//
	// TODO: Dunno how misleading this method is, since the extra precision
	// of the double is just discarded, but whatever.
	pushVertex(float(x), float(y), u, v);
}

void VertexBuffer2D::pushTexturedRectangle(Niski::Math::Rect2D& rect, float u, float v, float u2, float v2)
{
	pushVertex(rect.left, rect.top, u, v);
	pushVertex((rect.left + rect.right), rect.top, u2, v);
	pushVertex(rect.left, (rect.top + rect.bottom), u, v2);

	pushVertex((rect.left + rect.right), rect.top, u2, v);
	pushVertex((rect.left + rect.right), (rect.top + rect.bottom), u2, v2);
	pushVertex(rect.left, (rect.top + rect.bottom), u, v2);
}

void VertexBuffer2D::pushRectangle(Niski::Math::Rect2D& rect)
{
	pushVertex(rect.left, rect.top);
	pushVertex((rect.left + rect.right), rect.top);
	pushVertex(rect.left, (rect.top + rect.bottom));

	pushVertex((rect.left + rect.right), rect.top);
	pushVertex((rect.left + rect.right), (rect.top + rect.bottom));
	pushVertex(rect.left, (rect.top + rect.bottom));
}

void VertexBuffer2D::setColor(const Niski::Utils::Color& color)
{
	color_ = color;
}

Niski::Utils::Color VertexBuffer2D::getColor(void) const
{
	return color_;
}

size_t VertexBuffer2D::numVertices(void)
{
	return vertexCount_;
}

VertexBuffer2D::VertexFormat2D* VertexBuffer2D::getFirstVertex(void)
{
	return &vertices_[0];
}

void VertexBuffer2D::flushVertices(void)
{
	vertexCount_ = 0;
}

void VertexBuffer2D::render(Renderer& renderer)
{
	D3DPRIMITIVETYPE d3dPrimType;
	int16_t vertexCount = vertexCount_;

	switch(primitiveType_)
	{
	case pointList:
		d3dPrimType = D3DPT_POINTLIST;
		break;

	case lineList:
		d3dPrimType = D3DPT_LINELIST;
		break;

	case lineStrip:
		d3dPrimType = D3DPT_LINESTRIP;
		break;

	case triangleList:
		d3dPrimType = D3DPT_TRIANGLELIST;
		vertexCount = vertexCount_ / 3;
		break;

	case triangleStrip:
		d3dPrimType = D3DPT_TRIANGLESTRIP;
		break;

	case triangleFan:
		d3dPrimType = D3DPT_TRIANGLEFAN;
		break;

	case invalidPrimitiveType:
	default:
		//
		// TODO: Throw
		break;
	}

	//
	// Check if the current fvf is the same as the one we want to set
	// this way we can skip a function call, easily. 
	DWORD currentFVF;

	renderer.getNativeRenderer()->GetFVF(&currentFVF);

	if(currentFVF != FVF)
	{
		renderer.getNativeRenderer()->SetFVF(FVF);
	}

	renderer.getNativeRenderer()->DrawPrimitiveUP(d3dPrimType, vertexCount, getFirstVertex(), sizeof(Niski::Renderer::VertexBuffer2D::VertexFormat2D));

	if(currentFVF != FVF)
	{
		renderer.getNativeRenderer()->SetFVF(currentFVF);
	}
}