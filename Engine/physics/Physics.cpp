#include "stdafx.h"
#include "physics/Physics.h"
#include "Physics/RigidBody.h"


//btIDebugDrawクラス抜粋
class MyBtDebug: public btIDebugDraw {
	int debug = 0;
public:

	//デバッグ表示フラグ
	enum	DebugDrawModes {
		DBG_NoDebug = 0,
		DBG_DrawWireframe = 1,
		DBG_DrawAabb = 2,

	};

	//必須
	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	void setDebugMode(int debugMode) {
		debug = debugMode;
	}
	int	getDebugMode() const {
		return debug;
	}
};

void MyBtDebug::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color) {
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_WIREFRAME;

	ID3D11RasterizerState* rsState;
	HRESULT hr = g_graphicsEngine->GetD3DDevice()->CreateRasterizerState(&desc, &rsState);

	D3D11_BUFFER_DESC bufDesc{};
	bufDesc.ByteWidth = sizeof(btVector3) * 2;
	bufDesc.CPUAccessFlags = 0;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	btVector3 data[]{ from,to };
	D3D11_SUBRESOURCE_DATA sub{};
	sub.pSysMem = data;

	ID3D11Buffer* vBuf;
	hr = g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufDesc, &sub ,&vBuf);


}

////インターフェイスの指定
//btDiscreteDynamicsWorld::setDebugDrawer(btIDebugDraw*	debugDrawer);
//
////描画の実行
////drawLineなどが実行される
//btDiscreteDynamicsWorld::debugDrawWorld();

PhysicsWorld g_physics;

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

	dynamicWorld = nullptr;
	constraintSolver = nullptr;
	overlappingPairCache = nullptr;
	collisionDispatcher = nullptr;
	collisionConfig = nullptr;
}
void PhysicsWorld::Init()
{
	Release();
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
}
void PhysicsWorld::Update()
{
	dynamicWorld->stepSimulation(1.0f/60.0f);
}
void PhysicsWorld::AddRigidBody(RigidBody& rb)
{
	dynamicWorld->addRigidBody(rb.GetBody());
}
void PhysicsWorld::RemoveRigidBody(RigidBody& rb)
{
	dynamicWorld->removeRigidBody(rb.GetBody());
}
