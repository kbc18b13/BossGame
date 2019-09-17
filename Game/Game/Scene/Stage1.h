#include "Ground/Ground1.h"
class Troll;
class Player;
class Stage1 : public IGameObject {
public:
	Stage1();
	~Stage1();
	void Update();

private:
	Ground g;
	Player* p = nullptr;
	Troll* t = nullptr;
};