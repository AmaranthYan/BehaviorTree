#include <iostream>
#include "Blackboard/Blackboard.h"
#include "Node/Tree/BehaviorTree.h"
#include "Node/Action/Action.h"
#include "Node/Composite/Parallel.h"
#include "Node/Decorator/BlackboardCondition.h"
#include "Node/Decorator/BlackboardComparator.h"
#include "Node/Decorator/Loop.h"

class CountInt : public BTree::Action
{
public:
	std::string name;
	int times;

	static int i;

protected:
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

class CountInt2 : public BTree::Action
{
public:
	std::string name;

protected:
	EState Run() override
	{
		CountInt::i++;
		std::cout << name << " " << CountInt::i << std::endl;
		return EState::Success;
	}
};

int CountInt::i = 0;

int main()
{
	std::shared_ptr<BTree::Blackboard> bb = std::make_shared<BTree::Blackboard>();

	BTree::BlackboardCondition<bool> bcb(bb, "t", false);
	BTree::BlackboardComparator<bool> bcc(bb, "t", true, false);

	//bcb.HaHa

	bb->Set<int>("10", 42);	
	
	BTree::BehaviorTree bt;

	auto paral = std::make_shared<BTree::Parallel>(true);
	bt.SetRoot(paral);


	auto c_a = std::make_shared<CountInt>();
	c_a->name = "A";
	c_a->times = 5;
	auto c_b = std::make_shared<CountInt2>();
	c_b->name = "B";

	auto c_c = std::make_shared<BTree::Loop>(500);
	c_c->SetChild(c_b);

	paral->SetChild(c_a);
	paral->SetChild(c_c);

	while (bt.Tick() != BTree::Node::EState::Success)
	{

	}

	system("pause");
	return 0;
}