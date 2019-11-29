#include "stdafx.h"
#include "Bloom.h"


Bloom::Bloom(){}


Bloom::~Bloom(){}

void Bloom::Init(){
    UINT w = FRAME_BUFFER_W / 2;
    UINT h = FRAME_BUFFER_H / 2;

    //最終加算合成用ターゲットを初期化
    lastPlusTarget.Init( w, h , FRAME_BUFFER_FORMAT);

    //ダウンサンプリング用ターゲットを初期化
    for( RenderTarget& rt : progressTargets ){
        rt.Init( w, h, FRAME_BUFFER_FORMAT );
        w /= 2;
        h /= 2;
    }
}

void Bloom::ApplyEffect(){
    ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();


}
