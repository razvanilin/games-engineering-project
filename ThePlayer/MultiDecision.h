#pragma once

#include <list>
#include "DecisionTreeNode.h"

namespace GameEngine
{
	template <typename T>
	class MultiDecision : public DecisionTreeNode<T>
	{
	protected:
		// A list of child nodes. This is lie a standard decision, but with more than two paths
		std::list<DecisionTreeNode<T>*> _childNodes;
		// Like Decision, we alsi need a getBranch method
		virtual DecisionTreeNode<T>* getBranch(T* owner) = 0;
	public:
		// Creates a new MultiDecision node
		MultiDecision(const std::list<DecisionTreeNode<T>*>& childNodes)
			: _childNodes(childNodes)
		{
		}
		// Destructor is still virtual
		virtual ~MultiDecision() { }
		// akes a decision. Calls getBranch to determine what to do
		void makeDecision(T* owner) { getBranch(owner)->makeDecision(owner); }
	};
}