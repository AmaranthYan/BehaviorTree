#include <iostream>
#include <conio.h>
#include "../Node/Tree/BehaviorTree.h"
#include "../Node/Action/Action.h"
#include "../Node/Composite/Selector.h"
#include "../Node/Composite/Sequence.h"
#include "../Node/Decorator/BlackboardCondition.h"

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

// agent object with speed 20 per sec at position 0 
static Agent agent(0, 20);
std::unique_ptr<BTree::BehaviorTree> CreateBehaviorTree1()
{
	auto behavior_tree = std::make_unique<BTree::BehaviorTree>();
	auto blackboard = behavior_tree->GetBlackboard();

	auto selector = std::make_shared<BTree::Selector>();
	behavior_tree->SetRoot(selector);

	auto blackboard_condition = std::make_shared<BTree::BlackboardCondition<bool>>(blackboard, "interrupt", false);
	blackboard_condition->SetAbortMode(true);
	auto stay_idle = std::make_shared<StayIdle>(&agent);

	selector->SetChild(blackboard_condition);
	selector->SetChild(stay_idle);

	auto sequence = std::make_shared<BTree::Sequence>();
	blackboard_condition->SetChild(sequence);

	auto find_random_dest = std::make_shared<FindRandomDestination>(&agent, 50.f);
	find_random_dest->SetBlackboard(blackboard);
	auto move_to = std::make_shared<MoveTo>(&agent);
	move_to->SetBlackboard(blackboard);

	sequence->SetChild(find_random_dest);
	sequence->SetChild(move_to);

	return behavior_tree;
}

void SimulatePlayerInteraction1(std::shared_ptr<BTree::Blackboard> blackboard)
{
	if (_kbhit())
	{
		if (_getch() == KEY_SPACE)
		{
			if (blackboard->Has<bool>("interrupt"))
			{
				blackboard->Remove<bool>("interrupt");
			}
			else
			{
				blackboard->Set<bool>("interrupt", true);
			}
		}
	}
}