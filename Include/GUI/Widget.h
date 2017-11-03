#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "GuiRenderer.h"
#include "Types.h"

namespace GUInterface
{

/**
 * Object holding all of the logic for a widget.
 *
 * @author Michael Conard
 */
class Widget
{
public:
	virtual ~Widget() {}

	Widget() : mX(0),mY(0),mWidth(0),mHeight(0),mParent(nullptr),mChildren(std::vector<Widget*>()) {}
	Widget(int32 x, int32 y, int32 width, int32 height) : mX(x),mY(y),mWidth(width),mHeight(height),mParent(nullptr),mChildren(std::vector<Widget*>()) {}
	Widget(int32 x, int32 y, int32 width, int32 height, Widget* parent) : mX(x),mY(y),mWidth(width),mHeight(height),mParent(parent),mChildren(std::vector<Widget*>()) {}

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
	bool MouseButton(int32 x, int32 y, int32 button, bool down)
	{
		for(uint32 i = 0; i < mChildren.size(); i++)
		{
			if(GetChild(i)->MouseButton(x-mX,y-mY,button,down))
				return true;
		}
		bool bounds = InBounds(x,y);
		if (bounds) OnMouseButton(x, y, button, down);
		return bounds;
	}

	/**
	 * Virtual method for actual widgets to implement, to be called when the widget is clicked.
	 *
	 * @param x an int representing the x position of the click
	 * @param y an int representing the y position of the click
	 * @param button an in representing which button was clicked, 1 = left, 2 = middle, 3 = right
	 * @param down a bool representing if the button was down (why do we have this?)
	 */
	virtual void OnMouseButton(int32 x, int32 y, int32 button, bool down) {}

	/**
	 * Propagates the update event down the children.
	 *
	 * @param dt a double that represents change in time
	 */
	void Update(float64 dt)
	{
	    OnUpdate(dt);

	    for(uint32 i = 0; i < GetChildCount(); i++)
        {
            GetChild(i)->Update(dt);
        }
	}

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
	void Draw(Video::IGraphicsDevice* graphics, Video::GuiRenderer* g)
	{
		//Actually draws this widget
		OnDraw(graphics, g);

		//Moves the origin because children have position relative to this parent
		g->Translate(mX, mY);
		for (uint32 i = 0; i < GetChildCount(); i++)
		{
			//Draws the children
			GetChild(GetChildCount() - i - 1)->Draw(graphics, g);
		}
		//Translates the origin back
		g->Translate(-mX, -mY);
	}

	/**
	 * Contains the draw logic for the widget. To be implemented by real widgets.
	 *
	 * @param graphics The Video::IgraphicsDevice*
	 * @param g The Video::GuiRenderer
	 */
	virtual void OnDraw(Video::IGraphicsDevice* graphics, Video::GuiRenderer* g) {}

	/**
	 * Focuses this widget to the front of the screen.
	 */
	void Focus() {
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
	void AddChild(Widget* w)
	{
		AddChild(w, GetChildCount());
	}

	/**
	 * Adds a child to this widget at a position in it's child list.
	 *
	 * @param w a Widget* that is the new child
	 * @param index a uint32 that is the position to add the child
	 */
	void AddChild(Widget* w, uint32 index) {
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
	void RemoveChild(Widget* w)
	{
		mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), w), mChildren.end());
	}

	/**
	 * Changes the parent of this widget
	 *
	 * @param parent the Widget* that is the new parent
	 */
	void SetParent(Widget* parent)
	{
		mParent = parent;
	}

	/**
	 * Sets with width and height of the widget.
	 *
	 * @param w a float that is the new width
	 * @param h a float that is the new height
	 */
	void SetSize(float32 w, float32 h)
	{
		mWidth = w;
		mHeight = h;
	}

	/**
	 * Sets with relative x and y position of the widget.
	 *
	 * @param s a float that is the new x position
	 * @param y a float that is the new y position
	 */
	void SetPosition(float32 x, float32 y)
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
	void SetBounds(float32 x, float32 y, float32 w, float32 h)
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
	bool InBounds(float32 x, float32 y)
	{
		x = x - GetX();
		y = y - GetY();

		//std::cout << "X: " << x << ", Y: " << y << std::endl;

		if (x < 0 || x >= GetWidth()) return false;
		if (y < 0 || y >= GetHeight()) return false;

		return true;
	}

	float32 GetX() { return mX; }
	float32 GetY() { return mY; }
	float32 GetWidth() { return mWidth; }
	float32 GetHeight() { return mHeight; }
	Widget* GetParent() { return mParent; }
	Widget* GetChild(uint32 i) { return mChildren[i]; }
	uint32 GetChildCount() { return mChildren.size(); }

	/**
	 * Recursively gets the children count to build total descendant count of this widget.
	 *
	 * @return uint32 the number of descendants from this widget
	 */
	uint32 GetDescendantCount()
	{
		uint32 count = GetChildCount();
		for(uint32 i = 0; i < GetChildCount(); i++)
		{
			count += GetChild(i)->GetDescendantCount();
		}
		return count;
	}

private:
    float32 mX, mY, mWidth, mHeight;
	Widget* mParent;
	std::vector<Widget*> mChildren;
};


}
