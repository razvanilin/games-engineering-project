#pragma once

//add bullet libs. Choose between debug libs and release libs.
#if defined(DEBUG) | defined(_DEBUG)
#pragma comment (lib, "BulletCollision_Debug")
#pragma comment (lib, "BulletDynamics_Debug")
#pragma comment (lib, "LinearMath_Debug")
#else
#pragma comment (lib, "BulletCollision")
#pragma comment (lib, "BulletDynamics")
#pragma comment (lib, "LinearMath")
#endif

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicscommon.h>
#include <list>
#include "Entity.h"

using namespace irr;
using namespace irr::core;


namespace GameEngine{
	class PhysicsEngine{
	private:
		//Pointer to Bullets World simulation
		static btDynamicsWorld* _world;
		//pointer to collision config
		static btDefaultCollisionConfiguration* _config;
		//pointer to collision dispatcher
		static btCollisionDispatcher* _dispatcher;
		//pointer to proad phase interface
		static btBroadphaseInterface* _broadphase;
		//pointer to constraint solver
		static btSequentialImpulseConstraintSolver* _solver;
		//list containing all rigid bodies in the world
		static std::list<btRigidBody*> _rigidBodies;
		//Private constructor
		PhysicsEngine(){ }
	public:
		//Initialises the PhysicsEngine
		static bool initialise();
		//updates the simulation
		static bool update(float deltaTime);
		//shutsdown the simulation
		static void shutdown();
		//creates and registers a new square rigidbody - assumes position is set
		static btRigidBody* createBoxRigidBody(Entity* entity, const vector3df& scale, float mass);
		//creates and registers a new sphere - assumes position already set
		static btRigidBody* createSphereRigidBody(Entity* entity, float radius, float mass);
		//removes a rigid body from simulation
		static bool removeRigidBody(btRigidBody* body);
	};
}