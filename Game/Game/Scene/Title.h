class SpriteRender;

class Title : public IGameObject{
public:
	Title();
	~Title();

	//XVŠÖ”
	void Update();

	//•`‰æŠÖ”
	void Draw();

private:
	SpriteRender* backImage = nullptr;
};