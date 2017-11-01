#pragma once

#include <cstdlib>
#include <vector>
#include <algorithm>

#include "Environment.h"
#include "GuiRenderer.h"
#include "Types.h"

namespace Gui
{

class Widget
{
private:
	int32 mX, mY, mWidth, mHeight;
	Widget* mParent;
	std::vector<Widget*> mChildren;

public:
	virtual ~Widget() {}

	Widget() : mX(0),mY(0),mWidth(0),mHeight(0),mParent(nullptr),mChildren(std::vector<Widget>()) {}
	Widget(int32 x, int32 y, int32 width, int32 height) : mX(x),mY(y),mWidth(width),mHeight(mHeight),mParent(nullptr),mChildren(std::vector<Widget>()) {}
	Widget(int32 x, int32 y, int32 width, int32 height, Widget* parent) : mX(x),mY(y),mWidth(width),mHeight(mHeight),mParent(parent),mChildren(std::vector<Widget>()) {}

	virtual bool OnMouseClick(Environment* e, int32 x, int32 y, int32 button, bool down)
	{
		bool result = false;
		for(uint32 i = 0; i < mChildren.size(); i++)
		{
			if(GetChild(i)->OnMouseClick(e, x+mX,y+mY,button,down))
			{
				result = true;
				break;
			}
		}
		return InBounds(x,y);
	}

	void Draw(Environment* e, Video::GuiRenderer* g)
	{
		OnDraw(e, g);

		g->Translate(mX, mY);
		for (uint32 i = GetChildCount() - 1; i >= 0; i--)
		{
			GetChild(i)->Draw(e, g);
		}
		g->Translate(-mX, -mY);
	}

	void OnDraw(Environment* e, Video::GuiRenderer* g)
	{
		g->SetColor(255,255,255);
		g->FillRect(mX, mY, mWidth - 1, mHeight - 1);
	}

	void Focus() {
		Widget* w = this;

		while (w->GetParent() != nullptr)
		{
			w->GetParent()->AddChild(w, 0);
			w = w->GetParent();
		}
	}

	void AddChild(Widget* w)
	{
		AddChild(w, GetChildCount());
	}

	void AddChild(Widget* w, uint32 index) {
		Widget* parent = w->GetParent();

		if (parent != nullptr)
		{
			parent->RemoveChild(w);
		}

		mChildren.insert(mChildren.begin() + index, w);
		w->SetParent(this);
	}

	void RemoveChild(Widget* w)
	{
		mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), w), mChildren.end());
	}

	void SetParent(Widget* parent)
	{
		mParent = parent;
	}

	void SetSize(int32 w, int32 h)
	{
		mWidth = w;
		mHeight = h;
	}

	void SetPosition(int32 x, int32 y)
	{
		mX = x;
		mY = y;
	}

	void SetBounds(int32 x, int32 y, int32 w, int32 h)
	{
		SetPosition(x, y);
		SetSize(w, h);
	}

	bool InBounds(int32 x, int32 y)
	{
		x = x - GetX();
		y = y - GetY();

		if (x < 0 || x >= GetWidth()) return false;
		if (y < 0 || y >= GetHeight()) return false;

		return true;
	}

	int GetX() { return mX; }
	int GetY() { return mY; }
	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	Widget* GetParent() { return mParent; }
	Widget* GetChild(uint32 i) { return mChildren[i]; }
	int GetChildCount() { return mChildren.size(); }
};


}
