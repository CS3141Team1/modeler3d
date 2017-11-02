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
		g->SetColor(mR, mG, mB);
		g->FillRect(GetParent()->GetX() + GetX(), GetParent()->GetY() + GetY(), GetWidth(), GetHeight());
	}

	bool OnMouseButton(int32 x, int32 y, int32 button, bool down)
	{
		if (down && InBounds(x, y))
		{
			this->Focus();
			std::cout << "in widget\n";
			return true;
		}
		return false;
	}

	void OnUpdate(float dt)
	{
		for(uint32 i = 0; i < GetChildCount(); i++)
		{
			GetChild(i)->OnUpdate();
		}

	}

private:
	float64 mR = 0, mG = 0, mB = .5;
};

}
