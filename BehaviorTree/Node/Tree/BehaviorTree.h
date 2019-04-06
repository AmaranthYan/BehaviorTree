#pragma once

#include <memory>
#include "../../Blackboard/Blackboard.h"
#include "../Node.h"

namespace BTree
{
	class BehaviorTree : public Node
	{
	public:
		BehaviorTree();

		void SetRoot(std::shared_ptr<Node> root);
		std::shared_ptr<Blackboard> GetBlackboard();

	protected:
		EState Run() override;

	private:
		std::shared_ptr<Node> root;
		std::shared_ptr<Blackboard> blackboard;
	};
}