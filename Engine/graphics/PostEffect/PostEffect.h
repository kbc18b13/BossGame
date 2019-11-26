#pragma once
#include "..\Shader.h"


class PostEffect {
public:
    PostEffect();
    ~PostEffect();

    void Init();

    void DrawScreenRect(ID3D11PixelShader* pixelShader, ID3D11ShaderResourceView* srv);

private:
    Shader vsShader;
    ID3D11Buffer* vertexBuf;
};

