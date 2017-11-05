#pragma once

namespace Core
{

/**
 * Interface for a Mouse object implementation.
 *
 * @author Michael Conard
 */
class IMouse
{
public:
	virtual ~IMouse();

	virtual void SetX(int32 x) = 0;
	virtual void SetY(int32 y) = 0;
	virtual void SetPosition(int32 x, int32 y) = 0;

	virtual void SetRelX(int32 relx) = 0;
	virtual void SetRelY(int32 rely) = 0;
	virtual void SetRelativePosition(int32 x, int32 y) = 0;

	virtual void SetClicks(int32 left, int32 middle, int32 right) = 0;
	virtual void SetLeftClicks(int32 left) = 0;
	virtual void SetMiddleClicks(int32 middle) = 0;
	virtual void SetRightClicks(int32 right) = 0;

	virtual int32 GetX() const = 0;
	virtual int32 GetY() const = 0;
	virtual int32 GetRelX() const = 0;
	virtual int32 GetRelY() const = 0;
	virtual int32 GetLeftClicks() const = 0;
	virtual int32 GetMiddleClicks() const = 0;
	virtual int32 GetRightClicks() const = 0;
};

}
