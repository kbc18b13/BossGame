#include "stdafx.h"
#include "Bloom.h"


Bloom::Bloom(){}


Bloom::~Bloom(){}

void Bloom::Init(){
    UINT w = FRAME_BUFFER_W;
    UINT h = FRAME_BUFFER_H;

	//輝度抽出用ターゲットを初期化
	luminanceTarget.Init( w, h, FRAME_BUFFER_FORMAT );

    //最終一歩手前用ターゲットを初期化
    hurfTarget.Init( w/2, h/2 , FRAME_BUFFER_FORMAT);

    //ダウンサンプリング用ターゲットを初期化
	ID3D11ShaderResourceView* srv = luminanceTarget.GetRenderTargetSRV();
    for( Blur& bl : downSumples ){
		bl.Init( w, h, FRAME_BUFFER_FORMAT );
		bl.SetSource( srv );
		srv = bl.GetResult();
        w /= 2;
        h /= 2;
    }
}

void Bloom::ApplyEffect( PostEffect& postEffect ){
	using PS = ID3D11PixelShader;
    ID3D11DeviceContext* dc = g_graphicsEngine->GetD3DDeviceContext();

	//輝度抽出
	luminanceTarget.SetToContext( dc );
	postEffect.DrawScreenRect( m_source, (PS*)luminanceShader.GetBody() );

	//ダウンサンプリング
	for( int i = 0; i < downSumpleNum; i++){
		downSumples[i].ApplyEffect( postEffect );
		ID3D11ShaderResourceView* srv = downSumples[i].GetResult();
		dc->PSSetShaderResources( i, 1,  &srv);
	}

	//フレームの2分の1サイズのターゲットにダウンサンプルした複数の絵の平均を出す。
	hurfTarget.SetToContext( dc );
	postEffect.DrawScreenRect((PS*)luminanceShader.GetBody() );

	//描画先をフレームバッファに
	g_graphicsEngine->BegineFrameBuffer();
	postEffect.DrawScreenRect( (PS*)lastShader.GetBody() );
}
