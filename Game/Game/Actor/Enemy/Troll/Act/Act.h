#pragma once
class CharaConEx;
class SkinModelRender;
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
	virtual bool Continue(CharaConEx& chara, SkinModelRender* model) = 0;

protected:
#include "..\TrollAnimEnum.h"
};