#pragma once
#include "RenderMachine.h"

class IRenderObject {
public:
    virtual ~IRenderObject() {
        machine->RemoveRenderObject( this );
    };
    virtual void Render() = 0;

private:
    friend class RenderMachine;
    friend class RenderObjectManager;
    RenderMachine* machine;
    UINT index;
};
