#pragma once

template<class T ,unsigned int N>
class LimitQueue{
public:
	LimitQueue(){
		static_assert( N > 0, "Array size must be greater than 0." );
	}

	void Push(const T& value){
		m_array[back] = value;

		plusOne( back );
		if( back == begin ){
			plusOne( begin );
		}
	}

	T Pop(){
		int num = begin;
		plusOne( begin );
		return m_array( num );
	}

private:
	void plusOne( unsigned int& num ){
		num++;
		if( num == N ){
			num = 0;
		}
	}

	unsigned int begin = 0;
	unsigned int back = 1;
	T m_array[N];
};

