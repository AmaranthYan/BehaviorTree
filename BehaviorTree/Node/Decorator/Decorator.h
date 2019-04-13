#pragma once

#include <memory>
#include "../Node.h"

namespace BTree
{
	class Decorator : public Node
	{
	public:
		void SetChild(std::shared_ptr<Node> child);

	protected:
		std::shared_ptr<Node> child;
	};
}