#pragma once

class AmbientLight {
public:

	void Init(UINT bufferNum);

	void SetColor(const CVector4& c) {
		m_color = c;
	}

	void Apply();

private:
	ID3D11Buffer* m_CBuf;
	UINT m_bufferNum;
	CVector4 m_color;
};