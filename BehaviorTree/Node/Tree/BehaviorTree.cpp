#include "BehaviorTree.h"

namespace BTree
{
	BehaviorTree::BehaviorTree() : blackboard(std::make_shared<Blackboard>()) {}
	BehaviorTree::BehaviorTree(std::shared_ptr<Blackboard> blackboard) : blackboard(blackboard) {}

	void BehaviorTree::SetRoot(std::shared_ptr<Node> root)
	{
		this->root = root;
	}

	std::shared_ptr<Blackboard> BehaviorTree::GetBlackboard()
	{
		return blackboard;
	}

	void BehaviorTree::Abort()
	{
		state = Node::EState::Idle;

		if (root)
		{
			root->Abort();
		}
	}

	Node::EState BehaviorTree::Run()
	{
		if (root)
		{
			return root->Tick();
		}

		return Node::EState::Success;
	}
}