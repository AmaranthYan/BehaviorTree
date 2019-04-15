#include "Action.h"

namespace BTree
{
	void BTree::Action::Abort()
	{
		state = Node::EState::Idle;
	}
}
