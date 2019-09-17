#include "stdafx.h"
#include "ResistVector3.h"

ResistVector3::ResistVector3() : x(v.x), y(v.y), z(v.z){}

void ResistVector3::Update(float resist) {
	float decay = resist * GameTime::GetDeltaTime();
	if (decay < 1) {
		v -= v * decay;
	} else {
		v = CVector3::Zero();
	}
}
