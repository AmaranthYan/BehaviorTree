#pragma once

#include "Decorator.h"
#include "../../Blackboard/Blackboard.h"
#include "../../Blackboard/Observer.h"

namespace BTree
{
	template <typename T>
	class BlackboardCondition : public Decorator
	{
	public:
		BlackboardCondition(std::shared_ptr<Blackboard> blackboard, const std::string& key, bool is_set)
			: observer(std::make_unique<Observer<T>>(blackboard, key)), set_condition(is_set), abort_child(false) {}

		void SetAbortMode(bool abort)
		{
			this->abort_child = abort;
		}

	protected:
		Node::EState Run() override
		{
			if (observer->IsSet() == set_condition)
			{
				return child->Tick();
			}
			else
			{
				if (abort_child)
				{
					child->Abort();
				}

				return Node::EState::Failure;
			}
		}

	private:
		std::unique_ptr<Observer<T>> observer;
		bool set_condition;
		bool abort_child;
	};
}