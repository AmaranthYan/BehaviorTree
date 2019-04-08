#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "Blackboard/Blackboard.h"
#include "Node/Node.h"

namespace BTree
{

	class Composite : public Node
	{
	public:
		void SetChild(std::shared_ptr<Node> child)
		{
			this->children.push_back(child);
		}

	protected:
		std::vector<std::shared_ptr<Node>> children;
		std::vector<std::shared_ptr<Node>>::iterator current;
	};

	class Decorator : public Node
	{
	public:
		void SetChild(std::shared_ptr<Node> child)
		{
			this->child = child;
		}

	protected:
		std::shared_ptr<Node> child;		
	};

	class Action : public Node
	{
	public:
		Action() : blackboard() {}
		Action(std::shared_ptr<Blackboard> blackboard) : blackboard(blackboard) {}

	protected:
		std::weak_ptr<Blackboard> blackboard;
	};

	class Sequence : public Composite
	{
	public:
		void Enter() override
		{
			current = children.begin();
		}

		EState Run() override
		{
			while (current != children.end())
			{
				EState state = (*current)->Tick();
				if (state != EState::Success)
				{
					return state;
				}

				current++;
			}

			return EState::Success;
		}
	};

	class Selector : public Composite
	{
	public:
		void Enter() override
		{
			current = children.begin();
		}

		EState Run() override
		{
			while (current != children.end())
			{
				EState state = (*current)->Tick();
				if (state != EState::Failure)
				{
					return state;
				}

				current++;
			}

			return EState::Failure;
		}
	};

	class Parallel : public Composite
	{
	public:
		Parallel(bool abort_on_fail) : abort_on_fail(abort_on_fail) {}

		EState Run() override
		{
			int success_count = 0;
			bool has_failed = false;

			current = children.begin();
			while (current != children.end())
			{
				EState state = (*current)->Tick();

				if (state == EState::Success)
				{
					success_count++;
				}
				else if (state == EState::Failure)
				{
					has_failed = true;
					if (abort_on_fail)
					{
						break;
					}					
				}

				current++;
			}

			if (has_failed)
			{
				return EState::Failure;
			}
			else if (success_count == children.size())
			{
				return EState::Success;
			}

			return EState::Running;
		}

	private:
		bool abort_on_fail;
	};

	class Loop : public Decorator
	{
	public:
		Loop(int times = 0) : times(times) {}

		void Enter() override
		{
			count = 0;
		}

		EState Run() override
		{
			child->Tick();
			
			if (times > 0 && ++count >= times)
			{
				return EState::Success;				
			}

			return EState::Running;
		}

	private:
		int times;
		int count;
	};

	class UntilSuccess : public Decorator
	{
	public:
		EState Run() override
		{
			EState state = child->Tick();

			if (state == EState::Success)
			{
				return EState::Success;
			}

			return EState::Running;
		}
	};

	template <typename T>
	class BlackboardCondition : public Decorator
	{
	public:
		BlackboardCondition(std::shared_ptr<Blackboard> blackboard, const std::string& key, bool is_set)
			: observer(std::make_unique<Observer<T>>(blackboard, key)), set_condition(is_set) {}

		EState Run() override
		{
			if (observer->IsSet() == set_condition)
			{
				return child->Tick();
			}
			return EState::Failure;
		}

	private:
		std::unique_ptr<Observer<T>> observer;
		bool set_condition;
	};

	template <typename T>
	class BlackboardComparator : public Decorator
	{
	public:
		BlackboardComparator(std::shared_ptr<Blackboard> blackboard, const std::string& key_a, const std::string& key_b, bool is_equal)
			: observer_a(std::make_unique<Observer<T>>(blackboard, key_a)), observer_b(std::make_unique<Observer<T>>(blackboard, key_b)), compared_value(), equal_condition(is_equal), compare_key(true) {}

		BlackboardComparator(std::shared_ptr<Blackboard> blackboard, const std::string& key, const T& value, bool is_equal)
			: observer_a(std::make_unique<Observer<T>>(blackboard, key)), observer_b(), compared_value(value), equal_condition(is_equal), compare_key(false) {}
		
		EState Run() override
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
			return EState::Failure;
		}

	private:
		std::unique_ptr<Observer<T>> observer_a;
		std::unique_ptr<Observer<T>> observer_b;
		T compared_value;
		bool equal_condition;
		bool compare_key; // compare with Blackboard entry or with value
	};
}