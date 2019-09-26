#include "stdafx.h"
#include "Player.h"
#include "graphics/SkinModelRender.h"

Player::Player()
{
	//アニメーションクリップ読み込み
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestChara_Run.tka", true);
	m_animClip[enAnimSlash].Load(L"Assets/animData/TestChara_Slash.tka");

	//cmoファイルの読み込み。
	m_model = NewGO<SkinModelRender>(0);
	m_model->Init(L"Assets/modelData/TestChara.cmo",m_animClip,enAnimNum);

	m_swordModel.Init(L"Assets/modelData/Sword.cmo",enFbxUpAxisY);
	m_charaCon.Init(8, 24, {0,50,0});//キャラコンの初期化

	m_camera.SetVec({ 0, 80, -80 });
}


Player::~Player()
{
	DeleteGO(m_model);
}

void Player::Update()
{
	//歩行処理
	{
		const float accel = m_charaCon.IsOnGround() ? WALK_ACCEL : WALK_ACCEL_AIR;
		CVector3 pad = g_pad->GetLStickXF()*m_camera.GetRightVec() + g_pad->GetLStickYF()*m_camera.GetFrontVec_XZ();
		
		//最大速度。外因によってWALK_MAXを超過している場合、それを妨げない。
		const float maxSpeed = max(WALK_MAX, m_walkSpeed.Length());

		//加速処理
		m_walkSpeed += pad * (accel+WALK_BLAKE);

		float len = m_walkSpeed.Length();//歩行ベクトルの長さ

		if (len > 0.1f) {//停止していない場合

			//減速処理
			CVector3 norm = m_walkSpeed / len;
			CVector3 beforeSpeed = m_walkSpeed;
			m_walkSpeed -= norm * WALK_BLAKE;
			if (m_walkSpeed.Dot(beforeSpeed) < 0){//減速の結果逆方向に行ったら停止する。
				m_walkSpeed = CVector3(0,0,0);
			}


			if (len > maxSpeed) {//上限以上のスピードが出ているなら抑える。
				m_walkSpeed /= len;
				m_walkSpeed *= maxSpeed;
			}
		}
	}

	//ジャンプ処理。(重力も)
	{
		jumpSpeed -= 30.0f;
		if (g_pad->IsTrigger(enButtonA)) {
			jumpSpeed += JUMP_POWER;
		}
	}
	if (g_pad->IsTrigger(enButtonRB1)) {
		m_model->Play(enAnimSlash, 0.1f);
	}
	if (!m_model->IsPlaying()) {
		m_model->Play(enAnimWalk, 0.3f);
	}
	m_walkSpeed.y = jumpSpeed;

	CVector3 pos = m_charaCon.Execute(GameTime::GetDeltaTime(), m_walkSpeed);

	jumpSpeed = m_walkSpeed.y;
	m_walkSpeed.y = 0;

	//モデル位置
	m_model->SetPos(pos);
	//モデル回転
	if (m_walkSpeed.x*m_walkSpeed.x + m_walkSpeed.z*m_walkSpeed.z > 1) {
		float angle = atan2f(m_walkSpeed.x, m_walkSpeed.z);
		rot.SetRotation(CVector3::AxisY(), angle);
	}

	m_model->SetRot(rot);
	m_camera.Update(GetPos()+CVector3::Up()*25);
	m_swordModel.UpdateWorldMatrix(m_model->GetModel().GetSkeleton().GetBone(L"Hand_L")->GetWorldMatrix());
	m_swordModel.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	//m_moveSpeed.Update(m_charaCon.IsOnGround() ? 3 : 0);
}