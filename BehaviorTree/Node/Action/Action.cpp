#include "Action.h"

namespace BTree
{
	void Action::SetBlackboard(std::shared_ptr<Blackboard> blackboard)
	{
		this->blackboard = blackboard;
	}

	void BTree::Action::Abort()
	{
		state = Node::EState::Idle;
	}
}
