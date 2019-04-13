#include "Loop.h"

namespace BTree
{
	void Loop::Enter()
	{
		count = 0;
	}

	Node::EState Loop::Run()
	{
		child->Tick();

		if (times > 0 && ++count >= times)
		{
			return Node::EState::Success;
		}

		return Node::EState::Running;
	}
}