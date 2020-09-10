#pragma once

template<unsigned int N>
class FpsStock{
public:
	FpsStock() : m_array{}{
		static_assert( N > 0, "Array size must be greater than 0." );
	}

	void Push(float value){
		nowTotal -= m_array[next];
		m_array[next] = value;
		nowTotal += value;

		next++;
		if( next == N ){
			next = 0;
		}
	}

	float GetAverage(){
		return nowTotal / N;
	}

private:
	unsigned int next = 0;
	float m_array[N];
	float nowTotal = 0;
};

