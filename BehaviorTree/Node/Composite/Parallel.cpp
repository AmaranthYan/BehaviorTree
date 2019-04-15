#include "Parallel.h"

namespace BTree
{
	Node::EState Parallel::Run()
	{
		int success_count = 0;
		bool has_failed = false;

		iterator = children.begin();
		while (iterator != children.end())
		{
			Node::EState state = (*iterator)->Tick();

			if (state == Node::EState::Success)
			{
				success_count++;
			}
			else if (state == Node::EState::Failure)
			{
				has_failed = true;
				if (stop_on_fail)
				{
					break;
				}
			}

			iterator++;
		}

		if (has_failed)
		{
			return Node::EState::Failure;
		}
		else if (success_count == children.size())
		{
			return Node::EState::Success;
		}

		return Node::EState::Running;
	}
}