#if VEC_TYPE == 2

#define VEC_NAME CVector2
#define VEC_LOAD(x) DirectX::XMLoadFloat2((x));
#define VEC_STORE(x) DirectX::XMStoreFloat2( &vec, (x) );

#elif VEC_TYPE == 3

#define VEC_NAME CVector3
#define VEC_LOAD(x) DirectX::XMLoadFloat3((x));
#define VEC_STORE(x) DirectX::XMStoreFloat3( &vec, (x) );

#elif VEC_TYPE == 4

#define VEC_NAME CVector4
#define VEC_LOAD(x) DirectX::XMLoadFloat4((x));
#define VEC_STORE(x) DirectX::XMStoreFloat4( &vec, (x) );

#endif

//Žl‘¥‰‰ŽZ‘ã“ü‰‰ŽZŽq
const VEC_NAME& operator+=( const VEC_NAME& param ){
	DirectX::XMVECTOR xmv0 = VEC_LOAD(&vec);
	DirectX::XMVECTOR xmv1 = VEC_LOAD( &param.vec );
	DirectX::XMVECTOR xmvr = DirectX::XMVectorAdd( xmv0, xmv1 );
	VEC_STORE( xmvr );
	return *this;
}

const VEC_NAME operator-=( const VEC_NAME& param ){
	DirectX::XMVECTOR xmv0 = VEC_LOAD( &vec );
	DirectX::XMVECTOR xmv1 = VEC_LOAD( &param.vec );
	DirectX::XMVECTOR xmvr = DirectX::XMVectorSubtract( xmv0, xmv1 );
	VEC_STORE( xmvr );
	return *this;
}

const VEC_NAME operator*=( float param ){
	DirectX::XMVECTOR xmv = VEC_LOAD( &vec );
	xmv = DirectX::XMVectorScale( xmv, param );
	VEC_STORE( xmv );
	return *this;
}

const VEC_NAME operator/=( float param ){
	DirectX::XMVECTOR xmv = VEC_LOAD( &vec );
	xmv = DirectX::XMVectorScale( xmv, param );
	VEC_STORE( xmv );
	return *this;
}

//Žl‘¥‰‰ŽZŽq
const VEC_NAME operator+( const VEC_NAME& param ) const{
	VEC_NAME tempV = *this;
	tempV += param;
	return tempV;
}

const VEC_NAME operator-( const VEC_NAME& param ) const{
	VEC_NAME tempV = *this;
	tempV -= param;
	return tempV;
}

const VEC_NAME operator-() const{
	VEC_NAME tempV = *this;
	tempV *= -1;
	return tempV;
}

const VEC_NAME operator*( float param ) const{
	VEC_NAME tempV = *this;
	tempV *= param;
	return tempV;
}

const VEC_NAME operator/( float param ) const{
	VEC_NAME tempV = *this;
	tempV /= param;
	return tempV;
}

#undef VEC_NAME
#undef VEC_LOAD
#undef VEC_STORE