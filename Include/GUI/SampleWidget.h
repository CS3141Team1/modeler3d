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

	void OnMouseButton(int32 x, int32 y, int32 button, bool down)
	{
		if (down)
		{
			this->Focus();
			SetColor((float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX);
			std::cout << "in a SampleWidget" << std::endl;
		}
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
