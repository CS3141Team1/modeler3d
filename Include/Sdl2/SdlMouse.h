#pragma once

#include "IMouse.h"

namespace Core
{

class SdlMouse
{
private:
	int32 mX, mY, mRelX, mRelY;
	int32 mClicks[3];

public:
	SdlMouse()
	{
		mX = mY = mRelX = mRelY = 0;
		mClicks[0] = mClicks[1] = mClicks[2] = 0;
	}

	void SetX(int32 x) { mX = x; }
	void SetY(int32 y) { mY = y; }
	void SetPosition(int32 x, int32 y) { mX = x; mY = y; }
	void SetRelX(int32 relx) { mRelX = relx; }
	void SetRelY(int32 rely) { mRelY = rely; }
	void SetRelativePosition(int32 relx, int32 rely) { mRelX = relx; mRelY = rely; }

	void SetClicks(int32 left, int32 middle, int32 right)
	{
		mClicks[0] = left;
		mClicks[1] = middle;
		mClicks[2] = right;
	}
	void SetLeftClicks(int32 left) { mClicks[0] = left; }
	void SetMiddleClicks(int32 middle) { mClicks[1] = middle; }
	void SetRightClicks(int32 right) { mClicks[2] = right; }

	int32 GetX() { return mX; }
	int32 GetY() { return mY; }
	int32 GetRelX() { return mRelX; }
	int32 GetRelY() { return mRelY; }

	int32 GetLeftClicks() { return mClicks[0]; }
	int32 GetMiddleClicks() { return mClicks[1]; }
	int32 GetRightClicks() { return mClicks[2]; }
};

}
