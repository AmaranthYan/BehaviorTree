#pragma once

#include <memory>
#include "../Node.h"
#include "../../Blackboard/Blackboard.h"

namespace BTree
{
	class Action : public Node
	{
	public:
		Action() : blackboard() {}
		Action(std::shared_ptr<Blackboard> blackboard) : blackboard(blackboard) {}

		void Abort() override;

	protected:
		std::weak_ptr<Blackboard> blackboard;
	};
}