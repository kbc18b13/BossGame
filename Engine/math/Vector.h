#pragma once
#include "kMath.h"
#include "CVecVariable.h"

class CMatrix;

template<int N>
class CVector : public CVecVariable<N>{
public:
	CVector(){}
	CVector(const CVecVariable<N>& value) : CVecVariable(value){}
	CVector(const CVector<N>& vec) : CVecVariable( vec ){}

	//XMVECTOR�ɕϊ�
	DirectX::XMVECTOR toXM() const{
		return LoadXM<N>(this->vec);
	}

	//������Z�q
	const CVector<N>& operator=( const CVector<N>& v ){
		this->vec = v.vec;
	}
	//����������Z�q
	const CVector<N>& operator+=( const CVector<N>& param ){
		DirectX::XMVECTOR r = LoadXM<N>( this->vec );
		DirectX::XMVECTOR l = LoadXM<N>( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorAdd( r, l );
		StoreXM<N>( &this->vec , a );
		return *this;
	}
	const CVector<N>& operator-=( const CVector<N>& param ){
		DirectX::XMVECTOR r = LoadXM<N>( this->vec );
		DirectX::XMVECTOR l = LoadXM<N>( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorSubtract( r, l );
		StoreXM<N>( &this->vec, a );
		return *this;
	}
	const CVector<N>& operator*=( const float& param ){
		DirectX::XMVECTOR r = LoadXM<N>( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVectorScale( r, param );
		StoreXM<N>( &this->vec, a );
		return *this;
	}
	const CVector<N>& operator/=( const float& param ){
		return *this *= (1.0f / param);
	}

	//�l�����Z�q
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

	//����
	float Length(){
		DirectX::XMVECTOR t = LoadXM<N>( this->vec );
		DirectX::XMVECTOR a = XMVectorLength<N>( t );
		return DirectX::XMVectorGetX( a );
	}
	//������2��
	float LengthSq(){
		DirectX::XMVECTOR t = LoadXM<N>( this->vec );
		DirectX::XMVECTOR a = XMVectorLengthSq<N>( t );
		return DirectX::XMVectorGetX( a );
	}
	//����
	float Dot( const CVector<N>& param ){
		DirectX::XMVECTOR l = LoadXM<N>( this->vec );
		DirectX::XMVECTOR r = LoadXM<N>( param.vec );
		DirectX::XMVECTOR a = XMVectorDot<N>( l, r );
		return DirectX::XMVectorGetX( a );
	}

//========================��������x�N�g���̎������Ƃɗp�ӂ��Ȃ���΂Ȃ�Ȃ������֐�=================
private:
	//XMFloatN����XMVECTOR�ւ̕ϊ��֐�
	template<int N>
	static DirectX::XMVECTOR LoadXM(DirectX::XMFLOAT2& p){
		return DirectX::XMLoadFloat2( &p );
	}
	template<>
	static DirectX::XMVECTOR LoadXM<3>( DirectX::XMFLOAT3& p ){
		return DirectX::XMLoadFloat3( &p );
	}
	template<>
	static DirectX::XMVECTOR LoadXM<4>( DirectX::XMFLOAT4& p ){
		return DirectX::XMLoadFloat4( &p );
	}
	//XMVECTOR����XMFloatN�֕ۑ�����֐�
	template<int N>
	static DirectX::XMVECTOR StoreXM( DirectX::XMFLOAT2* store, DirectX::XMVECTOR& p ){
		return DirectX::XMStoreFloat2( store, p );
	}
	template<>
	static DirectX::XMVECTOR StoreXM<3>( DirectX::XMFLOAT3* store, DirectX::XMVECTOR& p ){
		return DirectX::XMStoreFloat3( store, p );
	}
	template<>
	static DirectX::XMVECTOR StoreXM<4>( DirectX::XMFLOAT4* store, DirectX::XMVECTOR& p ){
		return DirectX::XMStoreFloat4( store, p );
	}
	//������Ԃ��֐�
	template<int N>
	static DirectX::XMVECTOR XMVectorLength( DirectX::XMVECTOR p ){
		return DirectX::XMVector2Length( p );
	}
	template<>
	static DirectX::XMVECTOR XMVectorLength<3>( DirectX::XMVECTOR p ){
		return DirectX::XMVector3Length( p );
	}
	template<>
	static DirectX::XMVECTOR XMVectorLength<4>( DirectX::XMVECTOR p ){
		return DirectX::XMVector4Length( p );
	}
	//������2���Ԃ��֐�
	template<int N>
	static DirectX::XMVECTOR XMVectorLengthSq( DirectX::XMVECTOR p ){
		return DirectX::XMVector2LengthSq( p );
	}
	template<>
	static DirectX::XMVECTOR XMVectorLengthSq<3>( DirectX::XMVECTOR p ){
		return DirectX::XMVector3LengthSq( p );
	}
	template<>
	static DirectX::XMVECTOR XMVectorLengthSq<4>( DirectX::XMVECTOR p ){
		return DirectX::XMVector4LengthSq( p );
	}
	//����
	template<int N>
	static DirectX::XMVECTOR XMVectorDot( DirectX::XMVECTOR l , DirectX::XMVECTOR r ){
		return DirectX::XMVector2Dot( l, r );
	}
	template<>
	static DirectX::XMVECTOR XMVectorDot<3>( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
		return DirectX::XMVector3Dot( l, r );
	}
	template<>
	static DirectX::XMVECTOR XMVectorDot<4>( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
		return DirectX::XMVector4Dot( l, r );
	}
	//�O��
	template<int N>
	static DirectX::XMVECTOR XMVectorCross( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
		return DirectX::XMVector2Cross( l, r );
	}
	template<>
	static DirectX::XMVECTOR XMVectorCross<3>( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
		return DirectX::XMVector3Cross( l, r );
	}
	template<>
	static DirectX::XMVECTOR XMVectorCross<4>( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
		return DirectX::XMVector4Cross( l, r );
	}
};

using CVector2 = CVector<2>;
using CVector3 = CVector<3>;
using CVector4 = CVector<4>;

class CQuaternion : public CVector4{
public:
	CQuaternion(){}
	CQuaternion( const CVecVariable<4>& value ) : CVector4( value ){}

	btQuaternion toBT() const{
		return btQuaternion( this->x, this->y, this->z, this->w );
	}

	//�C�ӂ̎�����̉�]�N�H�[�^�j�I�����쐬�B
	void SetRotation( const CVector3& axis, float angle ){
		float s;
		float halfAngle = angle * 0.5f;
		s = sin( halfAngle );
		w = cos( halfAngle );
		x = axis.x * s;
		y = axis.y * s;
		z = axis.z * s;
	}

};

static inline const CVector2 operator*( float lhs , const CVector2& rhs ){
	return rhs * lhs;
}
static inline const CVector3 operator*( float lhs, const CVector3& rhs ){
	return rhs * lhs;
}
static inline const CVector4 operator*( float lhs, const CVector4& rhs ){
	return rhs * lhs;
}