#pragma once

#include <memory>
#include <string>
#include "Blackboard.h"

namespace BTree
{	
	template <typename T>
	class Observer
	{
	public:
		Observer() : blackboard(), observed_key(), observed_value(), is_set(false) {}
		Observer(std::shared_ptr<Blackboard> blackboard, const std::string& blackboard_key)
			: blackboard(blackboard), observed_key(blackboard_key), observed_value(), is_set(false)
		{
			blackboard->RegisterObserver(this);
		}

		~Observer()
		{
			if (!blackboard.expired())
			{
				blackboard.lock()->UnregisterObserver(this);
			}
		}

		const std::string& GetKey()
		{
			return observed_key;
		}

		const T& GetValue()
		{
			return observed_value;
		}

		bool IsSet()
		{
			return is_set;
		}

		void Update(bool is_set, const T& value)
		{
			this->is_set = is_set;
			this->observed_value = value;
		}

	private:
		std::weak_ptr<Blackboard> blackboard;
		std::string observed_key;
		T observed_value;
		bool is_set;
	};
}