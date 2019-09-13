#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//�A�j���[�V�����N���b�v�ǂݍ���
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestChara_Run.tka", true);
	//m_animClip[enAnimRun].Load(L"Assets/animData/run.tka", true);

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.reset(GOManager().NewGO<SkinModelRender>(0));
	m_model->Init(L"Assets/modelData/TestChara.cmo",m_animClip,1);
	m_charaCon.Init(8, 24, {0,50,0});//�L�����R���̏�����
}


Player::~Player()
{
}

void Player::Update()
{
	m_moveSpeed.y -= 30.0f * GameTime::GetDeltaTime();

	m_moveSpeed.x = g_pad->GetLStickXF() * 100 * GameTime::GetDeltaTime();
	m_moveSpeed.z = g_pad->GetLStickYF()* 100 * GameTime::GetDeltaTime();

	if (g_pad->IsTrigger(enButtonA)) {
		m_moveSpeed.y = 10;
	}

	CVector3 pos = m_charaCon.Execute(1, m_moveSpeed);
	m_model->SetPos(pos);
}