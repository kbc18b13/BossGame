#include "stdafx.h"
#include "GameTime.h"
#include <chrono>
using namespace std::chrono;
namespace GameTime {

static time_point<system_clock> beforeFrame;//�O�t���[���̎���
static float deltaTime = 0;//�O�t���[���Ƃ̍�

void UpdateTime() {
	auto now = system_clock::now();
	long long mili = duration_cast<milliseconds>(now - beforeFrame).count();
	deltaTime = mili / 1000.0f;
	beforeFrame = now;
}

float GetDeltaTime() {
	return deltaTime;
}

}