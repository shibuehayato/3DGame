#include "Player.h"
#include "Matrix.h"
#include "ImGuiManager.h"

void Player::Initialize(Model* model, uint32_t textureHandle)
{ 
	model_ = model; 
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
};

void Player::Update()
{
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動の速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更 (左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	// 押した方向で移動ベクトルを変更 (上下)
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 移動限界座標
	const float kMoveLimitX = 30;
	const float kMoveLimitY = 18;
	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// 座標移動 (ベクトルの加算)
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

		// キャラクターの座標を画面表示する処理
	float moves[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	// キャラクターの座標を画面表示する処理
	ImGui::Begin("Player");
	ImGui::InputFloat3("InputFloat3", moves);
	ImGui::SliderFloat3("SliderFloat3", moves, -20.0f, 20.0f);
	ImGui::Text("DebugCamera ENTER");
	ImGui::End();

	worldTransform_.translation_.x = moves[0];
	worldTransform_.translation_.y = moves[1];
	worldTransform_.translation_.z = moves[2];

};

void Player::Draw(ViewProjection& viewProjection)
{
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
};