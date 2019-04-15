#pragma once

#include <memory>
#include <vector>
#include "../Node.h"

namespace BTree
{
	class Composite : public Node
	{
	public:
		void SetChild(std::shared_ptr<Node> child);

		void Abort() override;

	protected:
		std::vector<std::shared_ptr<Node>> children;
		std::vector<std::shared_ptr<Node>>::iterator iterator;
	};
}