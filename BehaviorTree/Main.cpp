#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include "Blackboard/Blackboard.h"
#include "Node/Tree/BehaviorTree.h"
#include "Node/Action/Action.h"
#include "Node/Composite/Parallel.h"
#include "Node/Composite/Selector.h"
#include "Node/Composite/Sequence.h"
#include "Node/Decorator/BlackboardCondition.h"
#include "Node/Decorator/BlackboardComparator.h"
#include "Node/Decorator/Loop.h"

#define KEY_SPACE 32

// 1D agent
class Agent
{
public:
	Agent(float pos, float spd) : position(pos), speed(spd) {}

	float GetPosition()
	{
		return position;
	}

	bool MoveTo(float destination)
	{
		int sign = (destination > position) - (position > destination);
		if (sign)
		{
			position += sign * speed / 60.f;

			std::cout << "Agent is moving towards " << destination << ", currently at " << position << std::endl;
			// doesn't reach destination
			if ((destination - position) * sign > 0)
			{
				return false;
			}
		}

		position = destination;
		std::cout << "Agent arrived at " << destination << std::endl;
		return true;
	}

	void StayIdle()
	{
		std::cout << "Agent is staying idle" << std::endl;
	}

private:
	float position;
	float speed;
};

class FindRandomDestination : public BTree::Action
{
public:
	FindRandomDestination(Agent* agent, float range) : agent(agent), range(range) {}

protected:
	EState Run() override
	{
		float delta = ((static_cast<float>(rand()) / RAND_MAX) - 0.5f) * range;
		blackboard.lock()->Set<float>("destination", agent->GetPosition() + delta);
		return EState::Success;
	}

private:
	Agent* agent;
	float range;
};

class MoveTo : public BTree::Action
{
public:
	MoveTo(Agent* agent) : agent(agent) {}

protected:
	EState Run() override
	{
		float dest;
		if (blackboard.lock()->Get<float>("destination", dest))
		{
			return agent->MoveTo(dest) ? Node::EState::Success : Node::EState::Running;
		}
		else
		{
			return Node::EState::Failure;
		}
		return EState::Success;
	}

private:
	Agent* agent;
};

class StayIdle : public BTree::Action
{
public:
	StayIdle(Agent* agent) : agent(agent) {}

protected:
	EState Run() override
	{
		agent->StayIdle();
		return EState::Success;
	}

private:
	Agent* agent;
};

std::chrono::nanoseconds delta_time = std::chrono::nanoseconds(16666667); // 16.666667 ms

int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	Agent agent(0, 50);

	std::shared_ptr<BTree::Blackboard> bb = std::make_shared<BTree::Blackboard>();
	
	BTree::BehaviorTree bt(bb);

	//auto paral = std::make_shared<BTree::Parallel>(true);
	//bt.SetRoot(paral);

	auto selector = std::make_shared<BTree::Selector>();
	bt.SetRoot(selector);

	auto blackboard_condition = std::make_shared<BTree::BlackboardCondition<bool>>(bb, "interrupt", false);
	blackboard_condition->SetAbortMode(true);
	auto stay_idle = std::make_shared<StayIdle>(&agent);
	selector->SetChild(blackboard_condition);
	selector->SetChild(stay_idle);

	auto sequence = std::make_shared<BTree::Sequence>();
	blackboard_condition->SetChild(sequence);

	auto find_random_dest = std::make_shared<FindRandomDestination>(&agent, 50.f);
	find_random_dest->SetBlackboard(bb);
	auto move_to = std::make_shared<MoveTo>(&agent);
	move_to->SetBlackboard(bb);

	sequence->SetChild(find_random_dest);
	sequence->SetChild(move_to);

	while (true)
	{
		auto time = std::chrono::high_resolution_clock::now();

		// simulate player interaction
		if (_kbhit())
		{
  			if (_getch() == KEY_SPACE)
			{
				if (bb->Has<bool>("interrupt"))
				{
					bb->Remove<bool>("interrupt");
				}
				else
				{
					bb->Set<bool>("interrupt", true);
				}
			}
		}

		bt.Tick();
		std::this_thread::sleep_for(delta_time - (std::chrono::high_resolution_clock::now() - time));
	}

	return 0;
}