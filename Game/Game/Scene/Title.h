class SpriteRender;

class Title : public IGameObject{
public:
	Title();
	~Title();

	//�X�V�֐�
	void Update();

	//�`��֐�
	void Draw();

private:
	SpriteRender* backImage = nullptr;
};