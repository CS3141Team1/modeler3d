#pragma once

#include "Environment.h"
#include "Widget.h"

namespace GUInterface
{

class RootWidget : public Widget
{
public:
	RootWidget(int32 x, int32 y, int32 w, int32 h)
		: Widget(x, y, w, h)
	{

	}

	void OnDraw(Video::GuiRenderer* g) { }

	bool OnMouseButton(int32 x, int32 y, int32 button, bool down)
	{
		if (down && InBounds(x, y))
		{
//			this->Focus();
			std::cout << "in RootWidget\n";
			return true;
		}
		return false;
	}

	void OnUpdate(float dt)
	{
		for(uint32 i = 0; i < GetChildCount(); i++)
		{
			GetChild(i)->OnUpdate(1.0/60);
		}

	}

private:
	float64 mR = 0, mG = 0, mB = .5;
};

}
