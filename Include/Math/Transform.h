#pragma once

#include "Math/ModelerMath.h"

namespace Core
{

namespace Math
{

/**
 * Transform class to track positions, rotations, and scales
 *
 * @tparam the datatype for the transform
 */
template <typename Type>
class Transform
{
private:
	Vector3<Type> mPosition;
	Quaternion<Type> mRotation;
	Vector3<Type> mScale;
	Transform* mParentTransform;

public:
	Transform(Transform* ParentTransform = nullptr) : mPosition(0), mRotation(0,0,0,1), mScale(1), mParentTransform(ParentTransform) {}
	Transform(Vector3<Type> Position, Quaternion<Type> Rotation, Vector3<Type> Scale, Transform* ParentTransform = nullptr) :
		mPosition(Position),
		mRotation(Normalize(Rotation)),
		mScale(Scale),
		mParentTransform(ParentTransform) {}
	Transform(const Transform<Type>& t)
	{
		mPosition = t.GetPosition();
		mRotation = t.GetRotation();
		mScale = t.GetScale();
		mParentTransform = t.GetParentTransform();
	}

	Transform* GetParentTransform() const { return mParentTransform; }
	Vector3<Type> GetPosition() const { return mPosition; }
	Quaternion<Type> GetRotation() const { return mRotation; }
	Vector3<Type> GetScale() const { return mScale; }

	/**
	 * Translate the position by the passed in Vector3
	 *
	 * @param v Vector3<Type> to translate by
	 * @return a reference to this transform
	 */
	Transform& Translate(Vector3<Type> v) { mPosition += v; return *this; }
	/**
	 * Rotate by the passed in quaternion
	 *
	 * @param q Quaternion<Type> to rotate by
	 * @return a reference to this transform
	 */
	Transform& Rotate(Quaternion<Type> q) { mRotation = Normalize(mRotation * Normlize(q)); return *this; }
	/**
	 * Scale by the passed in Vector3
	 *
	 * @param v Vector3<Type> to scale by
	 * @return a reference to this transform
	 */
	Transform& Scale(Vector3<Type> s) { mScale *= s; return *this; }

	void SetParentTransform(Transform* t) { mParentTransform = t; }
	void SetPosition(Vector3<Type> v) { mPosition = v; }
	void SetRotation(Quaternion<Type> q) { mRotation = Normlize(q); }
	void SetScale(Vector3<Type> s) { mScale = s; }

	/**
	 * Get the local matrix for this transform, Translation * Rotation * Scale
	 * That is, scaled then rotated then translated
	 *
	 * @return A Matrix4<Type> local matrix
	 */
	Matrix4<Type> GetLocalMatrix() { return ToTranslationMatrix(mPosition) * Quaternion<Type>::ToRotationMatrix(mRotation) * ToScaleMatrix(mScale); }
	/**
	 * Get the world matrix for this transform, which is either
	 * the local matrix if no parent or local multiplied by
	 * the parent's world
	 *
	 * @return A Matrix4<Type> world matrix, which could be the local matrix
	 */
	Matrix4<Type> GetWorldMatrix()
	{
		if(mParentTransform == nullptr)
		{
			return GetLocalMatrix();
		}
		else
		{
			return GetLocalMatrix() * mParentTransform->GetWorldMatrix();
		}
	}
};

typedef Transform<float32> Transformf;
typedef Transform<float64> Transformd;

}

}
