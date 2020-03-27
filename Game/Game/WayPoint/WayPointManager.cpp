#include "stdafx.h"
#include "WayPointManager.h"
#include <fstream>
#include <queue>

inline float Distance( const CVector3& from, const CVector3& to ){
	return ( from - to ).Length();
}

bool CanGo( CVector3 from, CVector3 to ){
	from.y += 5;
	to.y += 5;
	if( to.y - from.y > 10 ){
		return false;
	}
	btCollisionWorld::ClosestRayResultCallback cb( from, to );
	cb.m_collisionFilterMask = 0;
	cb.m_collisionFilterMask |= btCollisionObject::CollisionFlags::CF_Ground;

	g_physics.GetDynamicWorld()->rayTest( from, to, cb );
	return !cb.hasHit();
}

CVector3 WayPointManager::GetShouldGo( const CVector3& from, const CVector3& to ){
	//���ōs����Ȃ璲���̕K�v�Ȃ�
	if( CanGo( from, to ) ){
		//return to;
	}

	//�E�F�C�|�C���g�̃X�e�[�g��߂�
	for( WayPoint& wp : wayPoints ){
		wp.SetState( WayPoint::None );
	}

	//�X�^�[�g�n�_��WP
	WayPoint start;
	start.SetPos( from );
	start.SetScore( Distance(from, to) );
	start.SetState( WayPoint::Close );

	//�S�[���n�_��WP
	WayPoint goal;
	start.SetPos( to );
	start.SetState( WayPoint::None );

	auto c = []( WayPoint* lh, WayPoint* rh ) -> bool{return lh->GetScore() > rh->GetScore(); };
	std::priority_queue< WayPoint*, std::vector<WayPoint*>, decltype(c)> openQueue(c);

	//�X�^�[�g���瓞�B�\��WP��OPNE�A�X�R�A�����肷��B
	for( WayPoint& wp : wayPoints ){
		if( CanGo( from, wp.GetPos()) && Distance( from, wp.GetPos() ) > 20 ){
			wp.SetState( WayPoint::Open );
			wp.SetScore( Distance(from, wp.GetPos() ) + Distance( wp.GetPos(), to ) );

			//�ŏI�I�ɃX�^�[�g���璼�ʂ�WP�̒����琳����Ԃ��̂ŁA���������̏���͂��Ă����B
			wp.SetToGO( wp.GetPos() );
			openQueue.push( &wp );
		}
	}

	//�I�[�v���L���[����Ȃ瓞�B�s�\�A���ݒn�őҋ@�B
	if( openQueue.size() == 0 ){
		return from;
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
			return now->GetToGO();
		}

		//�I�[�v���L���[����Ȃ瓞�B�s�\�A���ݒn�őҋ@�B
		if( openQueue.size() == 0 ){
			return from;
		}

		//���ݒn�m�[�h���瓞�B�\��WP��OPNE�A�X�R�A�����肷��B
		for( Edge& e : now->GetEdges() ){
			WayPoint& next = wayPoints[e.wpNum];

			if( next.GetState() == WayPoint::None ){
				next.SetState( WayPoint::Open );
				//���ݒn�܂ł̃X�R�A + ���m�[�h�܂ł̋��� + ���m�[�h����S�[���܂ł̋����@
				next.SetScore( now->GetScore() + e.length + Distance( next.GetPos(), to ) );
				next.SetToGO( now->GetToGO() );
				openQueue.push( &next );
			}
		}
	}
}

void WayPointManager::Load( const wchar_t * file ){
	std::ifstream ifs(file , std::ios::binary );

	UINT wpSize = Util::readBinary<UINT>( ifs );
	wayPoints.reserve( wpSize );

	for( int i = 0; i < wpSize; i++ ){
		wayPoints.push_back( WayPoint{} );
		WayPoint& wp = wayPoints.back();
		CVector3 p = Util::readBinary<CVector3>( ifs );
		p.y -= 22;
		//�ʒu
		wp.SetPos( p);

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
