#include <iostream>
#include <thread>
#include <chrono>
#include "Node/Tree/BehaviorTree.h"

#define KEY_SPACE 32

extern std::unique_ptr<BTree::BehaviorTree> CreateBehaviorTree1();
extern void SimulatePlayerInteraction1(std::shared_ptr<BTree::Blackboard> blackboard);

std::chrono::nanoseconds delta_time = std::chrono::nanoseconds(16666667); // 16.666667 ms

int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	std::unique_ptr<BTree::BehaviorTree> behavior_tree;
	behavior_tree = CreateBehaviorTree1();

	std::shared_ptr<BTree::Blackboard> blackboard = behavior_tree->GetBlackboard();

	while (true)
	{
		auto time = std::chrono::high_resolution_clock::now();

		// simulate player interaction
		SimulatePlayerInteraction1(blackboard);

		behavior_tree->Tick();

		std::this_thread::sleep_for(delta_time - (std::chrono::high_resolution_clock::now() - time));
	}

	return 0;
}