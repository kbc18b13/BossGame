/*!
 * @brief	���[�e�B���e�B�֐��B
 */
#pragma once
#include <fstream>

class Util{
public:
	/*!
	 * @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
	 */
	static int MakeHash( const char* string )
	{
		int hash = 0;
		int l = (int)strlen(string);
		for( int i = 0; i < l; i++ ){
			hash = hash * 37 + string[i];
		}
		return hash;
	}

	/*!
	* @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
	*/
	static int MakeHash(const wchar_t* string)
	{
		int hash = 0;
		int l = (int)wcslen(string);
		for (int i = 0; i < l; i++) {
			hash = hash * 37 + string[i];
		}
		return hash;
	}

	template<typename T>
	static T readBinary( std::ifstream& ifs ){
		T value;
		ifs.read( reinterpret_cast<char*>(&value), sizeof( T ) );
		return value;
	}

	//������Ԃ�
	template<typename T>
	static T Sign( T A ){
		return ( A > 0 ) - ( A < 0 );
	}

	//�����_����Int�l��Ԃ��B�͈͂�end���܂ށB
	static int RandomInt(int begine, int end);
	//�����_����float�l��Ԃ��B�͈͂�end���܂܂Ȃ��B
	static float RandomFloat(float begine, float end);

	//�w��ꏊ�����������]��^����
	static CQuaternion LookRot( CVector3 lookVec, CVector3 nowFront = CVector3::AxisZ() );

	//�w��ꏊ�����������]��^����B�����ŉ�]�ʂ��w��ł���B�Ⴆ��0.5���Ɣ���������]���Ȃ��B
	static CQuaternion LookRotSLerp( CVector3 lookVec, CVector3 nowFront, float lerp );

	//Y�𖳎����Ďw��ꏊ�����������]��^����B
	static CQuaternion LookRotXZ(CVector3 lookVec, CVector3 nowFront = CVector3::AxisZ());

	static constexpr size_t AlignSize(size_t size , UINT multiple ){
		return ( ( ( size - 1 ) / multiple ) + 1 ) * multiple;
	}

	template<typename T>
	static constexpr T clamp( T v, T min, T max ){
		return v < min ? min : ( v > max  ? max : v);
	}
};

//2��
static inline constexpr float pow2( float f ){
	return f * f;
}

//�ݏ�
template<typename T>
static constexpr T CPow( T base, unsigned int exp ){
	T ans = 1;
	for( unsigned int i = 0; i < exp; i++ ){
		ans *= base;
	}
	return ans;
}

template<typename T>
class IndicesContainer{
public:
	IndicesContainer( T& container ) : container( container ){}

	class Itr{
	public:
		Itr( int now ) : n( now ){}
		Itr( const Itr& itr ) : n( itr.n ){}

		int operator*(){
			return n;
		}

		Itr operator++(){
			n++; return *this;
		}

		bool operator !=( Itr& itr ){
			return itr.n != n;
		}

	private:
		int n;
	};

	Itr begin() const{
		return Itr( 0 );
	}

	Itr end() const{
		return Itr( container.size() );
	}

private:
	T& container;
};

template<typename T>
IndicesContainer<T> Indices( T& container ){
	return IndicesContainer<T>( container );
}