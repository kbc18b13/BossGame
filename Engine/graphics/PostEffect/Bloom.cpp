#include "stdafx.h"
#include "Bloom.h"


Bloom::Bloom(){}


Bloom::~Bloom(){}

void Bloom::Init(){
    UINT w = FRAME_BUFFER_W / 2;
    UINT h = FRAME_BUFFER_H / 2;

    //�ŏI���Z�����p�^�[�Q�b�g��������
    lastPlusTarget.Init( w, h , FRAME_BUFFER_FORMAT);

    //�_�E���T���v�����O�p�^�[�Q�b�g��������
    for( RenderTarget& rt : progressTargets ){
        rt.Init( w, h, FRAME_BUFFER_FORMAT );
        w /= 2;
        h /= 2;
    }
}

void Bloom::ApplyEffect(){
    ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();


}
