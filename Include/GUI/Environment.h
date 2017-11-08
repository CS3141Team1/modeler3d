#pragma once

#include "IWindow.h"
#include "GuiRenderer.h"
#include "Types.h"
#include "GUI/Widget.h"

namespace Gui
{

/**
 * Object to hold the root widget and maintain the updating
 * and drawing of the main environment of the application.
 *
 * @author Michael Conard
 */
class Environment
{
private:
    float32 mWidth;
    float32 mHeight;
	Widget* mRoot;

public:
	Environment(float32 w, float32 h) : mWidth(w), mHeight(h) { mRoot = new Widget(0, 0, w, h); }
	~Environment() { delete mRoot; }

	void SetSize(float32 w, float32 h)
	{
	    mWidth = w;
	    mHeight = h;
	    mRoot->SetBounds(0, 0, w, h);
	}

	/**
	 * Called when mouse is clicked, propagates MouseButton down descendants
	 *
	 * @param x an int representing the mouse click location, origin bottom left
	 * @param y an int representing the mouse click location, origin bottom left
	 * @param button an int representing which button was clicked, 1 = left, 2 = middle, 3 = right
	 * @param down a bool stating if the button was clicked or not (why do we have this?)
	 */
	void OnMouseButton(int32 x, int32 y, int32 button, bool down)
	{
//		std::cout << std::endl << "Environment OnMouseButton, " << mRoot->GetDescendantCount() << " descendants" << std::endl;

		mRoot->MouseButton(x, y, button, down);
//		std::cout << std::endl;
	}

	void OnMouseMove(int32 x, int32 y, int32 dx, int32 dy, uint32 buttons)
	{
	    mRoot->MouseMove(x, y, dx, dy, buttons);
	}

	/**
	 * Propagates the draw event down the children.
	 *
	 * @param g The Video::GuiRenderer
	 */
	void Draw(Video::GuiRenderer* g)
	{
		mRoot->Draw(g);
	}

	/**
	 * Propagates the update event down the children.
	 *
	 * @param dt a double that represents change in time
	 */
	void Update(float64 dt)
	{
	    mRoot->Update(dt);
	}

	/**
	 * Calls the update logic for root.
	 */
	void OnUpdate()
	{
		mRoot->OnUpdate(1.0/60);
	}

	/**
	 * Adds a widget to the end of root's children list.
	 *
	 * @param widget A Widget* to be added to root's children
	 */
	void AddWidget(Widget* widget)
	{
		mRoot->AddChild(widget);
	}

	/**
	 * Removes a widget from root's children.
	 *
	 * @param widget A Widget* to search for and remove if found
	 */
	void RemoveWidget(Widget* widget)
	{
		mRoot->RemoveChild(widget);
	}

	/**
	 * Returns the total number of widgets present in the environment.
	 *
	 * @return int the number of descendants
	 */
	int GetWidgetCount()
	{
		return mRoot->GetDescendantCount();
	}

	/**
	 * Returns a child widget from root.
	 *
	 * @param index a uint32 index that is the position in the child list to get
	 *
	 * @return Widget* The widget in root's child list at position i
	 */
	Widget* GetWidget(uint32 index)
	{
		return mRoot->GetChild(index);
	}

};

}
