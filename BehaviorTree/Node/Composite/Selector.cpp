#include "Selector.h"

namespace BTree
{
	void Selector::Enter()
	{
		iterator = children.begin();
	}

	Node::EState Selector::Run()
	{
		while (iterator != children.end())
		{
			Node::EState state = (*iterator)->Tick();
			if (state != Node::EState::Failure)
			{
				return state;
			}

			iterator++;
		}

		return Node::EState::Failure;
	}
}