#include "Actor/Actor.h"
#include "graphics/CFont.h"
#include "Util/CharaConEx.h"
class SkinModelRender;
class Stage1;
class Act;

class Troll: public Actor {
public:
	Troll(Stage1* stage);
	~Troll();

	void Start() override;
	void Update() override;
	void Draw() override;

	void SetPos(const CVector3& pos) override;

	CVector3 GetPos() const override {
		return m_CharaCon.GetPosition();
	}

private:
	Stage1* stage;

#include "TrollAnimEnum.h"

	enum ActState {
		enActWait,
		enActChase,
		enActAttack,
		enActStep,
		enActNum,
	};
	Act* m_activeAction;
	std::unique_ptr<Act> m_actionArray[enActNum];

	int m_state;

	float m_timer = 0.0f;

	CharaConEx m_CharaCon;
	AnimationClip m_animClip[enAnimNum];//アニメーションクリップ
	SkinModelRender* m_model = nullptr;//モデル

	CFont m_font;
};