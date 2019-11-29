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
    RenderTarget progressTargets[progressNum]; //�_�E���T���v�����O�p�^�[�Q�b�g
    RenderTarget lastPlusTarget; //�ŏI���Z�����p�^�[�Q�b�g
};

