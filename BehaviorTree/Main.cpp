#include "BT.h"
#include "Blackboard/Blackboard.h"
#include "Node/Tree/BehaviorTree.h"

int main()
{
	std::shared_ptr<BTree::Blackboard> bb = std::make_shared<BTree::Blackboard>();

	BTree::BlackboardCondition<bool> bcb(bb, "t", false);
	BTree::BlackboardComparator<bool> bcc(bb, "t", true, false);

	return 0;
}