#pragma once
class Player;

class Shield{
public:
	Shield();
	~Shield();

	void Init( Bone* handBone, Player* p );

	void Update();

	void SetActive(bool active){
		//m_model.SetActive( active );
	}

private:
	Bone* m_hand;
};

