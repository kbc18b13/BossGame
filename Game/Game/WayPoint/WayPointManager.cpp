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
	//直で行けるなら調査の必要なし
	if( CanGo( from, to ) ){
		//return to;
	}

	//ウェイポイントのステートを戻す
	for( WayPoint& wp : wayPoints ){
		wp.SetState( WayPoint::None );
	}

	//スタート地点のWP
	WayPoint start;
	start.SetPos( from );
	start.SetScore( Distance(from, to) );
	start.SetState( WayPoint::Close );

	//ゴール地点のWP
	WayPoint goal;
	start.SetPos( to );
	start.SetState( WayPoint::None );

	auto c = []( WayPoint* lh, WayPoint* rh ) -> bool{return lh->GetScore() > rh->GetScore(); };
	std::priority_queue< WayPoint*, std::vector<WayPoint*>, decltype(c)> openQueue(c);

	//スタートから到達可能なWPをOPNE、スコアを決定する。
	for( WayPoint& wp : wayPoints ){
		if( CanGo( from, wp.GetPos()) && Distance( from, wp.GetPos() ) > 20 ){
			wp.SetState( WayPoint::Open );
			wp.SetScore( Distance(from, wp.GetPos() ) + Distance( wp.GetPos(), to ) );

			//最終的にスタートから直通のWPの中から正解を返すので、自分たちの情報を届けていく。
			wp.SetToGO( wp.GetPos() );
			openQueue.push( &wp );
		}
	}

	//オープンキューが空なら到達不能、現在地で待機。
	if( openQueue.size() == 0 ){
		return from;
	}

	//現在探索中のWP
	WayPoint* now;

	while( true ){
		//次に探索するWPをセット
		now = openQueue.top();
		now->SetState( WayPoint::Close );
		openQueue.pop();

		//ゴールへ行けるかを調査
		if( CanGo( now->GetPos(), to ) ){
			return now->GetToGO();
		}

		//オープンキューが空なら到達不能、現在地で待機。
		if( openQueue.size() == 0 ){
			return from;
		}

		//現在地ノードから到達可能なWPをOPNE、スコアを決定する。
		for( Edge& e : now->GetEdges() ){
			WayPoint& next = wayPoints[e.wpNum];

			if( next.GetState() == WayPoint::None ){
				next.SetState( WayPoint::Open );
				//現在地までのスコア + 次ノードまでの距離 + 次ノードからゴールまでの距離　
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
		//位置
		wp.SetPos( p);

		//接続の数
		UINT connectSize = Util::readBinary<UINT>( ifs );
		for( int j = 0; j < connectSize; j++ ){
			//接続先番号とそこまでの距離
			UINT number = Util::readBinary<UINT>( ifs );
			float length = Util::readBinary<float>( ifs );
			wp.AddEdge( Edge( number, length ) );
		}
	}
}
