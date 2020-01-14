#include "stdafx.h"
#include "Sword.h"
#include "graphics/SkinModelRender.h"
#include "physics/CollisionAttr.h"
#include "Player.h"

struct SwordContactResult : btCollisionWorld::ContactResultCallback{

    std::vector<Actor*> hitEnemys;

    btScalar	addSingleResult( btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap,
                                 int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap,
                                 int partId1, int index1 ){
        //敵のコリジョンに当たった時、その敵のポインタを記憶する。
        const btCollisionObject* co = colObj1Wrap->getCollisionObject();
        if( co->getUserIndex() == enCollisionAttr_Enemy ){
            Actor* enemy = static_cast<Actor*>( co->getUserPointer() );
            hitEnemys.push_back( enemy );
        }
        return 0.0f;
    }
};

Sword::Sword(){}

Sword::~Sword(){
	g_physics.RemoveCollision( m_collision );
}

void Sword::Init( Bone* handBone, Player* player ){
    m_model.Init( L"Assets/modelData/Sword.cmo" );

    m_collider.Create( { 13,5,5 } );
    m_collision.Create( m_collider );
    m_collision.SetGroup( 1 );
    m_collision.SetMask( 0 );
    m_collision.SetUserPointer( player );
    g_physics.AddCollision( m_collision );

	m_player = player;

    m_hand = handBone;
}

void Sword::Update(){
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
        SwordContactResult result;
        g_physics.GetDynamicWorld()->contactTest( m_collision.GetBody(), result );

        for( Actor* a : result.hitEnemys ){
            a->Damage(damage, coolTime, m_player);
        }
    }
}

void Sword::SlashStart(){
    m_isSlash = true;
}

void Sword::SlashEnd(){
    m_isSlash = false;
}
