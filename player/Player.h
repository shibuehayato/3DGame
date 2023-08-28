#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "PlayerBullet.h"
#include <list>



class Player {
public:
	~Player();

	void Initialize(Model* model, uint32_t textureHandle, Vector3 position);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Rotate();

	void Attack();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

		// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent">親となるワールドトランスフォームをセット</param>
	void SetParent(const WorldTransform* parent);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;
	// 弾
	std::list<PlayerBullet*> bullets_;
};
