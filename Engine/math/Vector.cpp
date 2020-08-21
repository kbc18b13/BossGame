/*!
 * @brief	�x�N�g���N���X�B
 */

#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"

namespace CVectorTemplates{
//�萔
const CQuaternion CQuaternion::Identity( 0, 0, 0, 1 );

//�s�񂩂�N�H�[�^�j�I�����쐬�B(�C���N���[�h�̊֌W�Ńw�b�_�ɂ͏����Ȃ�)
void CQuaternion::SetRotation( const CMatrix & m ){
	DirectX::XMStoreFloat4( &vec, DirectX::XMQuaternionRotationMatrix( m ) );
}

void CQuaternion::SetRotation( const CVector<3> & axis, float angle ){
	float s;
	float halfAngle = angle * 0.5f;
	s = sin( halfAngle );
	w = cos( halfAngle );
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
}

void CQuaternion::SetRotationVec( CVector<3> from, CVector<3> to ){
	from.Normalize();
	to.Normalize();
	float angle = acosf( from.Dot( to ) );
	from.Cross( to );
	from.Normalize();

	SetRotation( from, angle );
}

void CQuaternion::Multiply( const CQuaternion & rot ){
	float pw, px, py, pz;
	float qw, qx, qy, qz;

	pw = w; px = x; py = y; pz = z;
	qw = rot.w; qx = rot.x; qy = rot.y; qz = rot.z;

	w = pw * qw - px * qx - py * qy - pz * qz;
	x = pw * qx + px * qw + py * qz - pz * qy;
	y = pw * qy - px * qz + py * qw + pz * qx;
	z = pw * qz + px * qy - py * qx + pz * qw;

}

}