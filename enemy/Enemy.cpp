#include "Enemy.h"
#include "Matrix.h"
#include <cassert>
#include "Player.h"
#include "GameScene.h"

void Enemy::Initialize(Model* model, Vector3& position)
{ 
	assert(model);
	
	model_ = model; 
	textureHandle_ = TextureManager::Load("uvChecker.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	// 接近フェーズ初期化
	ApproachInitialize();
}

void Enemy::Update()
{ 
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = -0.2f;

	switch (phase_) {
	case Phase::Approach:
	default:
		// 発射タイマーカウントダウン
		--fireTimer;
		// 指定時間に達した
		if (fireTimer < 0) {
			// 弾を発射
			Fire();	
			// 発射タイマーを初期化
			fireTimer = kFireInterval;
		}

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

void Enemy::Draw(ViewProjection viewProjection)
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Fire()
{
	assert(player_);

	// 弾の速度
	const float kBulletSpeed = -1.0f;

	player_->GetWorldPosition();
	this->GetWorldPosition();
	Vector3 velocity = Subtract(this->GetWorldPosition(), player_->GetWorldPosition());
	velocity = Normalize(velocity);
	velocity.x *= kBulletSpeed;
	velocity.y *= kBulletSpeed;
	velocity.z *= kBulletSpeed;

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// 弾を登録する
	gameScene_->AddEnemyBullet(newBullet);
}

void Enemy::ApproachInitialize()
{
	// 発射タイマーを初期化
	fireTimer = kFireInterval;
}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得 (ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::OnCollision() {}