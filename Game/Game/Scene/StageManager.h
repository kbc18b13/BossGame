#pragma once

class Player;

class StageGate;

class Stage1;
class Stage2;

class StageManager : public IGameObject{
public:
	StageManager();
	
	void Destroy() override;

	void Update() override;

	Player* GetPlayer(){
		return m_player;
	}

	void SetPlayer(Player* p){
		m_player = p;
	}

	void EndStage(){
		isEndStage = true;
	}

private:
	bool isEndStage = false;;
	float m_endTime = 6.0f;

	Stage1* stage1;
	Stage2* stage2;

	Player* m_player;
	StageGate* m_gate;
};

