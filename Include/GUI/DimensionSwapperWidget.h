#pragma once

#include "Environment.h"
#include "Widget.h"

namespace GUInterface
{

class DimensionSwapperWidget : public Widget
{
public:
	DimensionSwapperWidget(int32 x, int32 y, int32 w, int32 h)
		: Widget(x, y, w, h)
	{

	}

	void OnDraw(Video::IGraphicsDevice* graphics, Video::GuiRenderer* g)
	{
		g->SetColor(mR, mG, mB);
		g->FillRect(GetX(), GetY(), GetWidth() - 1, GetHeight() - 1);
	}

	void SetColor(float r, float g, float b)
	{
	    mR = r;
	    mG = g;
	    mB = b;
	}

	void OnMouseButton(int32 x, int32 y, int32 button, bool down)
	{
		if (down)
		{
			this->Focus();
			SetSize(GetHeight(),GetWidth());
			std::cout << "clicked in a DimensionSwapperWidget" << std::endl;
		}
	}

	void OnUpdate(float64 dt) {}

private:
	float64 mR = 0, mG = .5, mB = .5;
	float64 mTime = 0;
	int32 mDir = 1;
};

}
