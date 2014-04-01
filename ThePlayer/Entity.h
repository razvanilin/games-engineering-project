#pragma once

#include <irrlicht.h>
#include "Message.h"

namespace GameEngine{
	class Entity{
	protected:
		int _id;
		std::string _name;
		irr::scene::IMeshSceneNode* _node;
		bool _alive;
	public:
		Entity(int id, irr::scene::IMeshSceneNode* node, const std::string& name = "");
		virtual ~Entity(){ }
<<<<<<< HEAD
		irr::scene::IMeshSceneNode* getNode(){ return _node; }
		void setNode(irr::scene::IMeshSceneNode* value) { _node = value; }
=======
		irr::scene::ISceneNode* getNode(){ return _node; }
		void setNode(irr::scene::ISceneNode* value) { _node = value; }
>>>>>>> DaveDev
		bool isAlive() const {return _alive;}
		void setAlive(bool value){ _alive = value; }
		std::string getName() const {return _name;}
		void setName(const std::string& val){_name = val;}
		int getID() const {return _id;}
		void setID(int val){_id = val;} 
		virtual void initialise() = 0;
		virtual void loadContent() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void unloadContent() = 0;
		virtual void handleMessage(const GameEngine::Message& message){ }
	};

}