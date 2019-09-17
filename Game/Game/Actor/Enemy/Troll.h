
class SkinModelRender;

class Troll: public IGameObject {
public:
	Troll();
	~Troll();

	void Update();

private:
	SkinModelRender* m_model = nullptr;//ƒ‚ƒfƒ‹
};