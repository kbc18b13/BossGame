#include "graphics/Shader.h"

class DebugWireframe : public btIDebugDraw {
	ID3D11Buffer* m_cBuf;//�萔�o�b�t�@
	ID3D11Buffer* m_vBuf;//���_�o�b�t�@
	Shader m_pShader;//�s�N�Z���V�F�[�_�[
	Shader m_vShader;//���_�V�F�[�_�[
	ID3D11DepthStencilState* m_depthState;//�[�x�X�e���V���X�e�[�g
	int m_debug = 0;
public:
	DebugWireframe();
	~DebugWireframe();

	//�K�{
	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

	void setDebugMode(int debugMode) override {
		m_debug = debugMode;
	}
	int	getDebugMode() const override {
		return m_debug;
	}

	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)override {};

	void reportErrorWarning(const char* warningString)override {};

	void draw3dText(const btVector3& location, const char* textString)override {};

	void DrawBegin();
};