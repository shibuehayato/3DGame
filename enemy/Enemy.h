#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "EnemyBullet.h"
#include <list>

// 行動フェーズ
enum class Phase {
	Approach, // 接近する
	Leave     // 離脱する
};

class Enemy {
public:
	~Enemy();

	void Initialize(Model* model, Vector3& position);

	void Update();

	void Draw(ViewProjection& viewProjection);

	// 弾発射
	void Fire();

	// 発射間隔
	static const int kFireInterval = 60;

	// 接近フェーズ初期化
	void ApproachInitialize();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	// フェーズ
	Phase phase_ = Phase::Approach;
	// 弾
	std::list<EnemyBullet*> bullets_;
	// 発射タイマー
	int32_t fireTimer = 0;
};
