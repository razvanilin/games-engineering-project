#pragma once

#include <cstdlib> // Required for rand
#include "Decision.h"

namespace GameEngine
{
	template <typename T>
	class RandomDecision : public Decision<T>
	{
	protected:
		// Get branch needs to be implemented now
		DecisionTreeNode<T>* getBranch(T* owner);
	public:
		// Constructor just calls constructor of Decision
		RandomDecision(DecisionTreeNode<T>* trueNode, DecisionTreeNode<T>* falseNode)
			: Decision<T>(trueNode, falseNode)
		{
		}
		// Destructor needs no body
		~RandomDecision() { }
	};

	// Get branch just uses rand to determine which branch t pick
	template <typename T>
	DecisionTreeNode<T>* RandomDecision<T>::getBranch(T* owner)
	{
		// Use choice operator to determine decision to make
		DecisionTreeNode<T>* choice = rand() % 2 == 0 ? _trueNode : _falseNode;
		return choice;
	}
}