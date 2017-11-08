#pragma once

#include "Math/ModelerMath.h"
#include "Types.h"

namespace Core
{

class Camera
{
public:
	enum Projection {ORTHOGRAPHIC = 1, PERSPECTIVE = 2};

	Camera(int32 width, int32 height)
	{
		mWidth = width;
		mHeight = height;
		mYaw = mPitch = 0;
	}

	Camera(int32 width, int32 height, Math::Vector3f position, Math::Quaternionf rotation)
	{
		mWidth = width;
		mHeight = height;

		mPosition = position;
		mRotation = rotation;

		mYaw = mPitch = 0;
	}

	void SetSize(int32 width, int32 height)
	{
		mWidth = width;
		mHeight = height;
	}

	void Rotate(Math::Quaternionf q)
	{
		mIsViewDirty = true;

		mRotation = Normalize(q * mRotation);
	}

	void SetRotation(Math::Quaternionf q)
	{
		mIsViewDirty = true;

		mRotation = Normalize(q);
	}

	void SetRotation(float32 yaw, float32 pitch)
	{
		mIsViewDirty = true;

		mRotation = Math::Quaternionf::AxisAngle(Math::Vector3f::Up, yaw);
		mRotation *= Math::Quaternionf::AxisAngle(Math::Vector3f::Right, pitch);
	}

	void SetRotation()
	{
		mIsViewDirty = true;

		mRotation = Math::Quaternionf::AxisAngle(Math::Vector3f::Up, mYaw);
		mRotation *= Math::Quaternionf::AxisAngle(Math::Vector3f::Right, mPitch);
	}

	void SetPosition(Math::Vector3f v)
	{
		mIsViewDirty = true;

		mPosition = v;
	}

	Math::Matrix4f GetView()
	{
		if(mIsViewDirty)
		{
			Math::Vector3f forward = Math::Rotate(Math::Vector3f::Forward, mRotation);
			mViewMatrix = Math::Matrix4f::ToLookAt(mPosition, mPosition + forward, Math::Vector3f::Up);
		}
		return mViewMatrix;
	}

	//persp
	Math::Matrix4f GetProjection(float32 fov, float32 ar, float32 n, float32 f)
	{
		Math::Matrix4f projection;

		projection = Math::Matrix4f::ToPerspective(fov, ar, n, f);

		return projection;
	}

	//ortho
	Math::Matrix4f GetProjection(float32 n, float32 f, float32 r, float32 l, float32 t, float32 b)
	{
		Math::Matrix4f projection;
		// TODO
		projection = Math::Matrix4f::ToOrthographic(n, f, r, l, t, b);

		return projection;
	}

	Math::Quaternionf GetRotation() { return mRotation; }
	Math::Vector3f GetPosition() { return mPosition; }
	int32 GetWidth() { return mWidth; }
	int32 GetHeight() { return mHeight; }
	Projection GetProjectionType() { return mProjection; }

	void UpdateYaw(float32 yaw)
	{
		mYaw += yaw;
	}

	void UpdatePitch(float32 pitch)
	{
		mPitch += pitch;
	}

private:
	int32 mWidth, mHeight;
	Math::Vector3f mPosition;
	Math::Quaternionf mRotation;
	Math::Matrix4f mViewMatrix;
	float32 mYaw, mPitch;
	bool mIsViewDirty = true;
	Projection mProjection = PERSPECTIVE;

};

}
