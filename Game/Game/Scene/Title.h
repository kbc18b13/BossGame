class SpriteRender;

class Title : public IGameObject{
public:
	Title();
	~Title();

	//XVŠÖ”
	void Update();

private:
	SpriteRender* backImage = nullptr;
};