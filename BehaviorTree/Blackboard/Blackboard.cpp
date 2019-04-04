#include "Blackboard.h"

namespace BTree
{
	Map<int>& Blackboard::GetIntData()
	{
		return int_map;
	}

	void Blackboard::RegisterObserver(Observer<int>* observer)
	{
		int_map.RegisterObserver(observer);
	}

	void Blackboard::UnregisterObserver(Observer<int>* observer)
	{
		int_map.UnregisterObserver(observer);
	}

	Map<float>& Blackboard::GetFloatData()
	{
		return float_map;
	}

	void Blackboard::RegisterObserver(Observer<float>* observer)
	{
		float_map.RegisterObserver(observer);
	}

	void Blackboard::UnregisterObserver(Observer<float>* observer)
	{
		float_map.UnregisterObserver(observer);
	}

	Map<bool>& Blackboard::GetBoolData()
	{
		return bool_map;
	}

	void Blackboard::RegisterObserver(Observer<bool>* observer)
	{
		bool_map.RegisterObserver(observer);
	}

	void Blackboard::UnregisterObserver(Observer<bool>* observer)
	{
		bool_map.UnregisterObserver(observer);
	}
}