#pragma once

#include <memory>
#include "../Node.h"
#include "../../Blackboard/Blackboard.h"

namespace BTree
{
	class BehaviorTree : public Node
	{
	public:
		BehaviorTree();
		BehaviorTree(std::shared_ptr<Blackboard> blackboard); // create tree with an existing blackboard

		void SetRoot(std::shared_ptr<Node> root);
		std::shared_ptr<Blackboard> GetBlackboard();

		void Abort() override;

	protected:
		EState Run() override;

	private:
		std::shared_ptr<Node> root;
		std::shared_ptr<Blackboard> blackboard;
	};
}