#include "UntilSuccess.h"

namespace BTree
{
	Node::EState UntilSuccess::Run()
	{
		Node::EState state = child->Tick();

		if (state == Node::EState::Success)
		{
			return Node::EState::Success;
		}

		return Node::EState::Running;
	}
}