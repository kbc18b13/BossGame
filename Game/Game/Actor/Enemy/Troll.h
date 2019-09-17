
class SkinModelRender;

class Troll: public IGameObject {
public:
	Troll();
	~Troll();

	void Update();

private:
	enum {
		enAnimWalk,
		enAnimNum
	};
	AnimationClip m_animClip[enAnimNum];//アニメーションクリップ
	SkinModelRender* m_model = nullptr;//モデル
};