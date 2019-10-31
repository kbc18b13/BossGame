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
	/// Act�J�n���ɌĂ�
	/// </summary>
	virtual void Start() = 0;

	/// <summary>
	/// ���t���[���Ă�
	/// </summary>
	/// <param name="chara">�L�����R��</param>
	/// <param name="model">���f��</param>
	/// <returns>Act�𑱍s����ꍇ��true</returns>
	virtual void Continue(ActArg& arg) = 0;
};