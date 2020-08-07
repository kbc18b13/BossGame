#pragma once
#include "kMath.h"
#include "CVecVariable.h"

class CMatrix;

namespace CVectorTemplates{

//型がすべてfloatに変換できるかをチェックする変数
template<typename T, typename ...U>
static constexpr bool is_all_float = std::is_convertible_v<T, float> && is_all_float<U...>;
template<typename T>
static constexpr bool is_all_float<T> = std::is_convertible_v<T, float>;

//ベクトル
template<int N>
class CVector : public CVecVariable<N>{
public:
	CVector(){}
	CVector( const CVecVariable<N>& value ) : CVecVariable( value ){}
	CVector( const CVector<N>& vec ) : CVecVariable( vec ){}
	template<typename ...T>
	CVector(/* typename std::enable_if<is_all_float<T...> && sizeof...( T ) == N-1, float>::type p1, */T ...p2 )
	: CVecVariable( p2... ){}

	//XMVECTORに変換
	DirectX::XMVECTOR toXM() const{
		return LoadXM( this->vec );
	}

	//代入演算子
	const CVector<N>& operator=( const CVector<N>& v ){
		this->vec = v.vec;
	}
	//複合代入演算子
	const CVector<N>& operator+=( const CVector<N>& param ){
		DirectX::XMVECTOR r = LoadXM( this->vec );
		DirectX::XMVECTOR l = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorAdd( r, l );
		StoreXM( &this->vec, a );
	}
	const CVector<N>& operator-=( const CVector<N>& param ){
		DirectX::XMVECTOR r = LoadXM( this->vec );
		DirectX::XMVECTOR l = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorSubtract( r, l );
		StoreXM( &this->vec, a );
		return *this;
	}
	const CVector<N>& operator*=( const float& param ){
		DirectX::XMVECTOR r = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVectorScale( r, param );
		StoreXM( &this->vec, a );
		return *this;
	}
	const CVector<N>& operator/=( const float& param ){
		return *this *= ( 1.0f / param );
	}

	//四則演算子
	const CVector<N> operator+( const CVector<N>& param )const{
		CVector<N> temp = *this;
		temp += param;
		return temp;
	}
	const CVector<N> operator-( const CVector<N>& param )const{
		CVector<N> temp = *this;
		temp -= param;
		return temp;
	}
	const CVector<N> operator*( const float& param )const{
		CVector<N> temp = *this;
		temp *= param;
		return temp;
	}
	const CVector<N> operator/( const float& param )const{
		CVector<N> temp = *this;
		temp /= param;
		return temp;
	}

	//長さ
	float Length(){
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = XMVectorLength<N>( t );
		return DirectX::XMVectorGetX( a );
	}
	//長さの2乗
	float LengthSq(){
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = XMVectorLengthSq<N>( t );
		return DirectX::XMVectorGetX( a );
	}
	//正規化
	void Normalize(){
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = XMVectorNormalize<N>( t );
		StoreXM( &this->vec, a );
	}
	//内積
	float Dot( const CVector<N>& param ){
		DirectX::XMVECTOR l = LoadXM( this->vec );
		DirectX::XMVECTOR r = LoadXM( param.vec );
		DirectX::XMVECTOR a = XMVectorDot<N>( l, r );
		return DirectX::XMVectorGetX( a );
	}
	//外積
	auto Cross( const CVector<N>& param ){
		DirectX::XMVECTOR l = LoadXM( this->vec );
		DirectX::XMVECTOR r = LoadXM( param.vec );
		DirectX::XMVECTOR a = XMVectorCross<N>( l, r );
		if constexpr( N == 2 ){
			return DirectX::XMVectorGetX( a );
		} else if constexpr( N == 3 ){
			CVector<3> tempV;
			StoreXM( &tempV.vec, a );
			return tempV;
		} else{
			abort();
		}
	}


	//======================定数=======================
	static const CVector<N> AxisX;
	static const CVector<N> AxisY;
	static const CVector<N> AxisZ;
};

template<int N>
const CVector<N> CVector<N>::AxisX = VariableAxisX<N>();
template<int N>
const CVector<N> CVector<N>::AxisY = VariableAxisY<N>();
template<int N>
const CVector<N> CVector<N>::AxisZ = VariableAxisZ<N>();


//クォータニオン
class CQuaternion : public CVector<4>{
public:
	CQuaternion(){}
	CQuaternion( const CVecVariable<4>& value ) : CVector<4>( value ){}

	btQuaternion toBT() const{
		return btQuaternion( this->x, this->y, this->z, this->w );
	}

	//任意の軸周りの回転クォータニオンを作成。
	void SetRotation( const CMatrix& m );
	void SetRotation( const CVector3& axis, float angle );
	//ベクトルからベクトルへの回転クォータニオンを作成。
	void SetRotationVec( CVector3 from, CVector3 to );
};

static const CQuaternion Identity;

}

using CVector2 = CVectorTemplates::CVector<2>;
using CVector3 = CVectorTemplates::CVector<3>;
using CVector4 = CVectorTemplates::CVector<4>;
using CQuaternion = CVectorTemplates::CQuaternion;

static inline const CVector2 operator*( float lhs , const CVector2& rhs ){
	return rhs * lhs;
}
static inline const CVector3 operator*( float lhs, const CVector3& rhs ){
	return rhs * lhs;
}
static inline const CVector4 operator*( float lhs, const CVector4& rhs ){
	return rhs * lhs;
}