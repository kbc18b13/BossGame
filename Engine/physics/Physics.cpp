#include "stdafx.h"
#include "physics/Physics.h"
#include "Physics/RigidBody.h"
#include "graphics/Shader.h"
#include "DebugWireframe.h"

PhysicsWorld g_physics;
static DebugWireframe* st_debugWire;

PhysicsWorld::PhysicsWorld() {
}

PhysicsWorld::~PhysicsWorld()
{
	Release();
}
void PhysicsWorld::Release()
{
	delete dynamicWorld;
	delete constraintSolver;
	delete overlappingPairCache;
	delete collisionDispatcher;
	delete collisionConfig;
	delete st_debugWire;

	dynamicWorld = nullptr;
	constraintSolver = nullptr;
	overlappingPairCache = nullptr;
	collisionDispatcher = nullptr;
	collisionConfig = nullptr;
	st_debugWire = nullptr;
}
void PhysicsWorld::setDebugDraw(bool isDraw) {
	btIDebugDraw::DebugDrawModes mode = isDraw ? btIDebugDraw::DBG_DrawWireframe : btIDebugDraw::DBG_NoDebug;
	st_debugWire->setDebugMode(mode);
}

void PhysicsWorld::Init()
{
	Release();

	st_debugWire = new DebugWireframe();

	//物理エンジンを初期化。
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	collisionConfig = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	collisionDispatcher = new	btCollisionDispatcher(collisionConfig);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	constraintSolver = new btSequentialImpulseConstraintSolver;

	dynamicWorld = new btDiscreteDynamicsWorld(
		collisionDispatcher,
		overlappingPairCache,
		constraintSolver,
		collisionConfig
		);

	dynamicWorld->setGravity(btVector3(0, -10, 0));

	//デバッグどろーわーの指定
	dynamicWorld->setDebugDrawer(st_debugWire);
}
void PhysicsWorld::Update()
{
	dynamicWorld->stepSimulation(1.0f/60.0f);
	st_debugWire->DrawBegin();//ワイヤフレーム描画準備
	dynamicWorld->debugDrawWorld();//デバッグワイヤーフレームの描画
	int i = 0;
}
void PhysicsWorld::AddRigidBody(RigidBody& rb)
{
	dynamicWorld->addRigidBody(rb.GetBody());
}
void PhysicsWorld::RemoveRigidBody(RigidBody& rb)
{
	dynamicWorld->removeRigidBody(rb.GetBody());
}
