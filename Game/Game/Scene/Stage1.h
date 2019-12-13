#include "Ground/Ground1.h"
#include "IStage.h"
class Troll;
class Player;
class Stage1 : public IStage {
public:
	Stage1();
	~Stage1();
	void Update();

private:
	Ground g;
};