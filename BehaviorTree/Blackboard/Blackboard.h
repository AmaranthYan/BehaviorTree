#pragma once

#include "Map.h"
#include "Observer.h"

namespace BTree
{
	class Blackboard
	{
	public:
		Map<int>& GetIntData();
		void RegisterObserver(Observer<int>* observer);
		void UnregisterObserver(Observer<int>* observer);

		Map<float>& GetFloatData();
		void RegisterObserver(Observer<float>* observer);
		void UnregisterObserver(Observer<float>* observer);

		Map<bool>& GetBoolData();
		void RegisterObserver(Observer<bool>* observer);
		void UnregisterObserver(Observer<bool>* observer);

	private:
		Map<int> int_map;
		Map<float> float_map;
		Map<bool> bool_map;
	};
}