class SpriteRender;

class Title : public IGameObject{
public:
	Title();
	~Title();

	//�X�V�֐�
	void Update();

private:
	SpriteRender* backImage = nullptr;
};