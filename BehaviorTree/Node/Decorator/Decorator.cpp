#include "Decorator.h"

namespace BTree
{
	void Decorator::SetChild(std::shared_ptr<Node> child)
	{
		this->child = child;
	}
}