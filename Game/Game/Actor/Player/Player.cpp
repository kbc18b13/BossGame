#include "stdafx.h"
#include "Player.h"
#include "graphics/SkinModelRender.h"

Player::Player()
{
	//�A�j���[�V�����N���b�v�ǂݍ���
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestChara_Run.tka", true);
	m_animClip[enAnimSlash].Load(L"Assets/animData/TestChara_Slash.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model = NewGO<SkinModelRender>(0);
	m_model->Init(L"Assets/modelData/TestChara.cmo",m_animClip,enAnimNum);

	m_swordModel.Init(L"Assets/modelData/Sword.cmo",enFbxUpAxisY);
	m_charaCon.Init(8, 24, {0,50,0});//�L�����R���̏�����

	m_camera.SetVec({ 0, 80, -80 });
}


Player::~Player()
{
	DeleteGO(m_model);
}

void Player::Update()
{
	//���s����
	{
		const float accel = m_charaCon.IsOnGround() ? WALK_ACCEL : WALK_ACCEL_AIR;
		CVector3 pad = g_pad->GetLStickXF()*m_camera.GetRightVec() + g_pad->GetLStickYF()*m_camera.GetFrontVec_XZ();
		
		//�ő呬�x�B�O���ɂ����WALK_MAX�𒴉߂��Ă���ꍇ�A�����W���Ȃ��B
		const float maxSpeed = max(WALK_MAX, m_walkSpeed.Length());

		//��������
		m_walkSpeed += pad * (accel+WALK_BLAKE);

		float len = m_walkSpeed.Length();//���s�x�N�g���̒���

		if (len > 0.1f) {//��~���Ă��Ȃ��ꍇ

			//��������
			CVector3 norm = m_walkSpeed / len;
			CVector3 beforeSpeed = m_walkSpeed;
			m_walkSpeed -= norm * WALK_BLAKE;
			if (m_walkSpeed.Dot(beforeSpeed) < 0){//�����̌��ʋt�����ɍs�������~����B
				m_walkSpeed = CVector3(0,0,0);
			}


			if (len > maxSpeed) {//����ȏ�̃X�s�[�h���o�Ă���Ȃ�}����B
				m_walkSpeed /= len;
				m_walkSpeed *= maxSpeed;
			}
		}
	}

	//�W�����v�����B(�d�͂�)
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

	//���f���ʒu
	m_model->SetPos(pos);
	//���f����]
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