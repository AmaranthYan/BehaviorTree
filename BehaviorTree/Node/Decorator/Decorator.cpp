#include "Decorator.h"

namespace BTree
{
	void Decorator::SetChild(std::shared_ptr<Node> child)
	{
		this->child = child;
	}

	void Decorator::Abort()
	{
		state = Node::EState::Idle;

		if (child)
		{
			child->Abort();
		}
	}
}