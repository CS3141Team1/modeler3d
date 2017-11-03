#pragma once

#include "IMouse.h"

namespace Core
{

/**
 * An implementation of IMouse for SDL2.
 *
 * @author Michael Conard
 */
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

	//Absolute position setters
	void SetX(int32 x) { mX = x; }
	void SetY(int32 y) { mY = y; }
	void SetPosition(int32 x, int32 y) { mX = x; mY = y; }

	//Relative position setters
	void SetRelX(int32 relx) { mRelX = relx; }
	void SetRelY(int32 rely) { mRelY = rely; }
	void SetRelativePosition(int32 relx, int32 rely) { mRelX = relx; mRelY = rely; }

	/**
	 * Sets the click count for each mouse button,
	 * where 0 is not clicked, 1 is single click, 2 is a double click ...
	 *
	 * @param left int representing left button click count
	 * @param middle int representing middle button click count
	 * @param right int representing right button click count
	 */
	void SetClicks(int32 left, int32 middle, int32 right)
	{
		mClicks[0] = left;
		mClicks[1] = middle;
		mClicks[2] = right;
	}

	/**
	 * Sets the click count for the left mouse button,
	 * where 0 is not clicked, 1 is single click, 2 is a double click ...
	 *
	 * @param left int representing left button click count
	 */
	void SetLeftClicks(int32 left) { mClicks[0] = left; }

	/**
	 * Sets the click count for the middle mouse button,
	 * where 0 is not clicked, 1 is single click, 2 is a double click ...
	 *
	 * @param middle int representing middle button click count
	 */
	void SetMiddleClicks(int32 middle) { mClicks[1] = middle; }

	/**
	 * Sets the click count for the right mouse button,
	 * where 0 is not clicked, 1 is single click, 2 is a double click ...
	 *
	 * @param right int representing right button click count
	 */
	void SetRightClicks(int32 right) { mClicks[2] = right; }

	//Getters for absolute position
	int32 GetX() { return mX; }
	int32 GetY() { return mY; }

	//Getters for relative position
	int32 GetRelX() { return mRelX; }
	int32 GetRelY() { return mRelY; }

	//Getters for click status
	int32 GetLeftClicks() { return mClicks[0]; }
	int32 GetMiddleClicks() { return mClicks[1]; }
	int32 GetRightClicks() { return mClicks[2]; }
};

}
