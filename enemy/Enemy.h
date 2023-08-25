#pragma once
#include "WorldTransform.h"
#include "Model.h"

class Enemy {
public:
	void Initialize(Model* model, Vector3& position);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
