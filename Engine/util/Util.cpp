#include "stdafx.h"
#include "Util.h"
#include <random>
#include <time.h>

static std::mt19937& getRand() {
	static std::mt19937 mt(time(0));
	return mt;
}

int Util::RandomInt(int begine, int end) {
	std::uniform_int_distribution<int> l_rand(begine, end);
	return l_rand(getRand());
}

int Util::RandomFloat(float begine, float end) {
	std::uniform_real_distribution<float> l_rand(begine, end);
	return l_rand(getRand());
}

CQuaternion Util::LookRotXZ(CVector3 lookVec, CVector3 nowFront) {
	lookVec.y = 0;
	nowFront.y = 0;
	lookVec.Normalize();
	nowFront.Normalize();
	float d = lookVec.Dot(nowFront);
	float rot = acosf(d);
	lookVec.Cross(nowFront);
	if (lookVec.y > 0) {
		rot *= -1;
	}
	CQuaternion qRot;
	qRot.SetRotation(CVector3::AxisY(), rot);

	return qRot;
}
