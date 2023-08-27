﻿#include "EnemyBullet.h"
#include <cassert>
#include "TextureManager.h"
#include "Matrix.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("renga.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

}

void EnemyBullet::Update()
{
	worldTransform_.UpdateMatrix();

	// 座標を移動させる (1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyBullet::OnCollision()
{ isDead_ = true; }

Vector3 EnemyBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得 (ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}