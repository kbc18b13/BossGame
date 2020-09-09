#pragma once
#include <chrono>
#include <string>
#include <sstream>

class DebugTimer{
public:
	void Start(){
		beforeFrame = std::chrono::system_clock::now();
	}

	void StopAndPrint(){
		auto now = std::chrono::system_clock::now();
		long long mili = std::chrono::duration_cast<std::chrono::milliseconds>( now - beforeFrame ).count();
		float duration = mili / 1000.0f;
		std::ostringstream str;
		str << "ŠÔ : " << duration << "\n";
		OutputDebugStringA(str.str().c_str());
	}

private:
	std::chrono::time_point<std::chrono::system_clock> beforeFrame;//‘OƒtƒŒ[ƒ€‚Ì
};