#include "stdafx.h"
#include "Sword.h"
#include "graphics/SkinModelRender.h"
#include "physics/CollisionAttr.h"
#include "Actor/Actor.h"

struct SwordContactResult : btCollisionWorld::ContactResultCallback{

	SwordContactResult(bool players){
		if( players ){
			target = enCollisionAttr_Enemy;
		} else{
			target = enCollisionAttr_Player;
		}
	}

    std::vector<Actor*> hitEnemys;

    btScalar	addSingleResult( btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
                                 int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap,
                                 int partId1, int index1 ){
        //敵のコリジョンに当たった時、その敵のポインタを記憶する。
        const btCollisionObject* co = colObj1Wrap->getCollisionObject();
        if( co->getUserIndex() == target ){
            Actor* enemy = static_cast<Actor*>( co->getUserPointer() );
            hitEnemys.push_back( enemy );
        }
        return 0.0f;
    }

private:
	EnCollisionAttr target;
};

Sword::Sword(){}

Sword::~Sword(){
	g_physics.RemoveCollision( m_collision );
}

void Sword::Init( Bone* handBone, Actor* master , const CVector3& halfExtents,
				  const wchar_t* modelpath, bool playersSword){
    m_model.Init( modelpath );
    m_collider.Create( halfExtents );
    m_collision.Create( m_collider );
    m_collision.SetGroup( 1 );
    m_collision.SetMask( 0 );
    m_collision.SetUserPointer( master );
    g_physics.AddCollision( m_collision );

	m_isPlayers = playersSword;

	m_master = master;

    m_hand = handBone;
}

void Sword::Update(){
	if( !m_isActive ){
		return;
	}

    //位置の更新
    {
        const CMatrix& worldMat = m_hand->GetWorldMatrix();

        CQuaternion rot;
        rot.SetRotation( worldMat );
        m_collision.GetBody()->getWorldTransform().setRotation( rot );

        CVector3 offset = m_offset;
        rot.Multiply( offset );
        CVector3 position = CVector3( worldMat.v[3] ) + offset;
        m_collision.GetBody()->getWorldTransform().setOrigin( position );

        m_model.SetWorldMatrix( worldMat );
        m_model.Update();
    }

    //敵へのダメージ処理
    if( m_isSlash ){
        SwordContactResult result(m_isPlayers);
        g_physics.GetDynamicWorld()->contactTest( m_collision.GetBody(), result );

        for( Actor* a : result.hitEnemys ){
            a->Damage(m_damage, m_coolTime, m_master);
        }
    }
}

void Sword::SlashStart(){
    m_isSlash = true;
}

void Sword::SlashEnd(){
    m_isSlash = false;
}

void Sword::SetActive( bool active ){
	if( m_isActive && !active ){
		g_physics.RemoveCollision( m_collision );
	}
	if( !m_isActive && active ){
		g_physics.AddCollision( m_collision );
	}
	m_isActive = active;
	m_model.SetActive( active );
}
