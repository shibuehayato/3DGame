#pragma once
#include "WorldTransform.h"
#include "Model.h"

// 行動フェーズ
enum class Phase {
	Approach, // 接近する
	Leave     // 離脱する
};

class Enemy {
public:
	void Initialize(Model* model, Vector3& position);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	// フェーズ
	Phase phase_ = Phase::Approach;
};
