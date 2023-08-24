#include "WorldTransform.h"
#include "Matrix.h"

void WorldTransform::UpdateMatrix()
{
	// スケール、回転、平行行列を合成して行列を計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	// 定数バッファに転送する
	TransferMatrix();
}