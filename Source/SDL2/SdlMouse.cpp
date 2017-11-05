#include "SDL2/SdlMouse.h"

#include "Types.h"

namespace Core
{
SdlMouse::SdlMouse()
{
	mX = mY = mRelX = mRelY = mWheelScroll = 0;
	mClicks[0] = mClicks[1] = mClicks[2] = 0;
}

//Absolute position setters
void SdlMouse::SetX(int32 x) { mX = x; }
void SdlMouse::SetY(int32 y) { mY = y; }
void SdlMouse::SetPosition(int32 x, int32 y) { mX = x; mY = y; }

//Relative position setters
void SdlMouse::SetRelX(int32 relx) { mRelX = relx; }
void SdlMouse::SetRelY(int32 rely) { mRelY = rely; }
void SdlMouse::SetRelativePosition(int32 relx, int32 rely) { mRelX = relx; mRelY = rely; }

/**
 * Sets the click count for each mouse button,
 * where 0 is not clicked, 1 is single click, 2 is a double click ...
 *
 * @param left int representing left button click count
 * @param middle int representing middle button click count
 * @param right int representing right button click count
 */
void SdlMouse::SetClicks(int32 left, int32 middle, int32 right)
{
	mClicks[0] = left;
	mClicks[1] = middle;
	mClicks[2] = right;
}

void SdlMouse::SetWheelScroll(int32 amount) { mWheelScroll = amount; }

/**
 * Sets the click count for the left mouse button,
 * where 0 is not clicked, 1 is single click, 2 is a double click ...
 *
 * @param left int representing left button click count
 */
void SdlMouse::SetLeftClicks(int32 left) { mClicks[0] = left; }

/**
 * Sets the click count for the middle mouse button,
 * where 0 is not clicked, 1 is single click, 2 is a double click ...
 *
 * @param middle int representing middle button click count
 */
void SdlMouse::SetMiddleClicks(int32 middle) { mClicks[1] = middle; }

/**
 * Sets the click count for the right mouse button,
 * where 0 is not clicked, 1 is single click, 2 is a double click ...
 *
 * @param right int representing right button click count
 */
void SdlMouse::SetRightClicks(int32 right) { mClicks[2] = right; }

//Getters for absolute position
int32 SdlMouse::GetX() { return mX; }
int32 SdlMouse::GetY() { return mY; }

//Getters for relative position
int32 SdlMouse::GetRelX() { return mRelX; }
int32 SdlMouse::GetRelY() { return mRelY; }

//Getters for click status
int32 SdlMouse::GetLeftClicks() { return mClicks[0]; }
int32 SdlMouse::GetMiddleClicks() { return mClicks[1]; }
int32 SdlMouse::GetRightClicks() { return mClicks[2]; }

//Getter for wheel scroll
int32 SdlMouse::GetWheelScroll() { return mWheelScroll; }
}
