#pragma once

#include "IMouse.h"
#include "Types.h"

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
	int32 mWheelScroll;
	int32 mClicks[3];

public:
	SdlMouse();

	//Absolute position setters
	void SetX(int32 x);
	void SetY(int32 y);
	void SetPosition(int32 x, int32 y);

	//Relative position setters
	void SetRelX(int32 relx);
	void SetRelY(int32 rely);
	void SetRelativePosition(int32 relx, int32 rely);

	/**
	 * Sets the click count for each mouse button,
	 * where 0 is not clicked, 1 is single click, 2 is a double click ...
	 *
	 * @param left int representing left button click count
	 * @param middle int representing middle button click count
	 * @param right int representing right button click count
	 */
	void SetClicks(int32 left, int32 middle, int32 right);

	void SetWheelScroll(int32 amount);

	/**
	 * Sets the click count for the left mouse button,
	 * where 0 is not clicked, 1 is single click, 2 is a double click ...
	 *
	 * @param left int representing left button click count
	 */
	void SetLeftClicks(int32 left);

	/**
	 * Sets the click count for the middle mouse button,
	 * where 0 is not clicked, 1 is single click, 2 is a double click ...
	 *
	 * @param middle int representing middle button click count
	 */
	void SetMiddleClicks(int32 middle);

	/**
	 * Sets the click count for the right mouse button,
	 * where 0 is not clicked, 1 is single click, 2 is a double click ...
	 *
	 * @param right int representing right button click count
	 */
	void SetRightClicks(int32 right);

	//Getters for absolute position
	int32 GetX();
	int32 GetY();

	//Getters for relative position
	int32 GetRelX();
	int32 GetRelY();

	//Getters for click status
	int32 GetLeftClicks();
	int32 GetMiddleClicks();
	int32 GetRightClicks();

	//Getter for wheel scroll
	int32 GetWheelScroll();

	uint32 GetButtonFlags() const;
};

}
