#include <vector>
#include <string>
#include <memory>

#include "renderer/Renderer.h"

class IApplication
{
public:
	typedef std::vector<std::string> commandLineArgs;

public:
	IApplication(const commandLineArgs& args);
	~IApplication(void);

	void initializeEverything(void);
	void run(void);

	void alert(const std::string& message);

private:
	std::shared_ptr<Niski::Renderer::RenderWindow*> renderWindow_;
	std::shared_ptr<Niski::Renderer::Renderer*> renderer_;
	commandLineArgs args_;
};

IApplication::IApplication(const commandLineArgs& args) : args_(args)
{
	//
	// Load configuration data
}

IApplication::~IApplication(void)
{
	//
	//
}

void IApplication::initializeEverything(void)
{
	try
	{
		renderWindow_ = std::make_shared<Niski::Renderer::RenderWindow*>(new Niski::Renderer::RenderWindow(L"Niski Application", Niski::Math::Rect2D(0, 0, 720, 1280), Niski::Renderer::RenderWindow::hasBorder));
		renderer_ = std::make_shared<Niski::Renderer::Renderer*>(new Niski::Renderer::Renderer(*renderWindow_, Niski::Math::Vector2D<uint16_t>(renderWindow_->getDimensions().right, )));
	}
	catch(...)
	{

	}
}