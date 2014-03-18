#pragma once

#include <cstdlib> // Required for rand
#include "MultiDecision.h"

namespace GameEngine
{
	template <typename T>
	class RandomMultiDecision : public MultiDecision<T>
	{
	protected:
		// Get branch needs to be implemented now
		DecisionTreeNode<T>* getBranch(T* owner);
	public:
		// Constructor just calls constructor of Decision
		RandomMultiDecision(const std::list<DecisionTreeNode<T>*> childNodes)
			: MultiDecision<T>(childNodes)
		{
			}
		// Destructor needs no body
		~RandomMultiDecision() { }
	};

	// Get branch just uses rand to determine which branch t pick
	template <typename T>
	DecisionTreeNode<T>* RandomMultiDecision<T>::getBranch(T* owner)
	{
		// Use choice operator to determine decision to make
		int choice = rand() % _childNodes.size();
		return _childNodes[choice];
	}
}