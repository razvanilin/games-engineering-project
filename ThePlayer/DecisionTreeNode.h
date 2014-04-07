/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

namespace GameEngine
{
	template <typename T>
	class DecisionTreeNode
	{
	public:
		// Virtual destructor. This is a base class
		virtual ~DecisionTreeNode() { }
		// Makes a decision. Pure Virtual method
		virtual void makeDecision(T* owner) = 0;
	};
}