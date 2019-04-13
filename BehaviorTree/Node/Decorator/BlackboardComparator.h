#pragma once

#include "Decorator.h"
#include "../../Blackboard/Blackboard.h"

namespace BTree
{
	template <typename T>
	class BlackboardComparator : public Decorator
	{
	public:
		BlackboardComparator(std::shared_ptr<Blackboard> blackboard, const std::string& key_a, const std::string& key_b, bool is_equal)
			: observer_a(std::make_unique<Observer<T>>(blackboard, key_a)), observer_b(std::make_unique<Observer<T>>(blackboard, key_b)), compared_value(), equal_condition(is_equal), compare_key(true) {}

		BlackboardComparator(std::shared_ptr<Blackboard> blackboard, const std::string& key, const T& value, bool is_equal)
			: observer_a(std::make_unique<Observer<T>>(blackboard, key)), observer_b(), compared_value(value), equal_condition(is_equal), compare_key(false) {}

	protected:
		Node::EState Run() override
		{
			bool is_equal = observer_a->IsSet();

			if (compare_key)
			{
				is_equal &= observer_b->IsSet() && observer_a->GetValue() == observer_b->GetValue();
			}
			else
			{
				is_equal &= observer_a->GetValue() == compared_value;
			}

			if (is_equal == equal_condition)
			{
				return child->Tick();
			}

			return Node::EState::Failure;
		}

	private:
		std::unique_ptr<Observer<T>> observer_a;
		std::unique_ptr<Observer<T>> observer_b;
		T compared_value;
		bool equal_condition;
		bool compare_key; // compare with Blackboard entry or with value
	};
}