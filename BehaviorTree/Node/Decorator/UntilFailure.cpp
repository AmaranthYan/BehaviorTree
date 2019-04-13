#include "UntilFailure.h"

namespace BTree
{
	Node::EState UntilFailure::Run()
	{
		Node::EState state = child->Tick();

		if (state == Node::EState::Failure)
		{
			return Node::EState::Failure;
		}

		return Node::EState::Running;
	}
}