#pragma once
#include "kMath.h"

class CMatrix;

namespace CVectorTemplates{

//XMFloatN����XMVECTOR�ւ̕ϊ��֐�
static inline DirectX::XMVECTOR LoadXM( const DirectX::XMFLOAT2& p ){
	return DirectX::XMLoadFloat2( &p );
}
static inline DirectX::XMVECTOR LoadXM( const DirectX::XMFLOAT3& p ){
	return DirectX::XMLoadFloat3( &p );
}
static inline DirectX::XMVECTOR LoadXM( const DirectX::XMFLOAT4& p ){
	return DirectX::XMLoadFloat4( &p );
}

//XMVECTOR����XMFloatN�֕ۑ�����֐�
static inline void StoreXM( DirectX::XMFLOAT2* store, const DirectX::XMVECTOR& p ){
	return DirectX::XMStoreFloat2( store, p );
}
static inline void StoreXM( DirectX::XMFLOAT3* store, const DirectX::XMVECTOR& p ){
	return DirectX::XMStoreFloat3( store, p );
}
static inline void StoreXM( DirectX::XMFLOAT4* store, const DirectX::XMVECTOR& p ){
	return DirectX::XMStoreFloat4( store, p );
}

class CVector2{
public:
	union{
		DirectX::XMFLOAT2 vec;
		struct{ float x, y; };
		float v[2];
	};

	//�R���X�g���N�^
	CVector2() : v{}{}
	CVector2( const CVector2& vec ) : vec( vec.vec ){}
	CVector2( float x, float y ) : v{ x, y }{}

	//XMVECTOR�ɕϊ�
	DirectX::XMVECTOR toXM() const{
		return LoadXM( vec );
	}

	//������Z�q
	const CVector2& operator=( const CVector2& v ){
		vec = v.vec;
		return *this;
	}

