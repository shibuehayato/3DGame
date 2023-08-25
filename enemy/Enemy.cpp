#include "Enemy.h"
#include "Matrix.h"
#include <cassert>

void Enemy::Initialize(Model* model, Vector3& position)
{ 
	assert(model);
	
	model_ = model; 
	textureHandle_ = TextureManager::Load("uvChecker.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void Enemy::Update()
{ 
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = -0.2f;

	switch (phase_) {
	case Phase::Approach:
	default:
		// 移動 (ベクトルを加算)
		move.z += kCharacterSpeed;
		// 規定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		move.x += kCharacterSpeed;
		move.y -= kCharacterSpeed;
		break;
	}
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}