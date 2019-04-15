#include "Composite.h"

namespace BTree
{
	void Composite::SetChild(std::shared_ptr<Node> child)
	{
		this->children.push_back(child);
	}

	void Composite::Abort()
	{
		state = Node::EState::Idle;

		for (auto child : children)
		{
			child->Abort();
		}
	}
}