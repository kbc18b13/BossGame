#include "stdafx.h"
#include "Player.h"
#include "graphics/SkinModelRender.h"
#include "Sword.h"
#include "physics/CollisionAttr.h"

Player::Player() : Actor(10)
{
	//�A�j���[�V�����N���b�v�ǂݍ���
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestChara_Run.tka", true);
	m_animClip[enAnimIdle].Load(L"Assets/animData/TestChara_Idle.tka",true);
	m_animClip[enAnimSlash].Load(L"Assets/animData/TestChara_Slash.tka");
	m_animClip[enAnimSlash2].Load(L"Assets/animData/TestChara_Slash2.tka");
	m_animClip[enAnimSlash3].Load(L"Assets/animData/TestChara_Slash3.tka");
	m_animClip[enAnimSlash4].Load(L"Assets/animData/TestChara_Slash4.tka");

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model = NewGO<SkinModelRender>(1);
	m_model->Init(L"Assets/modelData/TestChara.cmo",m_animClip,enAnimNum);
	m_model->GetAnim().AddEventFunc("End", [&]() {
		SlashEnd();
	});

	m_charaCon.Init(8, 24, {0,50,0},enCollisionAttr_Player, this);//�L�����R���̏�����

	m_camera.SetVec({ 0, 80, -80 });

	m_sword = NewGO<Sword>(2, m_model->GetModel().GetSkeleton().GetBone(L"Hand_L"), this);
	m_sword->SetOffset({ 12, 0, 0 });
}


Player::~Player()
{
	DeleteGO(m_sword);
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

	//�A�j���[�V����
	if (g_pad->IsTrigger(enButtonRB1)) {
		if (m_comboCount == -1) {
			m_comboCount++;
			m_model->Play(enAnimSlash, 0.1f);
			m_sword->SlashStart();
		} else {
			m_comboContinue = true;
		}
	}else
	if (m_comboCount == -1) {
		if (m_walkSpeed.LengthSq() > 0.001f) {
			m_model->Play(enAnimWalk, 0.1f);
		} else {
			m_model->Play(enAnimIdle, 0.3f);
		}
	}
}

void Player::SlashEnd() {
	if (m_comboContinue) {//���̃L�[���͂������

		m_comboCount++;//�R���{��i�߂�
		if (m_comboCount >= MAX_COMBO) {
			m_comboCount = -1;//�R���{�I��
			m_model->Play(enAnimIdle, 0.3f);
			m_sword->SlashEnd();
		} else {
			m_model->Play(enAnimSlash + m_comboCount, 0.1f);//�A�j���[�V����
			m_sword->SlashStart();
		}
	} else {
		m_comboCount = -1;//�R���{�I��
		m_model->Play(enAnimIdle, 0.3f);
		m_sword->SlashEnd();
	}
	m_comboContinue = false;
}
