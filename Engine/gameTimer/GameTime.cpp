#include "stdafx.h"
#include "GameTime.h"
#include <chrono>
#include "FpsStock.h"

using namespace std::chrono;
namespace GameTime {

static time_point<system_clock> beforeFrame;//前フレームの時刻
static float deltaTime = 1;//前フレームとの差
static FpsStock<50> fpsStock;

void UpdateTime() {
	auto now = system_clock::now();
	long long mili = duration_cast<milliseconds>(now - beforeFrame).count();
	deltaTime = mili / 1000.0f;
	fpsStock.Push( 1.0f / deltaTime );
	beforeFrame = now;
}

float GetFPS(){
	return fpsStock.GetAverage();
}

float GetDeltaTime() {
	return std::min(deltaTime, 1.0f/20.0f);
}

}