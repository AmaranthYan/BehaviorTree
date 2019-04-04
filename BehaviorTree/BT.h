#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

namespace BTree
{
	class Node
	{
	public:
		enum EState
		{
			Idle,
			Running,
			Success,
			Failure
		};

		virtual ~Node() {}

		EState Tick()
		{
			if (state != EState::Running)
			{
				Enter();
			}

			state = Run();

			if (state != EState::Running)
			{
				Exit();
			}

			return state;
		}

		virtual EState Run() = 0;

	protected:
		virtual void Enter() {}
		virtual void Exit() {}

	private:
		EState state;
	};

	class BehaviorTree : public Node
	{
	public:
		BehaviorTree() 
		{
			blackboard = std::make_shared<Blackboard>();
		}

		void SetRoot(std::shared_ptr<Node> root)
		{
			this->root = root;
		}

		std::shared_ptr<Blackboard> GetBlackboard()
		{
			return blackboard;
		}

		EState Run() override
		{
			if (root)
			{
				return root->Tick();
			}
			return EState::Success;
		}

	private:
		std::shared_ptr<Node> root;
		std::shared_ptr<Blackboard> blackboard;
	};

	class Composite : public Node
	{
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

	template <typename T>
	class BlackboardCondition : public Decorator
	{
	public:
		BlackboardCondition(std::shared_ptr<Blackboard> blackboard, const std::string& key, bool is_set)
			: blackboard(blackboard), observer(std::make_shared<Observer<T>>(key)), set_condition(is_set)
		{
			blackboard->RegisterObserver(observer);
		}

		virtual ~BlackboardCondition()
		{
			if (!blackboard.expired())
			{
				blackboard.lock()->UnregisterObserver(observer);
			}
		}

		EState Run() override
		{
			if (observer->IsSet() == set_condition)
			{
				return child->Tick();
			}
			return EState::Failure;
		}

	private:
		std::weak_ptr<Blackboard> blackboard;
		std::shared_ptr<Observer<T>> observer;
		bool set_condition;
	};

	template <typename T>
	class BlackboardComparator : public Decorator
	{
	public:
		BlackboardComparator(std::shared_ptr<Blackboard> blackboard, const std::string& key_a, const std::string& key_b, bool is_equal)
			: blackboard(blackboard), observer_a(std::make_shared<Observer<T>>(key_a)), observer_b(std::make_shared<Observer<T>>(key_b)), compared_value(), equal_condition(is_equal), compare_key(true)
		{
			blackboard->RegisterObserver(observer_a);
			blackboard->RegisterObserver(observer_b);
		}

		BlackboardComparator(std::shared_ptr<Blackboard> blackboard, const std::string& key, const T& value, bool is_equal)
			: blackboard(blackboard), observer_a(std::make_shared<Observer<T>>(key)), observer_b(), compared_value(value), equal_condition(is_equal), compare_key(false)
		{
			blackboard->RegisterObserver(observer_a);
		}

		virtual ~BlackboardComparator()
		{
			if (!blackboard.expired())
			{
				auto ptr = blackboard.lock();
				ptr->UnregisterObserver(observer_a);
				if (compare_key)
				{
					ptr->UnregisterObserver(observer_b);
				}
			}
		}

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
		std::weak_ptr<Blackboard> blackboard;
		std::shared_ptr<Observer<T>> observer_a;
		std::shared_ptr<Observer<T>> observer_b;
		T compared_value;
		bool equal_condition;
		bool compare_key; // compare with Blackboard entry or with value
	};
}