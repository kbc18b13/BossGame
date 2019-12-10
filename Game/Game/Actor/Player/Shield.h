#pragma once
class Player;

class Shield{
public:
	Shield();
	~Shield();

	void Init( Bone* handBone, Player* p );

	void Update();

private:
	SkinModelRender m_model;
	Bone* m_hand;
};

