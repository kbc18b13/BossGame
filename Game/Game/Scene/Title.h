class SpriteRender;

class Title : public IGameObject{
public:
	Title();
	~Title();

	//更新関数
	void Update();

	//描画関数
	void Draw();

private:
	SpriteRender* backImage = nullptr;
};