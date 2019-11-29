#pragma once
#include "..\RenderTarget.h"

class Bloom{
public:
    Bloom();
    ~Bloom();

    void Init();
    void ApplyEffect();

private:
    static constexpr UINT progressNum = 4;
    RenderTarget progressTargets[progressNum]; //ダウンサンプリング用ターゲット
    RenderTarget lastPlusTarget; //最終加算合成用ターゲット
};

