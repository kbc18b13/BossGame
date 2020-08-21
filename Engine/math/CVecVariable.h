#pragma once

namespace CVectorTemplates{

//========================ベクトルの次元ごとに用意された変数、共用体=================
template<int N>
struct CVecVariable;

template<>
struct CVecVariable<2>{
	CVecVariable() : v{}{};
	CVecVariable( const CVecVariable& v ) : x( v.x ), y( v.y ){}
	CVecVariable( float x, float y ) : x( x ), y( x ){}
	union{
		DirectX::XMFLOAT2 vec;
		struct{ float x, y; };
		float v[2];
	};
};

template<>
struct CVecVariable<3>{
	CVecVariable() : v{}{};
	CVecVariable( const CVecVariable& v ) : x( v.x ), y( v.y ), z( v.z ){}
	CVecVariable( float x, float y, float z ) : x( x ), y( x ), z( z ){}
	union{
		DirectX::XMFLOAT3 vec;
		struct{ float x, y, z; };
		float v[3];
	};
};

template<>
struct CVecVariable<4>{
	CVecVariable() : v{}{};
	CVecVariable( const CVecVariable& v ) : x( v.x ), y( v.y ), z( v.z ), w( v.w ){}
	CVecVariable( float x, float y, float z, float w ) : x( x ), y( x ), z( z ), w( w ){}
	union{
		DirectX::XMFLOAT4 vec;
		struct{ float x, y, z, w; };
		float v[4];
	};
};


//========================ベクトルの次元ごとに用意しなければならなかった関数=================
//XMFloatNからXMVECTORへの変換関数
static inline DirectX::XMVECTOR LoadXM( const DirectX::XMFLOAT2& p ){
	return DirectX::XMLoadFloat2( &p );
}
static inline DirectX::XMVECTOR LoadXM( const DirectX::XMFLOAT3& p ){
	return DirectX::XMLoadFloat3( &p );
}
static inline DirectX::XMVECTOR LoadXM( const DirectX::XMFLOAT4& p ){
	return DirectX::XMLoadFloat4( &p );
}

//XMVECTORからXMFloatNへ保存する関数
static inline void StoreXM( DirectX::XMFLOAT2* store, DirectX::XMVECTOR& p ){
	return DirectX::XMStoreFloat2( store, p );
}
static inline void StoreXM( DirectX::XMFLOAT3* store, DirectX::XMVECTOR& p ){
	return DirectX::XMStoreFloat3( store, p );
}
static inline void StoreXM( DirectX::XMFLOAT4* store, DirectX::XMVECTOR& p ){
	return DirectX::XMStoreFloat4( store, p );
}

//長さを返す関数
template<int N>
static inline DirectX::XMVECTOR XMVectorLength( DirectX::XMVECTOR p ){
	return DirectX::XMVector2Length( p );
}
template<>
static inline DirectX::XMVECTOR XMVectorLength<3>( DirectX::XMVECTOR p ){
	return DirectX::XMVector3Length( p );
}
template<>
static inline DirectX::XMVECTOR XMVectorLength<4>( DirectX::XMVECTOR p ){
	return DirectX::XMVector4Length( p );
}

//長さの2乗を返す関数
template<int N>
static inline DirectX::XMVECTOR XMVectorLengthSq( DirectX::XMVECTOR p ){
	return DirectX::XMVector2LengthSq( p );
}
template<>
static inline DirectX::XMVECTOR XMVectorLengthSq<3>( DirectX::XMVECTOR p ){
	return DirectX::XMVector3LengthSq( p );
}
template<>
static inline DirectX::XMVECTOR XMVectorLengthSq<4>( DirectX::XMVECTOR p ){
	return DirectX::XMVector4LengthSq( p );
}

//正規化
template<int N>
static inline DirectX::XMVECTOR XMVectorNormalize( DirectX::XMVECTOR p ){
	return DirectX::XMVector2Normalize( p );
}
template<>
static inline DirectX::XMVECTOR XMVectorNormalize<3>( DirectX::XMVECTOR p ){
	return DirectX::XMVector3Normalize( p );
}
template<>
static inline DirectX::XMVECTOR XMVectorNormalize<4>( DirectX::XMVECTOR p ){
	return DirectX::XMVector4Normalize( p );
}

//内積
template<int N>
static inline DirectX::XMVECTOR XMVectorDot( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
	return DirectX::XMVector2Dot( l, r );
}
template<>
static inline DirectX::XMVECTOR XMVectorDot<3>( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
	return DirectX::XMVector3Dot( l, r );
}
template<>
static inline DirectX::XMVECTOR XMVectorDot<4>( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
	return DirectX::XMVector4Dot( l, r );
}

//外積
template<int N>
static inline DirectX::XMVECTOR XMVectorCross( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
	return DirectX::XMVector2Cross( l, r );
}
template<>
static inline DirectX::XMVECTOR XMVectorCross<3>( DirectX::XMVECTOR l, DirectX::XMVECTOR r ){
	return DirectX::XMVector3Cross( l, r );
}
template<>
static inline DirectX::XMVECTOR XMVectorCross<4>( DirectX::XMVECTOR l, DirectX::XMVECTOR r ) = delete;


//==============================定数を設定するための関数=============================
template<int N>
static inline CVecVariable<N> VariableAxisX(){
	CVecVariable<N> v;
	v.x = 1;
	return v;
}
template<int N>
static inline CVecVariable<N> VariableAxisY(){
	CVecVariable<N> v;
	v.y = 1;
	return v;
}
template<int N>
static inline CVecVariable<N> VariableAxisZ(){
	CVecVariable<N> v;
	if constexpr( N >= 3 ){
		v.z = 1;
	}
	return v;
}
template<int N>
static inline CVecVariable<N> VariableOne(){
	CVecVariable<N> v;
	for( int i = 0; i < N; i++ ){
		v.v[i] = 1;
	}
	return v;
}

}
