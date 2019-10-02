#include "Actor/Actor.h"
#include "graphics/CFont.h"
#include "Util/CharaConEx.h"
class SkinModelRender;

class Troll: public Actor {
public:
	Troll();
	~Troll();

	void Update() override;
	void Draw() override;

	void SetPos(const CVector3& pos) override;

	CVector3 GetPos() const override {
		return m_CharaCon.GetPosition();
	}

private:
	enum {
		enAnimWalk,
		enAnimNum
	};
	CharaConEx m_CharaCon;
	AnimationClip m_animClip[enAnimNum];//アニメーションクリップ
	SkinModelRender* m_model = nullptr;//モデル

	CFont m_font;
};