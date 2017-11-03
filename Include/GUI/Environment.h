#pragma once

#include "GuiRenderer.h"
#include "Types.h"
#include "GUI/Widget.h"

namespace GUInterface
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
	Widget* mRoot;
	Video::IGraphicsDevice* mGraphics = nullptr;

public:
	Environment(Widget* root) { mRoot = root; }

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
		std::cout << std::endl << "Environment OnMouseButton, " << mRoot->GetDescendantCount() << " descendants" << std::endl;

		mRoot->MouseButton(x, y, button, down);
		std::cout << std::endl;
	}

	/**
	 * Propagates the draw event down the children.
	 *
	 * @param g The Video::GuiRenderer
	 */
	void Draw(Video::GuiRenderer* g)
	{
		mRoot->Draw(mGraphics, g);
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
	 * Changes the root widget of the environment.
	 *
	 * @param widget A Widget* that is the new root
	 */
	void SetRoot(Widget* widget)
	{
		mRoot = widget;
	}

	/**
	 * Sets the Video::IGraphicsDevice for the environment.
	 *
	 * @param g The Video::IGraphicsDevice*
	 */
	void SetGraphics(Video::IGraphicsDevice* g) { mGraphics = g; }

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
	 * Returns the root widget of the environment.
	 *
	 * @return Widget* the root widget
	 */
	Widget* GetRoot()
	{
		return mRoot;
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
