#pragma once
#include "..\Troll.h"
#include "Scene/IStage.h"
class Act;
class Player;

namespace TrollAct{

class Act{
public:
	virtual ~Act(){}

	/// <summary>
	/// Act開始時に呼ぶ
	/// </summary>
	virtual void Start( Troll* t ) = 0;

	/// <summary>
	/// 毎フレーム呼ぶ
	/// </summary>
	/// <param name="chara">キャラコン</param>
	/// <param name="model">モデル</param>
	/// <returns>Actを続行する場合はtrue</returns>
	virtual void Continue( Troll* t ) = 0;

protected:
	void ChangeActDefault( Troll* t ){
		t->ChangeActDefault();
	}
	void ChangeAct( Troll* t, Troll::ActState act ){
		t->ChangeAct( act );
	}
	CharaConEx& chara( Troll* t ){
		return t->m_CharaCon;
	}
	SkinModelRender& model( Troll* t ){
		return t->m_model;
	}
	Player* player( Troll* t ){
		return t->stage->GetPlayer();
	}

};

}