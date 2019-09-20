#include "stdafx.h"
#include "Player.h"
#include "graphics/SkinModelRender.h"

Player::Player()
{
	//アニメーションクリップ読み込み
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestChara_Run.tka", true);
	//m_animClip[enAnimRun].Load(L"Assets/animData/run.tka", true);

	//cmoファイルの読み込み。
	m_model.reset(NewGO<SkinModelRender>(0));
	m_model->Init(L"Assets/modelData/TestChara.cmo",m_animClip,1);
	m_charaCon.Init(8, 24, {0,50,0});//キャラコンの初期化

	m_camera.SetVec({ 0, 100, -100 });
}


Player::~Player()
{
}

void Player::Update()
{
	/////////移動とジャンプ///////////////
	m_moveSpeed.y -= 30.0f * GameTime::GetDeltaTime();

	if (g_pad->IsTrigger(enButtonA)) {
		m_moveSpeed.y = JUMP_SPEED;
	}

	float speed = m_charaCon.IsOnGround() ? WALK_SPEED : WALK_SPEED_AIR;

	m_moveSpeed.v += g_pad->GetLStickXF() * speed * GameTime::GetDeltaTime() * m_camera.GetRightVec();
	m_moveSpeed.v += g_pad->GetLStickYF() * speed * GameTime::GetDeltaTime() * m_camera.GetFrontVec_XZ();

	CVector3 pos = m_charaCon.Execute(1, m_moveSpeed.v);
	m_model->SetPos(pos);

	if (m_moveSpeed.x*m_moveSpeed.x + m_moveSpeed.z*m_moveSpeed.z > 1) {
		float angle = atan2f(m_moveSpeed.x, m_moveSpeed.z);
		rot.SetRotation(CVector3::AxisY(), angle);
	}

	m_model->SetRot(rot);
	m_camera.Update(GetPos()+CVector3::Up()*50);
	m_moveSpeed.Update(m_charaCon.IsOnGround() ? 3 : 0);
}