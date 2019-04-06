#include "Node.h"

namespace BTree
{
	Node::EState Node::Tick()
	{
		if (state != EState::Running)
		{
			Enter();
		}

		state = Run();

		if (state != EState::Running)
		{
			Exit();
		}

		return state;
	}
}