#include "Node.h"

namespace BTree
{
	Node::EState Node::Tick()
	{
		if (state != Node::EState::Running)
		{
			Enter();
		}

		state = Run();

		if (state != Node::EState::Running)
		{
			Exit();
		}

		return state;
	}
}