#pragma once
#include "Actor/Actor.h"

class CharaConEx;

class Act{
public:
	Act();
	virtual ~Act();

	void Start( Actor* a){
		m_isEnd = false;
		SubStart(a);
	}
	virtual void Update( Actor* a ) = 0;
	virtual void End( Actor* a ) = 0;

	void SetCharaCon( CharaConEx* chara ){
		m_chara = chara;
	}

	void SetSkinModelRender( SkinModelRender* model ){
		m_model = model;
	}

	bool isActEnd(){
		return m_isEnd;
	}

	int GetNextAct(){
		return m_nextActIndex;
	}

protected:
	virtual void SubStart( Actor* a ) = 0;

	void ActEnd(int nextIndex){
		m_isEnd = true;
		m_nextActIndex = nextIndex;
	}

	CharaConEx* m_chara;
	SkinModelRender* m_model;

private:
	int m_nextActIndex = 0;
	bool m_isEnd = false;
};

