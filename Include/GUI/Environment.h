#pragma once

#include "GuiRenderer.h"
#include "Types.h"
#include "Widget.h"

namespace GUInterface
{

class Environment
{
private:
	Widget* mRoot;
	Video::IGraphicsDevice* mGraphics = nullptr;

public:
	Environment(Widget* root) { mRoot = root; }

	void AddWidget(Widget* widget)
	{
		mRoot->AddChild(widget);
	}

	void RemoveWidget(Widget* widget)
	{
		mRoot->RemoveChild(widget);
	}

	int GetWidgetCount()
	{
		return mRoot->GetChildCount();
	}

	void SetRoot(Widget* widget)
	{
		mRoot = widget;
	}

	void SetGraphics(Video::IGraphicsDevice* g) { mGraphics = g; }

	void OnUpdate()
	{
		mRoot->OnUpdate(1.0/60);
	}

	Widget* GetRoot()
	{
		return mRoot;
	}

	Widget* GetWidget(uint32 index)
	{
		return mRoot->GetChild(index);
	}

	void Draw(Video::GuiRenderer* g)
	{
		mRoot->Draw(mGraphics, g);
	}

	void OnMouseButton(int32 x, int32 y, int32 button, bool down)
	{
		std::cout << "Environment OnMouseButton, " << mRoot->GetChildCount() << " children\n";

		if(mRoot->OnMouseClick(x, y, button, down))
		{
			mRoot->SetColor((float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX);
		}
	}
};

}
