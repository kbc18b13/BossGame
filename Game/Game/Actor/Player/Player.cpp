#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//アニメーションクリップ読み込み
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestChara_Run.tka", true);
	//m_animClip[enAnimRun].Load(L"Assets/animData/run.tka", true);

	//cmoファイルの読み込み。
	m_model.reset(GOManager().NewGO<SkinModelRender>(0));
	m_model->Init(L"Assets/modelData/TestChara.cmo",m_animClip,1);
	m_charaCon.Init(10, 20, {0,50,0});//キャラコンの初期化
}


Player::~Player()
{
}

void Player::Update()
{
	m_moveSpeed.y = g_pad->GetRStickYF();
	m_moveSpeed.x = g_pad->GetLStickXF();
	m_moveSpeed.z = g_pad->GetLStickYF();

	CVector3 pos = m_charaCon.Execute(1, m_moveSpeed);
	m_model->SetPos(pos);
}