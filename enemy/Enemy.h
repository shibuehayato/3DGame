#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "EnemyBullet.h"
#include <list>

// GameSceneの前方宣言 
class GameScene;

// 自機クラスの前方宣言
class Player;

// 行動フェーズ
enum class Phase {
	Approach, // 接近する
	Leave     // 離脱する
};

class Enemy {
public:

	void Initialize(Model* model,const Vector3& position);

	void Update();

	void Draw(ViewProjection viewProjection);

	// 弾発射
	void Fire();

	// 発射間隔
	static const int kFireInterval = 60;

	// 接近フェーズ初期化
	void ApproachInitialize();

	void SetPlayer(Player* player) { player_ = player; }

    Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// 弾リストを取得
	//const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	// フェーズ
	Phase phase_ = Phase::Approach;
	// 弾
	//std::list<EnemyBullet*> bullets_;
	// 発射タイマー
	int32_t fireTimer = 0;
	// 自キャラ
	Player* player_ = nullptr;
	// ゲームシーン
	GameScene* gameScene_ = nullptr;
	// デスフラグ
	bool isDead_ = false;
};
