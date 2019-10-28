#pragma once
#include "..\Troll.h"
class Act;
class Player;

struct ActArg {
	CharaConEx* charaCon = nullptr;
	SkinModelRender* model = nullptr;
	Player* player = nullptr;
    std::function<void(float)> changeAct;
};

class Act {
public:
	virtual ~Act() {}

	/// <summary>
	/// Act開始時に呼ぶ
	/// </summary>
	virtual void Start() = 0;

	/// <summary>
	/// 毎フレーム呼ぶ
	/// </summary>
	/// <param name="chara">キャラコン</param>
	/// <param name="model">モデル</param>
	/// <returns>Actを続行する場合はtrue</returns>
	virtual void Continue(ActArg& arg) = 0;
};