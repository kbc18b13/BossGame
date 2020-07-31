#pragma once

template<int N>
struct CVecVariable{};

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