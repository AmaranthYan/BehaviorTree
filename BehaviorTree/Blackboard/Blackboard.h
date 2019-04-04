#pragma once

#include <memory>
#include "Map.h"
#include "Observer.h"

namespace BTree
{
	class Blackboard
	{
	public:
		Map<int>& GetIntData();
		void RegisterObserver(std::shared_ptr<Observer<int>> observer);
		void UnregisterObserver(std::shared_ptr<Observer<int>> observer);

		Map<float>& GetFloatData();
		void RegisterObserver(std::shared_ptr<Observer<float>> observer);
		void UnregisterObserver(std::shared_ptr<Observer<float>> observer);

		Map<bool>& GetBoolData();
		void RegisterObserver(std::shared_ptr<Observer<bool>> observer);
		void UnregisterObserver(std::shared_ptr<Observer<bool>> observer);

	private:
		Map<int> int_map;
		Map<float> float_map;
		Map<bool> bool_map;
	};
}