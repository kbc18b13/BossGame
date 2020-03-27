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

	void SetState( WPState state ){
		m_state = state;
	}

	WPState GetState() const{
		return m_state;
	}

	void SetPos( const CVector3& pos ){
		m_pos = pos;
	}

	CVector3 GetPos() const{
		return m_pos;
	}

	void SetScore( float score ){
		m_score = score;
	}

	float GetScore() const{
		return m_score;
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
	CVector3 m_toGO;
	float m_score;
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