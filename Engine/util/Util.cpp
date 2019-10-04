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
