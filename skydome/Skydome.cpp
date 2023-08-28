#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) 
{ 
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {100, 100, 100};
}

void Skydome::Update() 
{
	worldTransform_.UpdateMatrix(); 
}

void Skydome::Draw(ViewProjection viewProjection) 
{  
	// 3Dモデル描画
	model_->Draw(worldTransform_, viewProjection);
}