#ifndef __RENDERER_VERTEXBUFFER2D_H__
#define __RENDERER_VERTEXBUFFER2D_H__

#include <vector>
#include "utils/Color.h"
#include "math/Rectangle.h"
#include "renderer/Renderer.h"
#include "renderer/VertexBuffer2D.h"

#ifdef ENABLE_DIRECTX
#	include <d3d9.h>
#	include <d3d9types.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>
#endif

namespace Niski
{
	namespace Renderer
	{
		class VertexBuffer2D
		{
		public:
			struct VertexFormat2D
			{
				float x, y, z, rhw;
				uint32_t color;
				float u, v;
			};

			enum PrimitiveType
			{
				invalidPrimitiveType = 0,
				pointList,
				lineList,
				lineStrip,
				triangleList,
				triangleStrip,
				triangleFan
			};
			
		public:
			static const int32_t FVF;
			static const int32_t maxVerts = 256;

		public:
			VertexBuffer2D(void);
			~VertexBuffer2D(void);

			void				pushVertex(int32_t x, int32_t y, float u = 0.0f, float v = 0.0f);
			void				pushVertex(float x, float y, float u = 0.0f, float v = 0.0f);
			void				pushVertex(double x, double y, float u = 0.0f, float v = 0.0f);

			void				pushTexturedRectangle(Niski::Math::Rect2D& rect, float u, float v, float u2, float v2);
			void				pushRectangle(Niski::Math::Rect2D& rect);

			void				setColor(const Niski::Utils::Color& color);
			Niski::Utils::Color getColor(void) const;

			size_t				numVertices(void);

			VertexFormat2D*		getFirstVertex(void);
			void				flushVertices(void);

			void				setPrimitiveType(PrimitiveType primitiveType) { primitiveType_ = primitiveType; }
			PrimitiveType		getPrimitiveType(void) const { return primitiveType_; }

			void				render(Niski::Renderer::Renderer& renderer);

		private:
			int16_t						vertexCount_;
			VertexFormat2D				vertices_[maxVerts];
			PrimitiveType				primitiveType_;
			Niski::Utils::Color			color_;
		};
	}
}

#endif