/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

namespace GameEngine{
	template <typename T>
	class State{
	public :
		/*
		This class will act as a base class for all states. 
		The destructor must be virtual to allow the object to be cleaned up properly when deleted
		*/
		virtual ~State(){ }
		/*
		this method is calld whenever teh state is executed.
		Method is purely virtual (no implementation).
		hence Method = 0. This denotes an abstract class which cannot be implemented
		*/
		virtual void execute(T* owner, float deltaTime) = 0;
	};
}