#include "stdafx.h"
#include "WayPointManager.h"
#include <fstream>
#include <queue>

inline float Distance( const CVector3& from, const CVector3& to ){
	return ( from - to ).Length();
}

bool CanGo( CVector3 from, CVector3 to){
	//�L�����N�^�[�̍��W�͒n�ʂƐڂ��Ă��邽�߁A��������ɂ�����B
	constexpr float upCorrect = 20.0f;
	from.y += upCorrect;
	to.y += upCorrect;
	btCollisionWorld::ClosestRayResultCallback cb( from.toBT(), to.toBT() );
	cb.m_collisionFilterGroup = COFlag::CF_Ray;
	cb.m_collisionFilterMask = COFlag::CF_Ground;

	g_physics.GetDynamicWorld()->rayTest( from.toBT(), to.toBT(), cb );

	//��Q���Ƀq�b�g������ʍs�s�B�������@����������Ȃ�ʂ��B
	return !cb.hasHit();
}

CVector3 WayPointManager::GetShouldGo( const CVector3& from, const CVector3& to ){
	//���ōs����Ȃ璲���̕K�v�Ȃ�
	if( CanGo( from, to ) ){
		return to;
	}

	//�E�F�C�|�C���g�̃X�e�[�g��߂��B���łɗ\���R�X�g���v�Z���Ă����B
	for( WayPoint& wp : wayPoints ){
		wp.SetState( WayPoint::None );
		wp.SetEstimationCost( to );
	}

	//�X�^�[�g�n�_��WP
	WayPoint start;
	start.SetPos( from );
	start.SetRealCost( 0 );
	start.SetState( WayPoint::Close );

	//�S�[���n�_��WP
	WayPoint goal;
	start.SetPos( to );
	start.SetState( WayPoint::None );

	auto c = []( WayPoint* lh, WayPoint* rh ) -> bool{return lh->GetCost() > rh->GetCost(); };
	std::priority_queue< WayPoint*, std::vector<WayPoint*>, decltype( c )> openQueue( c );

	//�X�^�[�g���瓞�B�\��WP��OPNE�A�X�R�A�����肷��B
	for( WayPoint& wp : wayPoints ){
		if( CanGo( from, wp.GetPos() ) ){
			wp.SetState( WayPoint::Open );
			wp.SetRealCost( Distance( from, wp.GetPos() ) );

			//�ŏI�I�ɃX�^�[�g���璼�ʂ�WP�̒����琳����Ԃ��̂ŁA���������̏���͂��Ă����B
			wp.SetToGO( wp.GetPos() );
			openQueue.push( &wp );
		}
	}

	//�I�[�v���L���[����Ȃ瓞�B�s�\�A���ݒn�őҋ@�B
	if( openQueue.size() == 0 ){
		return to;
	}

	//���ݒT������WP
	WayPoint* now;

	while( true ){
		//���ɒT������WP���Z�b�g
		now = openQueue.top();
		now->SetState( WayPoint::Close );
		openQueue.pop();

		//�S�[���֍s���邩�𒲍�
		if( CanGo( now->GetPos(), to ) ){
			CanGo( from, now->GetToGO() );
			return now->GetToGO();
		}

		//�I�[�v���L���[����Ȃ瓞�B�s�\�A�Ƃ肠�����ڕW�Ɍ����Đi�߁B
		if( openQueue.size() == 0 ){
			return to;
		}

		//���ݒn�m�[�h���瓞�B�\��WP��OPNE�A�X�R�A�����肷��B
		for( Edge& e : now->GetEdges() ){
			WayPoint& next = wayPoints[e.wpNum];

			if( !CanGo( now->GetPos(), next.GetPos()) ){
				CanGo( now->GetPos(), next.GetPos() );
			}

			if( next.GetState() == WayPoint::None ){
				next.SetState( WayPoint::Open );
				//���ݒn�܂ł̃X�R�A + ���m�[�h�܂ł̋���
				next.SetRealCost( now->GetRealCost() + e.length );
				next.SetToGO( now->GetToGO() );
				openQueue.push( &next );
			}
		}
	}
}

void WayPointManager::Load( const wchar_t * file ){
	std::ifstream ifs( file, std::ios::binary );

	UINT wpSize = Util::readBinary<UINT>( ifs );
	wayPoints.reserve( wpSize );

	for( int i = 0; i < wpSize; i++ ){
		wayPoints.push_back( WayPoint{} );
		WayPoint& wp = wayPoints.back();
		CVector3 p = Util::readBinary<CVector3>( ifs );
		p.y -= 22;
		//�ʒu
		wp.SetPos( p );

		//�ڑ��̐�
		UINT connectSize = Util::readBinary<UINT>( ifs );
		for( int j = 0; j < connectSize; j++ ){
			//�ڑ���ԍ��Ƃ����܂ł̋���
			UINT number = Util::readBinary<UINT>( ifs );
			float length = Util::readBinary<float>( ifs );
			wp.AddEdge( Edge( number, length ) );
		}
	}
}
