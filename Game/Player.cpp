#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//アニメーションクリップ読み込み
	m_animClip[enAnimWalk].Load(L"Assets/animData/zikken4.tka", true);
	//m_animClip[enAnimRun].Load(L"Assets/animData/run.tka", true);

	//cmoファイルの読み込み。
	m_model.reset(GOManager().NewGO<SkinModelRender>(0));
	m_model->Init(L"Assets/modelData/zikken4.cmo",m_animClip,1);
}


Player::~Player()
{
}

void Player::Update()
{
	/*if (g_pad->IsTrigger(enButtonA)) {
		m_model->Play(enAnimWalk, 0.2f);
	}*/
	if (g_pad->IsPress(enButtonB)) {
		/*for (Bone* b : m_model->GetModel().GetSkeleton().GetBones()) {
			CMatrix mat = b->GetWorldMatrix();
			CMatrix rot;
			rot.MakeTranslation({ 0,0.1f,0 });
			mat.Mul(mat, rot);
			b->SetWorldMatrix(mat);
		}*/
		Bone* b = m_model->GetModel().GetSkeleton().GetBone(1);
		CMatrix mat = b->GetLocalMatrix();
		CMatrix rot;
		rot.MakeRotationZ(0.07f);
		mat.Mul(mat, rot);
		b->SetLocalMatrix(mat);
	}
}