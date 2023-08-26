#pragma once
#define _USE_MATH_DEFIENS
#include "Matrix4x4.h"
#include <assert.h>
#include <cmath>

#include "Matrix4x4.h"
#include "Vector3.h"

Vector3 Add(Vector3 v1, Vector3 v2);

Vector3 Subtract(Vector3 v1, Vector3 v2);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);

Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeRotateMatrix(const Vector3& radian);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);

Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

Vector3 Normalize(const Vector3 v1);
