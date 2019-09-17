class Actor : public IGameObject{
public:
	virtual CVector3 SetPos() = 0;
	virtual CVector3 GetPos() = 0;

private:

};