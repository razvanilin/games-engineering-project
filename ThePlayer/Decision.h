/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "DecisionTreeNode.h"

namespace GameEngine 
{
	template <typename T>
	class Decision : public DecisionTreeNode<T>
	{
	protected:
		// Called when decision is true
		DecisionTreeNode<T>* _trueNode;
		// called when decision is false
		DecisionTreeNode<T>* _falseNode;
		// Gets the true or false branch, depending on decision made
		// This is also pure virtual, so this class is still abstract
		virtual DecisionTreeNode<T>* getBranch(T* owner) = 0;
	public:
		// Constructor. Sets true or false nodes
		Decision(DecisionTreeNode<T>* trueNode, DecisionTreeNode<T>* falseNode)
			: _trueNode(trueNode), _falseNode(falseNode)
		{
		}
		// Destructor is still virtual
		virtual ~Decision() { }
		// akes a decision. Calls getBranch to determine what to do
		void makeDecision(T* owner) { getBranch(owner)->makeDecision(owner); }
	};
}