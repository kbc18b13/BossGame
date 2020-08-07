/*!
 * @brief	ベクトルクラス。
 */

#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"

//定数
static const CQuaternion Identity( 0, 0, 0, 1 );

//行列からクォータニオンを作成。(インクルードの関係でヘッダには書けない)
void CVectorTemplates::CQuaternion::SetRotation( const CMatrix & m ){
	DirectX::XMStoreFloat4( &vec, DirectX::XMQuaternionRotationMatrix( m ) );
}

void CQuaternion::SetRotation( const CVector3 & axis, float angle ){
	float s;
	float halfAngle = angle * 0.5f;
	s = sin( halfAngle );
	w = cos( halfAngle );
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
}

void CQuaternion::SetRotationVec( CVector3 from, CVector3 to ){
	from.Normalize();
	to.Normalize();
	float angle = acosf( from.Dot( to ) );
	from.Cross( to );
	from.Normalize();

	SetRotation( from, angle );
}
