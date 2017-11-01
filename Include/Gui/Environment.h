#pragma once

#include "Widget.h"
#include "GuiRenderer.h"
#include "Types.h"

namespace Gui
{

class Environment
{
private:
	Widget* mRoot;

public:
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

	Widget* GetWidget(uint32 index)
	{
		return mRoot->GetChild(index);
	}

	void Draw(Video::GuiRenderer* g)
	{
		mRoot->Draw(this, g);
	}

	void OnMouseButton(int32 x, int32 y, int32 button, bool down)
	{
		mRoot->OnMouseClick(this, x, y, button, down);
	}
};

}
