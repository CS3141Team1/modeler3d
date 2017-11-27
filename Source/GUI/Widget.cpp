#include "GUI/Widget.h"

#include "Types.h"

namespace Gui {

const float64 Widget::LeftAlign = 0.0;
const float64 Widget::RightAlign = 1.0;
const float64 Widget::TopAlign = 1.0;
const float64 Widget::BottomAlign = 0.0;

/**
 * Called when the mouse is clicked. Checks if a child consumed the click and then if it gets the click.
 *
 * @param x an int representing the x position of the click
 * @param y an int representing the y position of the click
 * @param button an in representing which button was clicked, 1 = left, 2 = middle, 3 = right
 * @param down a bool representing if the button was down (why do we have this?)
 *
 * @return bool if the click was consumed
 */
bool Widget::MouseButton(float32 x, float32 y, int32 button, bool down)
{
	float32 px, py;
	for (uint32 i = 0; i < mChildren.size(); i++) {
		GetChild(i)->ComputePosition(px, py);
		if (GetChild(i)->MouseButton(x - px, y - py, button, down))
			return true;
	}
	bool bounds = InBounds(x, y);
	if (bounds)
		OnMouseButton(x, y, button, down);
	return bounds;
}

bool Widget::MouseMove(int32 x, int32 y, int32 dx, int32 dy, uint32 buttons)
{
    float32 px, py;
    for (uint32 i = 0; i < mChildren.size(); i++) {
        GetChild(i)->ComputePosition(px, py);
        if (GetChild(i)->MouseMove(x - px, y - py, dx, dy, buttons))
            return true;
    }
    bool bounds = InBounds(x, y) || InBounds(x - dx, y - dy);
    if (bounds)
        OnMouseMove(x, y, dx, dy, buttons);
    return bounds;
}

/**
 * Propagates the update event down the children.
 *
 * @param dt a double that represents change in time
 */
void Widget::Update(float64 dt)
{
	OnUpdate(dt);

	for (uint32 i = 0; i < GetChildCount(); i++)
	{
		GetChild(i)->Update(dt);
	}
}

/**
 * Propagates the draw event down the children.
 *
 * @param graphics The Video::IgraphicsDevice*
 * @param g The Video::GuiRenderer
 */
void Widget::Draw(Video::GuiRenderer* g)
{
	//Actually draws this widget
	OnDraw(g);

	//Moves the origin because children have position relative to this parent

	float32 x, y;
	for (uint32 i = 0; i < GetChildCount(); i++)
	{
		GetChild(GetChildCount() - i - 1)->ComputePosition(x, y);

		g->Translate(x, y);
		//Draws the children
		GetChild(GetChildCount() - i - 1)->Draw(g);
		//Translates the origin back
		g->Translate(-x, -y);
	}
}

/**
 * Focuses this widget to the front of the screen.
 */
void Widget::Focus()
{
	Widget* w = this;

	while (w->GetParent() != nullptr)
	{
		w->GetParent()->AddChild(w, 0);
		w = w->GetParent();
	}
}

/**
 * Adds a child to this widget at the end of it's child list.
 *
 * @param w a Widget* that is the new child
 */
void Widget::AddChild(Widget* w)
{
	AddChild(w, GetChildCount());
}

/**
 * Adds a child to this widget at a position in it's child list.
 *
 * @param w a Widget* that is the new child
 * @param index a uint32 that is the position to add the child
 */
void Widget::AddChild(Widget* w, uint32 index)
{
	Widget* parent = w->GetParent();

	if (parent != nullptr)
	{
		parent->RemoveChild(w);
	}

	mChildren.insert(mChildren.begin() + index, w);
	w->SetParent(this);
}

/**
 * Searches for and removes a child from this widget.
 *
 * @param w the Widget* to search for and remove
 */
void Widget::RemoveChild(Widget* w)
{
	if (w->mParent != this)
		return;
	w->mParent = nullptr;
	mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), w),
			mChildren.end());
}

/**
 * Sets with width and height of the widget.
 *
 * @param w a float that is the new width
 * @param h a float that is the new height
 */
void Widget::SetSize(float32 w, float32 h)
{
	mWidth = w;
	mHeight = h;
}

void Widget::SetAlignment(float32 h, float32 v)
{
	mHAlign = h;
	mVAlign = v;
}

/**
 * Sets with relative x and y position of the widget.
 *
 * @param s a float that is the new x position
 * @param y a float that is the new y position
 */
void Widget::SetPosition(float32 x, float32 y)
{
	mX = x;
	mY = y;
}

/**
 * Sets the position and size of the widget
 *
 * @param s a float that is the new x position
 * @param y a float that is the new y position
 * @param w a float that is the new width
 * @param h a float that is the new height
 */
void Widget::SetBounds(float32 x, float32 y, float32 w, float32 h)
{
	SetPosition(x, y);
	SetSize(w, h);
}

/**
 * Checks if (x,y) is within the bounds of this widget.
 *
 * @param x the x position of the coordinate being checked
 * @param y the y position of the coordinate being checked
 *
 * @return bool true if (x,y) is within the widget
 */
bool Widget::InBounds(float32 x, float32 y)
{
	x = x - GetX();
	y = y - GetY();

	//std::cout << "X: " << x << ", Y: " << y << std::endl;

	if (x < 0 || x >= GetWidth())
		return false;
	if (y < 0 || y >= GetHeight())
		return false;

	return true;
}

float32 Widget::GetHAlign() { return mHAlign; }
float32 Widget::GetVAlign() { return mVAlign; }
float32 Widget::GetX() { return mX; }
float32 Widget::GetY() { return mY; }
float32 Widget::GetWidth() { return mWidth; }
float32 Widget::GetHeight() { return mHeight; }
Widget* Widget::GetParent() { return mParent; }
Widget* Widget::GetChild(uint32 i) { return mChildren[i]; }
uint32 Widget::GetChildCount() { return mChildren.size();}

/**
 * Recursively gets the children count to build total descendant count of this widget.
 *
 * @return uint32 the number of descendants from this widget
 */
uint32 Widget::GetDescendantCount()
{
	uint32 count = GetChildCount();
	for (uint32 i = 0; i < GetChildCount(); i++)
	{
		count += GetChild(i)->GetDescendantCount();
	}
	return count;
}

/**
 * Changes the parent of this widget
 *
 * @param parent the Widget* that is the new parent
 */
void Widget::SetParent(Widget* parent)
{
	mParent = parent;
}

void Widget::ComputePosition(float32& x, float32& y)
{
	// TODO might be wrong
	if (!mParent)
		return;

	float32 x1 = mParent->mX + mHAlign * (mParent->mWidth - mParent->mX);
	float32 y1 = mParent->mY + mVAlign * (mParent->mHeight - mParent->mY);

	int amtX = mHAlign <= 0.5 ? 0 : 1;
	int amtY = mVAlign <= 0.5 ? 0 : 1;

	float32 x2 = amtX * (mWidth + mX * 2);
	float32 y2 = amtY * (mHeight + mY * 2);

	x = x1 - x2;
	y = y1 - y2;
}

}
