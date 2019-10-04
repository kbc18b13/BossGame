#pragma once
class CharaConEx;
class SkinModelRender;
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
	virtual bool Continue(CharaConEx& chara, SkinModelRender* model) = 0;

protected:
#include "..\TrollAnimEnum.h"
};