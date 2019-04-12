#pragma once

#include "Map.h"
#include "Observer.h"

namespace BTree
{
	class Blackboard
	{
	public:
		template<typename T>
		void Set(const std::string& key, T value);

		template<typename T>
		bool Get(const std::string& key, T& value);

		template<typename T>
		bool Has(const std::string& key);

		template<typename T>
		void Remove(const std::string& key);

		template<typename T>
		void RegisterObserver(Observer<T>* observer);

		template<typename T>
		void UnregisterObserver(Observer<T>* observer);

	private:
		Map<int> int_map;
		Map<float> float_map;
		Map<bool> bool_map;
	};
}