#include "gui/Base.h"
#include "gui/Label.h"

namespace Niski
{
	namespace GUI
	{
		class TitleBar : public Base
		{
		public:
			TitleBar(Base* parent, const std::wstring& title);
			~TitleBar(void);

			void			setTitle(const std::wstring& title);
			std::wstring	getTitle(void) const;

		private:
			Label* label_;
		};
	}
}

using namespace Niski::GUI;

TitleBar::TitleBar(Base* parent, const std::wstring& title) : Base(parent, "TitleBar")
{
	label_ = new Label(this, "titleBarLabel", Niski::Math::Vector2D<int32_t>(0, 0), L"Arial", 14);
	label_->setText(title);
}

TitleBar::~TitleBar(void)
{
	// ...
}

void TitleBar::setTitle(const std::wstring& title)
{
	label_->setText(title);
}

std::wstring TitleBar::getTitle(void) const
{
	return label_->getText();
}