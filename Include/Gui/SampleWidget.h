#pragma once

#include "Widget.h"
#include "Environment.h"

namespace Gui
{

class SampleWidget : public Widget
{
public:
	void OnDraw(Environment* e, Video::GuiRenderer* g)
	{
		g->SetColor(255,255,255);
		g->FillRect(GetX(), GetY(), GetWidth(), GetHeight());
	}

	bool OnMouseButton(Environment* e, int32 x, int32 y, int32 button, bool down)
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
