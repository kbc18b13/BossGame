#include "stdafx.h"
#include "CascadePart.h"
#include <numeric>

extern SkinModelRender* g_testSk[4];

void CascadePart::Init( UINT w, UINT h ){
	m_renderTarget.Init( w, h, DXGI_FORMAT_R32_FLOAT );
}

void CascadePart::RenderToShadowMap( ID3D11DeviceContext * dc, std::vector<SkinModelRender*>& casters ){

	//�������8���_���擾(���[���h���W)
	CVector3 verts[8];
	{
		float l_near = GetCameraNear();
		float l_far = GetCameraFar();

		CVector3 nearPos = g_camera3D.GetPosition() + g_camera3D.GetFront() * l_near;
		CVector3 farPos = g_camera3D.GetPosition() + g_camera3D.GetFront() * l_far;

		float viewAngleTan = tanf( g_camera3D.GetViewAngle() / 2 );

		CVector3 nearUp = g_camera3D.GetUp() * ( viewAngleTan * l_near );
		CVector3 farUp = g_camera3D.GetUp() * ( viewAngleTan * l_far );

		CVector3 nearLateral = g_camera3D.GetRight() * ( viewAngleTan * l_near * g_camera3D.GetAspect() );
		CVector3 farLateral = g_camera3D.GetRight() * ( viewAngleTan * l_far * g_camera3D.GetAspect() );

		verts[0] = nearPos + nearUp + nearLateral;
		verts[1] = nearPos + nearUp - nearLateral;
		verts[2] = nearPos - nearUp + nearLateral;
		verts[3] = nearPos - nearUp - nearLateral;
		verts[4] = farPos  + farUp + farLateral;
		verts[5] = farPos  + farUp - farLateral;
		verts[6] = farPos  - farUp + farLateral;
		verts[7] = farPos  - farUp - farLateral;
	}

	//�Ƃ肠�����ʒu�𖳎����ă��C�g�r���[�s����쐬
	CMatrix lightViewMatrix = DirectX::XMMatrixLookToLH( CVector4(0,0,0,1), m_dir, CVector3::Up() );

	//���C�g�̃r���[�s��ŕϊ�
	for( CVector3& v : verts ){
		lightViewMatrix.Mul( v );
	}

	//AABB���쐬
	constexpr float max_float = std::numeric_limits<float>().max();
	constexpr float min_float = std::numeric_limits<float>().min();
	CVector3 minPos{ max_float ,max_float ,max_float };
	CVector3 maxPos{ min_float ,min_float ,min_float };
	for( CVector3& v : verts ){
		minPos.Min( v );
		maxPos.Max( v );
	}

	CVector3 centerPos = ( minPos + maxPos ) / 2; //AABB�̒��S
	CVector3 newPos = ( minPos + maxPos ) / 2; //AABB�̒��S
	float moveBack = ( newPos.z - minPos.z ) + g_camera3D.GetNear(); //���S����ł���O�܂ł̋����{�j�A�N���b�v
	newPos.z -= moveBack+1000; //�V�����J������Ԃł̃��C�g�J�������W

	//AABB�ɂ��������ăr���[�s��A�v���W�F�N�V�����s����Đݒ�
	lightViewMatrix.v[3] -= CVector4(newPos, 0);

	CMatrix lightProjMatrix =
		DirectX::XMMatrixOrthographicLH( maxPos.x - minPos.x, maxPos.y - minPos.y,
										g_camera3D.GetNear(), maxPos.z - minPos.z + g_camera3D.GetNear() + 1000 );


	//�����_�[�^�[�Q�b�g�ƃr���[�|�[�g���X�V
	m_renderTarget.SetToContext( dc );

	//�V���h�E�}�b�v���N���A�B��ԉ���Z��1.0�Ȃ̂ŁA1.0�œh��Ԃ��B
	m_renderTarget.Clear( CVector4( 1.0f, 1.0f, 1.0f, 1.0f ) );

	//�`��
	for( SkinModelRender* r : casters ){
		r->Render( EnRenderMode::ShadowMap, lightViewMatrix, lightProjMatrix );
	}

	//���ۂ̃��f���`��̍ۂɂ����r���[�v���W�F�N�V�����s���ݒ�
	m_vpMat.Mul( lightViewMatrix, lightProjMatrix );
}
