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
}


Player::~Player()
{
}

void Player::Update()
{
}