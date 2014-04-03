#include "PhysicsEngine.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <set>
#include "MessageHandler.h"

namespace GameEngine{
	//Initialise static attributes to null{0}
	btDynamicsWorld* PhysicsEngine::_world = 0;
	btDefaultCollisionConfiguration* PhysicsEngine::_config = 0;
	btCollisionDispatcher* PhysicsEngine::_dispatcher = 0;
	btBroadphaseInterface* PhysicsEngine::_broadphase = 0;
	btSequentialImpulseConstraintSolver* PhysicsEngine::_solver = 0;
	std::list<btRigidBody*> PhysicsEngine::_rigidBodies = std::list<btRigidBody*>();

	std::unordered_map<Entity*, std::set<Entity*>> contacts;

	bool HandleContacts(btManifoldPoint& point, btCollisionObject* body0, btCollisionObject* body1){
		//Get the 2 entities involved by accessing the user pointer of the bodies in contact
		Entity* entity0 = (Entity*)body0->getUserPointer();
		Entity* entity1 = (Entity*)body1->getUserPointer();

		// check if entity0 is already in map
		auto found = contacts.find(entity0);
		if(found != contacts.end()){
			//Entity in map. Add entity2 to the set mapped to it
			//Sets don't allow duplicates, so value won't be added if it already exists
			found->second.insert(entity1);
		}else{
			//entity1 not in map. Create new set and add entity1
			std::set<Entity*> set;
			set.insert(entity1);
			//add entity0 mapped to the new set in the contacts map
			contacts[entity0] = set;
		}
		return true;
	}

	bool PhysicsEngine::initialise(){
		_config = new btDefaultCollisionConfiguration();
		_dispatcher = new btCollisionDispatcher(_config);
		_broadphase = new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000));
		_solver = new btSequentialImpulseConstraintSolver();
		_world = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _config);

		//set the collision processed callback
		gContactProcessedCallback = (ContactProcessedCallback)HandleContacts;
		
		//could check everything's ok but just return true for now
		return true;
	}

	bool PhysicsEngine::update(float deltaTime){
		_world->stepSimulation(deltaTime, 60);

		//iterate across the contacts map
		for(auto contactsIter = contacts.begin(); contactsIter!=contacts.end(); ++contactsIter){
			//get the entity key from  teh current entry in the map
			Entity* collider0 = contactsIter->first;
			//get the set of colliders from the current entry in the map
			std::set<Entity*>& set = contactsIter->second;
			//iterate thru all the entities in the set
			for(auto entityIter = set.begin(); entityIter!=set.end(); ++entityIter){
				// get the other colider from the iterator
				Entity* collider1 = *entityIter;
				//create 2 messages - one for collider and one for the entity being hit
				Message msg1(collider0, "COLLISION", collider1);
				Message msg2(collider1, "COLLISION", collider0);
				//dispatch teh messages
				MessageHandler::sendMessage(msg1);
				MessageHandler::sendMessage(msg2);
			}
		}
		//empty the contacts map ready for next time
		contacts.clear();

		//for now
		return true;
	}

	void PhysicsEngine::shutdown(){
		//remove all  rigid bodies
		for(auto iter = _rigidBodies.begin(); iter != _rigidBodies.end(); ++iter){
			//remove from world simulation
			_world->removeRigidBody(*iter);
			//delete from memory
			delete *iter;
			//set pointer to null{0}
			*iter = 0;
		}
		//now empty the list
		_rigidBodies.clear();

		//start deleting the physics components
		delete _world;
		_world = 0;
		delete _solver;
		_solver = 0;
		delete _dispatcher;
		_dispatcher = 0;
		delete _broadphase;
		_broadphase = 0;
		delete _config;
		_config = 0;
		//Physics now shutdown
	}
	

	//creates and registers a new square rigidbody - assumes position is set
	btRigidBody* PhysicsEngine::createBoxRigidBody(Entity* entity, const vector3df& scale, float mass){
		//create rigidbody's transform using entity's position
		btTransform transform;
		transform.setIdentity();
		vector3df pos = entity->getNode()->getPosition();
		transform.setOrigin(btVector3(pos.X, pos.Y, pos.Z));

		//create the motionState of the object
		btDefaultMotionState* motionState = new btDefaultMotionState(transform);

		//create the bounding volume
		btVector3 halfExtents(scale.X*0.5f, scale.Y*0.5f, scale.Z*0.5f);
		btCollisionShape* shape = new btBoxShape(halfExtents);

		//create intertia info for the shape
		btVector3 localinertia;
		shape->calculateLocalInertia(mass, localinertia);

		//now create the rigidBody
		btRigidBody* rigidBody = new btRigidBody(mass, motionState, shape, localinertia);

		//add a pointer to rigidBody pointing to associated Entity
		rigidBody->setUserPointer(entity);

		//add the rigidBody to the world
		_world->addRigidBody(rigidBody);

		//and add to the list of rigidBodies
		_rigidBodies.push_back(rigidBody);

		//finally return created body
		return rigidBody;
	}

	//creates and registers a new sphere - assumes position already set
	btRigidBody* PhysicsEngine::createSphereRigidBody(Entity* entity, float radius, float mass){
		//create rigidbody's transform using entity's position
		btTransform transform;
		transform.setIdentity();
		vector3df pos = entity->getNode()->getPosition();
		transform.setOrigin(btVector3(pos.X, pos.Y, pos.Z));

		//create the motionState of the object
		btDefaultMotionState* motionState = new btDefaultMotionState(transform);

		//create the bounding volume
		btCollisionShape* shape = new btSphereShape(radius);

		//create intertia info for the shape
		btVector3 localinertia;
		shape->calculateLocalInertia(mass, localinertia);

		//now create the rigidBody
		btRigidBody* rigidBody = new btRigidBody(mass, motionState, shape, localinertia);

		//add a pointer to rigidBody pointing to associated Entity
		rigidBody->setUserPointer(entity);

		//add the rigidBody to the world
		_world->addRigidBody(rigidBody);

		//and add to the list of rigidBodies
		_rigidBodies.push_back(rigidBody);

		//finally return created body
		return rigidBody;
	}

	bool PhysicsEngine::removeRigidBody(btRigidBody* body){
		_rigidBodies.remove(body);
		_world->removeRigidBody(body);

		return true;
	}

}