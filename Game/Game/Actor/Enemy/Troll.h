#include "character/CharacterController.h"
class SkinModelRender;

class Troll: public IGameObject {
public:
	Troll();
	~Troll();

	void Update() override;

	void SetPos(const CVector3& pos);

private:
	enum {
		enAnimWalk,
		enAnimNum
	};
	CharacterController m_CharaCon;
	AnimationClip m_animClip[enAnimNum];//アニメーションクリップ
	SkinModelRender* m_model = nullptr;//モデル
};