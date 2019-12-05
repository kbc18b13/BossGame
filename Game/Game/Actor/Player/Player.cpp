#include "stdafx.h"
#include "Player.h"
#include "physics/CollisionAttr.h"
#include "graphics/RenderObjectManager.h"

Player::Player() : Actor(10)
{
	//アニメーションクリップ読み込み
	m_animClip[enAnimWalk].Load(L"Assets/animData/TestChara_Run.tka", true);
	m_animClip[enAnimIdle].Load(L"Assets/animData/TestChara_Idle.tka",true);
	m_animClip[enAnimSlash].Load(L"Assets/animData/TestChara_Slash.tka");
	m_animClip[enAnimSlash2].Load(L"Assets/animData/TestChara_Slash2.tka");
	m_animClip[enAnimSlash3].Load(L"Assets/animData/TestChara_Slash3.tka");
	m_animClip[enAnimSlash4].Load(L"Assets/animData/TestChara_Slash4.tka");

	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/TestChara.cmo",m_animClip,enAnimNum);
	m_model.GetAnim().AddEventFunc("End", [&]() {
		SlashEnd();
	});
	m_model.GetModel().setEmissionColor( CVector3( 20, 0, 0 ) );

	CharaConDesc desc;
	{
		desc.radius = 8;
		desc.height = 24;

		desc.position = CVector3(0, 50, 0);

		desc.walkAccel    = 100;
		desc.walkAccelAir = 10;
		desc.walkBrake    = 10;
		desc.walkMax      = 150;

		desc.gravity      = 900;
		desc.jumpPower    = 500;

		desc.userIndex   = enCollisionAttr_Player;
		desc.userPointer = this;
	}
	m_charaCon.Init(desc);//キャラコンの初期化

	m_camera.SetVec({ 0, 80, -80 });

    m_sword.Init(m_model.GetModel().GetSkeleton().GetBone(L"Hand_L"), this);
	m_sword.SetOffset({ 12, 0, 0 });

	//HPバーの初期化
	m_hpBar.Init( L"Assets/sprite/HpOut.dds", L"Assets/sprite/HpIn.dds", 1000, 25 );
	m_hpBar.SetPosCenterZero( CVector2( 625, 325 ) );
}


Player::~Player()
{
}

void Player::Update()
{
    //シャドウマップの移動
    {
        g_ROManager.GetShadowMap().UpdateLight(GetPos() + CVector3(400, 400, 400), CVector3(-1, -1, -1));
    }

    if (g_pad->IsPress(enButtonLB1)) {
        m_charaCon.AddVelocity(CVector3::Up()*50);
    }

	//キャラコンの操作
	CVector3 move = g_pad->GetLStickXF() * m_camera.GetRightVec() + g_pad->GetLStickYF() * m_camera.GetFrontVec_XZ();
	CVector3 pos = m_charaCon.Excecute(move, g_pad->IsTrigger(enButtonA));
	CVector3 speed = m_charaCon.GetVelocity();

	//モデル位置
	m_model.SetPos(pos);
	//モデル回転
	if (speed.x*speed.x + speed.z*speed.z > 1) {
		float angle = atan2f(speed.x, speed.z);
		rot.SetRotation(CVector3::AxisY(), angle);
	}

	m_model.SetRot(rot);
	m_camera.Update(GetPos()+CVector3::Up()*25);

	//アニメーション
	if (g_pad->IsTrigger(enButtonRB1)) {
		if (m_comboCount == -1) {
			m_comboCount++;
			m_model.Play(enAnimSlash, 0.1f);
			m_sword.SlashStart();
		} else {
			m_comboContinue = true;
		}
	}else
	if (m_comboCount == -1) {
		if (speed.LengthSq() > 0.001f) {
			m_model.Play(enAnimWalk, 0.1f);
		} else {
			m_model.Play(enAnimIdle, 0.3f);
		}
	}

	//HPバーの更新
	m_hpBar.SetPercent( Actor::GetHPPer() );

    Actor::Update();
    m_model.Update();
    m_sword.Update();
}

void Player::SlashEnd() {
	if (m_comboContinue) {//次のキー入力があれば

		m_comboCount++;//コンボを進める
		if (m_comboCount >= MAX_COMBO) {
			m_comboCount = -1;//コンボ終了
			m_model.Play(enAnimIdle, 0.3f);
			m_sword.SlashEnd();
		} else {
			m_model.Play(enAnimSlash + m_comboCount, 0.1f);//アニメーション
			m_sword.SlashStart();
		}
	} else {
		m_comboCount = -1;//コンボ終了
		m_model.Play(enAnimIdle, 0.3f);
		m_sword.SlashEnd();
	}
	m_comboContinue = false;
}
