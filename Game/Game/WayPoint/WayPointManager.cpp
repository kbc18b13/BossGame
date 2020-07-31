#include "stdafx.h"
#include "WayPointManager.h"
#include <fstream>
#include <queue>

inline float Distance( const CVector3& from, const CVector3& to ){
	return ( from - to ).Length();
}

bool CanGo( CVector3 from, CVector3 to){
	//キャラクターの座標は地面と接しているため、すこし上にあげる。
	constexpr float upCorrect = 20.0f;
	from.y += upCorrect;
	to.y += upCorrect;
	btCollisionWorld::ClosestRayResultCallback cb( from.toBT(), to.toBT() );
	cb.m_collisionFilterGroup = COFlag::CF_Ray;
	cb.m_collisionFilterMask = COFlag::CF_Ground;

	g_physics.GetDynamicWorld()->rayTest( from.toBT(), to.toBT(), cb );

	//障害物にヒットしたら通行不可。ただし法線が上向きなら通す。
	return !cb.hasHit();
}

CVector3 WayPointManager::GetShouldGo( const CVector3& from, const CVector3& to ){
	//直で行けるなら調査の必要なし
	if( CanGo( from, to ) ){
		return to;
	}

	//ウェイポイントのステートを戻す。ついでに予測コストも計算しておく。
	for( WayPoint& wp : wayPoints ){
		wp.SetState( WayPoint::None );
		wp.SetEstimationCost( to );
	}

	//スタート地点のWP
	WayPoint start;
	start.SetPos( from );
	start.SetRealCost( 0 );
	start.SetState( WayPoint::Close );

	//ゴール地点のWP
	WayPoint goal;
	start.SetPos( to );
	start.SetState( WayPoint::None );

	auto c = []( WayPoint* lh, WayPoint* rh ) -> bool{return lh->GetCost() > rh->GetCost(); };
	std::priority_queue< WayPoint*, std::vector<WayPoint*>, decltype( c )> openQueue( c );

	//スタートから到達可能なWPをOPNE、スコアを決定する。
	for( WayPoint& wp : wayPoints ){
		if( CanGo( from, wp.GetPos() ) ){
			wp.SetState( WayPoint::Open );
			wp.SetRealCost( Distance( from, wp.GetPos() ) );

			//最終的にスタートから直通のWPの中から正解を返すので、自分たちの情報を届けていく。
			wp.SetToGO( wp.GetPos() );
			openQueue.push( &wp );
		}
	}

	//オープンキューが空なら到達不能、現在地で待機。
	if( openQueue.size() == 0 ){
		return to;
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
			CanGo( from, now->GetToGO() );
			return now->GetToGO();
		}

		//オープンキューが空なら到達不能、とりあえず目標に向けて進め。
		if( openQueue.size() == 0 ){
			return to;
		}

		//現在地ノードから到達可能なWPをOPNE、スコアを決定する。
		for( Edge& e : now->GetEdges() ){
			WayPoint& next = wayPoints[e.wpNum];

			if( !CanGo( now->GetPos(), next.GetPos()) ){
				CanGo( now->GetPos(), next.GetPos() );
			}

			if( next.GetState() == WayPoint::None ){
				next.SetState( WayPoint::Open );
				//現在地までのスコア + 次ノードまでの距離
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
		//位置
		wp.SetPos( p );

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
