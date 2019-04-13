#include "Sequence.h"

namespace BTree
{
	void Sequence::Enter()
	{
		iterator = children.begin();
	}
	
	Node::EState Sequence::Run()
	{
		while (iterator != children.end())
		{
			Node::EState state = (*iterator)->Tick();
			if (state != Node::EState::Success)
			{
				return state;
			}

			iterator++;
		}

		return Node::EState::Success;
	}
}