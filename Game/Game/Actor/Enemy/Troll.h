
class SkinModelRender;

class Troll: public IGameObject {
public:
	Troll();
	~Troll();

	void Update();

	void SetPos(const CVector3& pos);

private:
	enum {
		enAnimWalk,
		enAnimNum
	};
	AnimationClip m_animClip[enAnimNum];//�A�j���[�V�����N���b�v
	SkinModelRender* m_model = nullptr;//���f��
};