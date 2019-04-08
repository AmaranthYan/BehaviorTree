#include <iostream>
#include "BT.h"
#include "Blackboard/Blackboard.h"
#include "Node/Tree/BehaviorTree.h"

class CountInt : public BTree::Action
{
public:
	std::string name;
	int times;

protected:
	static int i;

	EState Run() override
	{
		if (times > 0)
		{
			times--;
			i++;
			std::cout << name << " " << i << std::endl;
			return EState::Running;
		}

		return EState::Success;
	}
};

int CountInt::i = 0;

int main()
{
	std::shared_ptr<BTree::Blackboard> bb = std::make_shared<BTree::Blackboard>();

	BTree::BlackboardCondition<bool> bcb(bb, "t", false);
	BTree::BlackboardComparator<bool> bcc(bb, "t", true, false);

	
	BTree::BehaviorTree bt;

	auto paral = std::make_shared<BTree::Parallel>(true);
	bt.SetRoot(paral);


	auto c_a = std::make_shared<CountInt>();
	c_a->name = "A";
	c_a->times = 5;
	auto c_b = std::make_shared<CountInt>();
	c_b->name = "B";
	c_b->times = 10;

	paral->SetChild(c_a);
	paral->SetChild(c_b);

	while (bt.Tick() != BTree::Node::EState::Success)
	{

	}

	system("pause");
	return 0;
}