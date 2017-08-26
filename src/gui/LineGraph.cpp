//
// My (poor) attempt at making a simple line graph widget..

#include "gui/Base.h"
#include "gui/Label.h"

namespace Niski
{
	namespace GUI
	{
		class LineGraph : public Base
		{
		public:
			LineGraph(Base* parent);
			~LineGraph(void);

			void precache(Niski::Renderer::Renderer& renderer);

			void addDataPoint(Niski::Math::Vector2D<float> dataPoint);

			void setLineColor(const Niski::Utils::Color& color);
			Niski::Utils::Color getLineColor(void) const;

			void setTitle(const std::wstring& name);
			std::wstring getTitle(void) const;

			void setAxisNameX(const std::wstring& name);
			std::wstring getAxisNameX(void) const;

			void setAxisNameY(const std::wstring& name);
			std::wstring getAxisNameY(void) const;

		private:
			Label*	title_;
			Label*	axisNameX_;
			Label*  axisNameY_;

			Niski::Utils::Color lineColor_;

			std::vector<Niski::Math::Vector2D<float> > dataPoints_;
		};
	}
}

using namespace Niski::GUI;

LineGraph::LineGraph(Base* parent) : Base(parent, "LineGraph"), lineColor_(Niski::Utils::Color::green)
{
	//
	// Initialize the fonts... 
	title_ = new Label(this, "lineGraphTitle", Niski::Math::Vector2D<int32_t>(0, 0), L"Arial", 12);
	axisNameX_ = new Label(this, "axisNameX", Niski::Math::Vector2D<int32_t>(0, 0), L"Arial", 12);
	axisNameY_ = new Label(this, "axisNameY", Niski::Math::Vector2D<int32_t>(0, 0), L"Arial", 12);
}

LineGraph::~LineGraph(void)
{
	//
}

void LineGraph::precache(Niski::Renderer::Renderer& renderer)
{
	//
	// Precache all the fonts..
	title_->precache(renderer);
	axisNameX_->precache(renderer);
	axisNameY_->precache(renderer);
}

void LineGraph::addDataPoint(Niski::Math::Vector2D<float> dataPoint)
{
	//
	// TODO: Should we sort whenever a data point is added?
	dataPoints_.push_back(dataPoint);
}

void LineGraph::setLineColor(const Niski::Utils::Color& color)
{
	lineColor_ = color;
}

Niski::Utils::Color LineGraph::getLineColor(void) const
{
	return lineColor_;
}

void LineGraph::setTitle(const std::wstring& name)
{
	title_->setText(name);
}

std::wstring LineGraph::getTitle(void) const
{
	return title_->getText();
}