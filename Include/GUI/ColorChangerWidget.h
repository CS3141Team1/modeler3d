#pragma once

#include "Environment.h"
#include "Widget.h"

namespace GUInterface
{

class ColorChangerWidget : public Widget
{
public:
	ColorChangerWidget(int32 x, int32 y, int32 w, int32 h)
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
			SetColor((float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX);
			std::cout << "in a SampleWidget" << std::endl;
		}
	}

	void OnUpdate(float64 dt)
	{
	    // TODO
	    // NOT SAFE, position and size could drift due to
	    // floating point precision
	    mTime += dt;

	    if (mTime >= 1)
	    {
	        mTime -= 1;
	        mDir *= -1;
	    }

	    SetBounds(GetX() - 100 * dt * mDir, GetY() - 50 * dt * mDir, GetWidth() + 200 * dt * mDir, GetHeight() + 100 * dt * mDir);
	}

private:
	float64 mR = 0, mG = 0, mB = .5;
	float64 mTime = 0;
	int32 mDir = 1;
};

}
