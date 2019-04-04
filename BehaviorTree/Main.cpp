#include "BT.h"
#include "Blackboard/Blackboard.h"

int main()
{
	std::shared_ptr<BTree::Blackboard> bb = std::make_shared<BTree::Blackboard>();

	BTree::BlackboardCondition<bool> bcb(bb, "t", false);

	return 0;
}