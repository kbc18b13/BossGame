class DirectionLight {
public:
	DirectionLight(UINT bufferNum);
	~DirectionLight();

private:
	ID3D11Buffer* m_lightConst;
};