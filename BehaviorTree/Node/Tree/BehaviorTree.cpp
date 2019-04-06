#include "BehaviorTree.h"

namespace BTree
{
	BehaviorTree::BehaviorTree() : blackboard(std::make_shared<Blackboard>()) {}

	void BehaviorTree::SetRoot(std::shared_ptr<Node> root)
	{
		this->root = root;
	}

	std::shared_ptr<Blackboard> BehaviorTree::GetBlackboard()
	{
		return blackboard;
	}

	Node::EState BehaviorTree::Run()
	{
		if (root)
		{
			return root->Tick();
		}

		return EState::Success;
	}
}