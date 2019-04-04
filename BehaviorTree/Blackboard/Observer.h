#pragma once

#include <string>

namespace BTree
{
	template <typename T>
	class Observer
	{
	public:
		Observer() : observed_key(), observed_value(), is_set(false) {}
		Observer(const std::string& blackboard_key) : observed_key(blackboard_key), observed_value(), is_set(false) {}

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
		std::string observed_key;
		T observed_value;
		bool is_set;
	};
}