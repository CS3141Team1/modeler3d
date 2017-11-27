#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "GuiRenderer.h"
#include "Types.h"

namespace Gui
{

/**
 * Object holding all of the logic for a widget.
 *
 * @author Michael Conard, Nicholas Hamilton
 */
class Widget
{
public:
    static const float64 LeftAlign;
    static const float64 RightAlign;
    static const float64 TopAlign;
    static const float64 BottomAlign;

	virtual ~Widget() {}

	Widget(float32 x = 0, float32 y = 0, float32 width = 0, float32 height = 0, float64 hAlign = Widget::LeftAlign, float64 vAlign = Widget::TopAlign) :
			mX(x),
			mY(y),
			mWidth(width),
			mHeight(height),
			mHAlign(hAlign),
			mVAlign(vAlign),
			mParent(nullptr),
			mChildren() {}

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
	bool MouseButton(float32 x, float32 y, int32 button, bool down);

	/**
	 * Virtual method for actual widgets to implement, to be called when the widget is clicked.
	 *
	 * @param x an int representing the x position of the click
	 * @param y an int representing the y position of the click
	 * @param button an in representing which button was clicked, 1 = left, 2 = middle, 3 = right
	 * @param down a bool representing if the button was down (why do we have this?)
	 */
	virtual void OnMouseButton(float32 x, float32 y, int32 button, bool down) {}

	bool MouseMove(int32 x, int32 y, int32 dx, int32 dy, uint32 buttons);

	virtual void OnMouseMove(int32 x, int32 y, int32 dx, int32 dy, uint32 buttons) {}

	/**
	 * Propagates the update event down the children.
	 *
	 * @param dt a double that represents change in time
	 */
	void Update(float64 dt);

	/**
	 * Calls the update logic for the widget.
	 */
	virtual void OnUpdate(float64 dt) {}

	/**
	 * Propagates the draw event down the children.
	 *
	 * @param graphics The Video::IgraphicsDevice*
	 * @param g The Video::GuiRenderer
	 */
	void Draw(Video::GuiRenderer* g);

	/**
	 * Contains the draw logic for the widget. To be implemented by real widgets.
	 *
	 * @param graphics The Video::IgraphicsDevice*
	 * @param g The Video::GuiRenderer
	 */
	virtual void OnDraw(Video::GuiRenderer* g) {}

	/**
	 * Focuses this widget to the front of the screen.
	 */
	void Focus();

	/**
	 * Adds a child to this widget at the end of it's child list.
	 *
	 * @param w a Widget* that is the new child
	 */
	void AddChild(Widget* w);

	/**
	 * Adds a child to this widget at a position in it's child list.
	 *
	 * @param w a Widget* that is the new child
	 * @param index a uint32 that is the position to add the child
	 */
	void AddChild(Widget* w, uint32 index);

	/**
	 * Searches for and removes a child from this widget.
	 *
	 * @param w the Widget* to search for and remove
	 */
	void RemoveChild(Widget* w);

	/**
	 * Sets with width and height of the widget.
	 *
	 * @param w a float that is the new width
	 * @param h a float that is the new height
	 */
	void SetSize(float32 w, float32 h);

	void SetAlignment(float32 h, float32 v);

	/**
	 * Sets with relative x and y position of the widget.
	 *
	 * @param s a float that is the new x position
	 * @param y a float that is the new y position
	 */
	void SetPosition(float32 x, float32 y);

	/**
	 * Sets the position and size of the widget
	 *
	 * @param s a float that is the new x position
	 * @param y a float that is the new y position
	 * @param w a float that is the new width
	 * @param h a float that is the new height
	 */
	void SetBounds(float32 x, float32 y, float32 w, float32 h);

	/**
	 * Checks if (x,y) is within the bounds of this widget.
	 *
	 * @param x the x position of the coordinate being checked
	 * @param y the y position of the coordinate being checked
	 *
	 * @return bool true if (x,y) is within the widget
	 */
	bool InBounds(float32 x, float32 y);

	float32 GetHAlign();
	float32 GetVAlign();
	float32 GetX();
	float32 GetY();
	float32 GetWidth();
	float32 GetHeight();
	Widget* GetParent();
	Widget* GetChild(uint32 i);
	uint32 GetChildCount();

	/**
	 * Recursively gets the children count to build total descendant count of this widget.
	 *
	 * @return uint32 the number of descendants from this widget
	 */
	uint32 GetDescendantCount();

private:
    /**
     * Changes the parent of this widget
     *
     * @param parent the Widget* that is the new parent
     */
    void SetParent(Widget* parent);

	void ComputePosition(float32& x, float32& y);

    float32 mX, mY, mWidth, mHeight;
    float32 mHAlign, mVAlign;
	Widget* mParent;
	std::vector<Widget*> mChildren;
};


}
