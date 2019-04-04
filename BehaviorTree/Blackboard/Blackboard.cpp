#include "Blackboard.h"

namespace BTree
{
	Map<int>& Blackboard::GetIntData()
	{
		return int_map;
	}

	void Blackboard::RegisterObserver(std::shared_ptr<Observer<int>> observer)
	{
		int_map.RegisterObserver(observer);
	}

	void Blackboard::UnregisterObserver(std::shared_ptr<Observer<int>> observer)
	{
		int_map.UnregisterObserver(observer);
	}

	Map<float>& Blackboard::GetFloatData()
	{
		return float_map;
	}

	void Blackboard::RegisterObserver(std::shared_ptr<Observer<float>> observer)
	{
		float_map.RegisterObserver(observer);
	}

	void Blackboard::UnregisterObserver(std::shared_ptr<Observer<float>> observer)
	{
		float_map.UnregisterObserver(observer);
	}

	Map<bool>& Blackboard::GetBoolData()
	{
		return bool_map;
	}

	void Blackboard::RegisterObserver(std::shared_ptr<Observer<bool>> observer)
	{
		bool_map.RegisterObserver(observer);
	}

	void Blackboard::UnregisterObserver(std::shared_ptr<Observer<bool>> observer)
	{
		bool_map.UnregisterObserver(observer);
	}
}