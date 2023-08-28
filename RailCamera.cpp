#include "RailCamera.h"
#include "Matrix.h"
#include "ImGuiManager.h"

void RailCamera::Initialize(const Vector3& position, const Vector3& rotation) {
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;
	viewProjection_.Initialize();
}

void RailCamera::Update() 
{
	worldTransform_.translation_.z += 0.01f;

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::DragFloat3("CameraTranslation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("CameraRotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
}