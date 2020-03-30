#pragma once
struct Edge{
	Edge( UINT wpNum, float length ) : wpNum( wpNum ), length( length ){}
	UINT wpNum;
	float length = 0;
};

class WayPoint{
public:
	enum WPState{
		None,
		Open,
		Close,
	};

	//位置関連
	void SetPos( const CVector3& pos ){
		m_pos = pos;
	}
	CVector3 GetPos() const{
		return m_pos;
	}

	//状態関連
	void SetState( WPState state ){
		m_state = state;
	}
	WPState GetState() const{
		return m_state;
	}

	//スコア関連
	void SetEstimationCost( const CVector3& goal ){
		m_estimationCost = ( m_pos - goal ).Length();
	}
	void SetRealCost( float score ){
		m_realCost = score;
	}
	float GetRealCost(){
		return m_realCost;
	}
	float GetCost() const{
		return m_realCost + m_estimationCost;
	}

	void SetToGO(const CVector3& toGO ){
		m_toGO = toGO;
	}

	CVector3 GetToGO() const{
		return m_toGO;
	}

	void AddEdge( const Edge& edge ){
		edges.push_back( edge );
	}

	std::vector<Edge>& GetEdges(){
		return edges;
	}

private:
	//スタートから次に行くべき方向
	CVector3 m_toGO;
	//現在地までの実コスト
	float m_realCost = 0;
	//ここからゴールまでの予測コスト
	float m_estimationCost = 0;
	WPState m_state = None;
	CVector3 m_pos;
	std::vector<Edge> edges;
};

class WayPointManager{
public:
	void AddWayPoint( const WayPoint& wp ){
		wayPoints.push_back( wp );
	}

	void Load( const wchar_t* file );

	CVector3 GetShouldGo( const CVector3& from, const CVector3& to );

private:
	std::vector<WayPoint> wayPoints;
};