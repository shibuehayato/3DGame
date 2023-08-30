#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"

class RailCamera {
public:
	void Initialize(const Vector3& pos, const Vector3& rotation);

	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }
	
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
};