	//����������Z�q
	const CVector2& operator+=( const CVector2& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR l = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorAdd( r, l );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector2& operator-=( const CVector2& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR l = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorSubtract( r, l );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector2& operator*=( const float& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR a = DirectX::XMVectorScale( r, param );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector2& operator/=( const float& param ){
		return *this *= ( 1.0f / param );
	}

	//�l�����Z�q
	const CVector2 operator+( const CVector2& param )const{
		CVector2 temp = *this;
		temp += param;
		return temp;
	}
	const CVector2 operator-( const CVector2& param )const{
		CVector2 temp = *this;
		temp -= param;
		return temp;
	}
	const CVector2 operator*( const float& param )const{
		CVector2 temp = *this;
		temp *= param;
		return temp;
	}
	const CVector2 operator/( const float& param )const{
		CVector2 temp = *this;
		temp /= param;
		return temp;
	}

	const CVector2 operator-()const{
		return *this * -1;
	}

	//����
	float Length()const{
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector2Length( t );
		return DirectX::XMVectorGetX( a );
	}
	//������2��
	float LengthSq()const{
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector2LengthSq( t );
		return DirectX::XMVectorGetX( a );
	}
	//���K��
	void Normalize(){
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector2Normalize( t );
		StoreXM( &this->vec, a );
	}
	//����
	float Dot( const CVector2& param )const{
		DirectX::XMVECTOR l = LoadXM( this->vec );
		DirectX::XMVECTOR r = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVector2Dot( l, r );
		return DirectX::XMVectorGetX( a );
	}
	//�O��
	float Cross( const CVector2& param )const{
		DirectX::XMVECTOR l = LoadXM( this->vec );
		DirectX::XMVECTOR r = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVector2Cross( l, r );
		return DirectX::XMVectorGetX( a );
	}

	//======================�萔=======================
	static CVector2 AxisX(){
		static CVector2 cv( 1, 0 ); return cv;
	};
	static CVector2 AxisY(){
		static CVector2 cv( 0, 1 ); return cv;
	};
	static CVector2 One(){
		static CVector2 cv( 1, 1 ); return cv;
	};
	static CVector2 Zero(){
		static CVector2 cv( 0, 0 ); return cv;
	};
};

class CVector3{
public:
	union{
		DirectX::XMFLOAT3 vec;
		struct{ float x, y, z; };
		float v[3];
	};

	//�R���X�g���N�^
	CVector3() : v{}{}
	CVector3( const CVector3& vec ) : vec( vec.vec ){}
	CVector3( float x, float y, float z ) : v{ x, y, z }{}
	explicit CVector3( const btVector3& _v ) : v{ _v.x(), _v.y(), _v.z() }{}

	//XMVECTOR�ɕϊ�
	DirectX::XMVECTOR toXM() const{
		return LoadXM( vec );
	}
	//btVector�ɕϊ�
	btVector3 toBT() const{
		return btVector3( x, y, z );
	}

	//������Z�q
	const CVector3& operator=( const CVector3& v ){
		vec = v.vec;
		return *this;
	}

	//����������Z�q
	const CVector3& operator+=( const CVector3& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR l = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorAdd( r, l );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector3& operator-=( const CVector3& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR l = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorSubtract( r, l );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector3& operator*=( const float& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR a = DirectX::XMVectorScale( r, param );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector3& operator/=( const float& param ){
		return *this *= ( 1.0f / param );
	}

	//�l�����Z�q
	const CVector3 operator+( const CVector3& param )const{
		CVector3 temp = *this;
		temp += param;
		return temp;
	}
	const CVector3 operator-( const CVector3& param )const{
		CVector3 temp = *this;
		temp -= param;
		return temp;
	}
	const CVector3 operator*( const float& param )const{
		CVector3 temp = *this;
		temp *= param;
		return temp;
	}
	const CVector3 operator/( const float& param )const{
		CVector3 temp = *this;
		temp /= param;
		return temp;
	}

	const CVector3 operator-()const{
		return *this * -1;
	}

	//����
	float Length()const{
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector3Length( t );
		return DirectX::XMVectorGetX( a );
	}
	//������2��
	float LengthSq()const{
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector3LengthSq( t );
		return DirectX::XMVectorGetX( a );
	}
	
	//2�_�Ԃ̋���
	float Distance(const CVector3& point)const{
		return operator-( point ).Length();
	}

	//2�_�Ԃ̋�����2��
	float DistanceSq( const CVector3& point )const{
		return operator-( point ).LengthSq();
	}
	
	//���K��
	void Normalize(){
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector3Normalize( t );
		StoreXM( &this->vec, a );
	}

	CVector3 GetNormalized() const{
		CVector3 temp = *this;
		temp.Normalize();
		return temp;
	}

	//����
	float Dot( const CVector3& param )const{
		DirectX::XMVECTOR l = LoadXM( this->vec );
		DirectX::XMVECTOR r = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVector3Dot( l, r );
		return DirectX::XMVectorGetX( a );
	}
	//�O��
	CVector3 Cross( const CVector3& param )const{
		DirectX::XMVECTOR l = LoadXM( this->vec );
		DirectX::XMVECTOR r = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVector3Cross( l, r );
		CVector3 tempV;
		StoreXM( &tempV.vec, a );
		return tempV;
	}

	//���`���
	void Lerp( float t, const CVector3& v0, const CVector3& v1 ){
		DirectX::XMVECTOR _v = DirectX::XMVectorLerp( LoadXM( v0.vec ), LoadXM( v1.vec ), t );
		StoreXM( &vec, _v );
	}

	//�ő�l��ݒ�B
	void Max( const CVector3& vMax ){
		DirectX::XMVECTOR xmv0 = LoadXM( vec );
		DirectX::XMVECTOR xmv1 = LoadXM( vMax.vec );
		StoreXM( &vec, DirectX::XMVectorMax( xmv0, xmv1 ) );
	}
	//�ŏ��l��ݒ�B
	void Min( const CVector3& vMin ){
		DirectX::XMVECTOR xmv0 = LoadXM( vec );
		DirectX::XMVECTOR xmv1 = LoadXM( vMin.vec );
		StoreXM( &vec, DirectX::XMVectorMin( xmv0, xmv1 ) );
	}

	void Set( float _x, float _y, float _z ){
		x = _x; y = _y; z = _z;
	}

	void Set( const btVector3& _v ){
		Set( _v.x(), _v.y(), _v.z() );
	}

	bool isZero(){
		return x == 0 && y == 0 && z == 0;
	}

	CVector2 xy() const{
		return CVector2( x, y );
	}
	CVector2 xz() const{
		return CVector2( x, z );
	}

	//======================�萔=======================
	static CVector3 AxisX(){
		static CVector3 cv( 1, 0, 0 ); return cv;
	}
	static CVector3 AxisY(){
		static CVector3 cv( 0, 1, 0 ); return cv;
	}
	static CVector3 AxisZ(){
		static CVector3 cv( 0, 0, 1 ); return cv;
	}
	static CVector3 Up(){
		static CVector3 cv( 0, 1, 0 ); return cv;
	}
	static CVector3 Down(){
		static CVector3 cv( 0, -1, 0 ); return cv;
	}
	static CVector3 One(){
		static CVector3 cv( 1, 1, 1 ); return cv;
	}
	static CVector3 Zero(){
		static CVector3 cv( 0, 0, 0 ); return cv;
	}
};

class CVector4{
public:
	union{
		DirectX::XMFLOAT4 vec;
		struct{ float x, y, z, w; };
		float v[4];
	};

	//�R���X�g���N�^
	CVector4() : v{0,0,0,1}{}
	CVector4( const CVector4& vec ) : vec( vec.vec ){}
	CVector4( float x, float y, float z, float w ) : v{ x, y, z, w }{}
	CVector4( const CVector3& v3, float e4 ) : v{ v3.x, v3.y, v3.z, e4 }{}

	operator CVector3() const{
		return CVector3( x, y, z );
	}

	//XMVECTOR�ɕϊ�
	DirectX::XMVECTOR toXM() const{
		return LoadXM( vec );
	}

	//������Z�q
	const CVector4& operator=( const CVector4& v ){
		vec = v.vec;
		return *this;
	}

	//����������Z�q
	const CVector4& operator+=( const CVector4& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR l = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorAdd( r, l );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector4& operator-=( const CVector4& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR l = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVectorSubtract( r, l );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector4& operator*=( const float& param ){
		DirectX::XMVECTOR r = LoadXM( vec );
		DirectX::XMVECTOR a = DirectX::XMVectorScale( r, param );
		StoreXM( &vec, a );
		return *this;
	}
	const CVector4& operator/=( const float& param ){
		return *this *= ( 1.0f / param );
	}

	//�l�����Z�q
	const CVector4 operator+( const CVector4& param )const{
		CVector4 temp = *this;
		temp += param;
		return temp;
	}
	const CVector4 operator-( const CVector4& param )const{
		CVector4 temp = *this;
		temp -= param;
		return temp;
	}
	const CVector4 operator*( const float& param )const{
		CVector4 temp = *this;
		temp *= param;
		return temp;
	}
	const CVector4 operator/( const float& param )const{
		CVector4 temp = *this;
		temp /= param;
		return temp;
	}

	//����
	float Length()const{
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector4Length( t );
		return DirectX::XMVectorGetX( a );
	}
	//������2��
	float LengthSq()const{
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector4LengthSq( t );
		return DirectX::XMVectorGetX( a );
	}
	//���K��
	void Normalize(){
		DirectX::XMVECTOR t = LoadXM( this->vec );
		DirectX::XMVECTOR a = DirectX::XMVector4Normalize( t );
		StoreXM( &this->vec, a );
	}
	//����
	float Dot( const CVector4& param )const{
		DirectX::XMVECTOR l = LoadXM( this->vec );
		DirectX::XMVECTOR r = LoadXM( param.vec );
		DirectX::XMVECTOR a = DirectX::XMVector4Dot( l, r );
		return DirectX::XMVectorGetX( a );
	}

	void Set( float _x, float _y, float _z, float _w ){
		x = _x; y = _y; z = _z; w = _w;
	}

	CVector2 xy() const{
		return CVector2( x, y );
	}

	//======================�萔=======================
	static const CVector4 White(){
		static CVector4 cv( 1, 1, 1, 1 ); return cv;
	}
	static const CVector4 Red(){
		static CVector4 cv( 1, 0, 0, 1 ); return cv;
	}
	static const CVector4 Green(){
		static CVector4 cv( 0, 1, 0, 1 ); return cv;
	}
	static const CVector4 Blue(){
		static CVector4 cv( 0, 0, 1, 1 ); return cv;
	}
	static const CVector4 Black(){
		static CVector4 cv( 0, 0, 0, 1 ); return cv;
	}
	static const CVector4 Zero(){
		static CVector4 cv( 0, 0, 0, 0 ); return cv;
	}
};

class CQuaternion : public CVector4{
public:
	CQuaternion() : CVector4(){}
	CQuaternion( const CQuaternion& q ) : CVector4( q ){}
	CQuaternion( float x, float y, float z, float w ) : CVector4( x, y, z, w ){}

	btQuaternion toBT() const{
		return btQuaternion( x, y, z, w );
	}

	//�C�ӂ̎�����̉�]�N�H�[�^�j�I�����쐬�B
	void SetRotation( const CMatrix& m );
	void SetRotation( const CVector3& axis, float angle );
	void SetRotationDeg( const CVector3& axis, float deg ){
		SetRotation( axis, CMath::DegToRad( deg ) );
	}
	//�x�N�g������x�N�g���ւ̉�]�N�H�[�^�j�I�����쐬�B
	void SetRotationVec( CVector3 from, CVector3 to );

	void AddRotation( const CVector3& axis, float angle ){
		Multiply( CreateRot( axis, angle ) );
	}
	void AddRotationDeg( const CVector3& axis, float deg ){
		AddRotation( axis, CMath::DegToRad( deg ) );
	}

	//�N�H�[�^�j�I�����m�̐�
	void Multiply( const CQuaternion& rot );

	//�x�N�g���ɃN�H�[�^�j�I����K�p
	void Multiply( CVector3& pVec ) const;

	//�N���X���璼�ځA�C�ӂ̎�����̉�]�N�H�[�^�j�I�����쐬�B
	static CQuaternion CreateRot( const CVector3& axis, float angle ){
		CQuaternion q;
		q.SetRotation( axis, angle );
		return q;
	}
	static CQuaternion CreateRotDeg( const CVector3& axis, float angle ){
		CQuaternion q;
		q.SetRotationDeg( axis, angle );
		return q;
	}
	static CQuaternion CreateRotVec( const CVector3& from, const CVector3& to ){
		CQuaternion q;
		q.SetRotationVec( from, to );
		return q;
	}

	//���ʐ��`�⊮�B
	void Slerp( float t, CQuaternion q1, CQuaternion q2 ){
		DirectX::XMVECTOR xmv = DirectX::XMQuaternionSlerp( LoadXM( q1.vec ), LoadXM( q2.vec ), t );
		StoreXM( &vec, xmv );
	}

	static CQuaternion Identity(){
		static CQuaternion cv( 0, 0, 0, 1 ); return cv;
	}
};

}

using CVector2 = CVectorTemplates::CVector2;
using CVector3 = CVectorTemplates::CVector3;
using CVector4 = CVectorTemplates::CVector4;
using CQuaternion = CVectorTemplates::CQuaternion;

static inline const CVector2 operator*( float lhs, const CVector2& rhs ){
	return rhs * lhs;
}
static inline const CVector3 operator*( float lhs, const CVector3& rhs ){
	return rhs * lhs;
}
static inline const CVector4 operator*( float lhs, const CVector4& rhs ){
	return rhs * lhs;
}