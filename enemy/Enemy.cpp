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
	worldTransform_.UpdateMatrix();

	// 敵の移動ベクトル
	Vector3 move = {0, 0, 0};

	// 敵の移動の速さ
	const float kCharacterSpeed = -0.2f;

	move.z += kCharacterSpeed;

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
}

void Enemy::Draw(ViewProjection& viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}