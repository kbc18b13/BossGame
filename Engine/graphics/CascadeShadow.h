#pragma once
#include "RenderTarget.h"
#include "CascadePart.h"
#include "graphics/Parts/ConstantBuffer.h"

class SkinModelRender;

class CascadeShadow{
public:
	CascadeShadow();
	~CascadeShadow();

	void Init( unsigned int w, unsigned int h );

	void AddShadowCaster( SkinModelRender* render ){
		m_shadowCasters.push_back( render );
	}
	void RemoveShadowCaster( SkinModelRender* render );


	/// <summary>
	/// �V���h�E�}�b�v�ɕ`��B
	/// </summary>
	void RenderToShadowMap( ID3D11DeviceContext* dc );

	/// <summary>
	/// �V���h�E�}�b�v��SRV���擾�B
	/// </summary>
	ID3D11ShaderResourceView** GetSRVPointer(){
		return partSRVs;
	}

	/// <summary>
	/// �V���h�E�}�b�v��SRV�����擾
	/// </summary>
	int GetSRVNum()const{
		return partNum;
	}

private:
	void UpdateMatirx(CVector3( &verts )[8] );

	CVector3 m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget = CVector3::Zero();	//���C�g�J�����̒����_�B
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//���C�g�v���W�F�N�V�����s��B
	
	ComPtr<ID3D11SamplerState> m_sampler;//�T���v���X�e�[�g

	//�����̐�
	static constexpr int partNum = 5;

	//�������Ƃ�SRV
	ID3D11ShaderResourceView* partSRVs[partNum];

	//�����`��I�u�W�F�N�g
	CascadePart parts[partNum];

	//�������Ƃ�VP�s��
	CMatrix partVPMats[partNum];
	ConstantBuffer shadowVCB;

	//�������Ƃ̃t�@�[�N���b�v
	float partFarClips[partNum];
	ConstantBuffer shadowPCB;


	std::vector<SkinModelRender*> m_shadowCasters;

	CVector3 m_dir{ -1, -1, -1 };
};

