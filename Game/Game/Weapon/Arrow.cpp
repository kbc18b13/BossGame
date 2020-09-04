#include "stdafx.h"
#include "Arrow.h"
#include "Actor/Actor.h"

Arrow::Arrow(){}

Arrow::~Arrow(){}

void Arrow::Init(Actor* a){
	owner = a;
	m_model.Init( { L"Assets/modelData/Arrow.cmo" } );
	m_collider.Create( {1,1,13} );
	m_collision.Init( m_collider, EnCollisionAttr::enCollisionAttr_Player, owner );
}

CVector3 Arrow::CalcShotVec( const CVector3 & start, const CVector3 & target, float speed){
	//������2�_����ˏo�p�x�����߂�B
	const float g = m_gravity;
	const float s = speed;

	CVector3 toT = target - start;
	const float y = toT.y;
	toT.y = 0;
	const float x = toT.Length();

	const float p = ( g * pow2( x ) ) / ( 2 * pow2( s ) );

	const float a = 1;
	const float b = -( x / p );
	const float c = y / p + 1;

	//���̌����̔��ʎ�
	const float inRoot = pow2( b ) - 4 * a * c;

	if( inRoot < 0 ){
		//�𓚂������ꍇ
		return CVector3::Zero();
	} else{
		//�𓚂�����ꍇ
		const float _tan1 = ( -b + sqrt( inRoot ) ) / ( 2 * a );
		const float _tan2 = ( -b - sqrt( inRoot ) ) / ( 2 * a );

		const float _tan = std::min( _tan1, _tan2 );

		const float _cos = sqrt( 1 / ( 1 + pow2( _tan ) ) );
		const float _sin = sqrt( 1 - pow2(_cos) ) * Util::Sign(_tan);

		CVector3 calcV = toT.GetNormalized() * (speed * _cos);
		calcV.y = speed * _sin;
		return calcV;
	}
}

void Arrow::Update(){
	//���Ԃŏ���
	m_timer -= GameTime::GetDeltaTime();
	if( m_timer <= 0 ){
		DeleteGO( this );
	}

	//�h�����Ă���̂œ����Ȃ�
	if( isStop ){
		return;
	}

	CVector3 nextPos = GetPos() + m_vec * GameTime::GetDeltaTime();

	//�ʒu�Ɗp�x�̍X�V
	SetPos(nextPos);
	SetRot( Util::LookRot( m_vec ) );

	auto result = m_collision.ContactTest();

	//�v���C���[�Ƀ_���[�W
	if( !result.actors.empty() ){
		DeleteGO( this );
		for( Actor* a : result.actors ){
			a->Damage( 2, owner );
		}
	}

	//��Q���Ɏh�������B
	if( result.groundHit ){
		isStop = true;
	}

	//�d�͂�K�p
	m_vec.y -= m_gravity * GameTime::GetDeltaTime();

	m_model.Update();
}