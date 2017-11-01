#pragma once

#include "Environment.h"
#include "Widget.h"

namespace GUInterface
{

class SampleWidget : public Widget
{
public:
	SampleWidget(int32 x, int32 y, int32 w, int32 h)
		: Widget(x, y, w, h)
	{

	}

	void OnDraw(Video::GuiRenderer* g)
	{
		g->SetColor(0,0,.5);
		g->FillRect(GetX(), GetY(), GetWidth(), GetHeight());
	}

	bool OnMouseButton(int32 x, int32 y, int32 button, bool down)
	{
		if (down && InBounds(x, y))
		{
			this->Focus();
			return true;
		}
		return false;
	}
};

}
