class Player;

class Stage1 : public IGameObject {
public:
	Stage1();
	~Stage1();
	void Update();

private:
	Player* p = nullptr;
};