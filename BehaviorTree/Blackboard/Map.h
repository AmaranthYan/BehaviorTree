#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Observer.h"

namespace BTree
{
	template <typename T>
	class Map
	{
	public:
		void Set(const std::string& key, T value)
		{
			map[key] = value;
			NotifyAll(key, true, value);
		}

		bool Get(const std::string& key, T& value)
		{
			if (Has(key))
			{
				value = map[key];
				return true;
			}
			return false;
		}

		bool Has(const std::string& key)
		{
			return map.find(key) != map.end();
		}

		void Remove(const std::string& key)
		{
			map.erase(key);
			NotifyAll(key, false, {});
		}

		void RegisterObserver(Observer<T>* observer)
		{
			observers.push_back(observer);
			if (Has(observer->GetKey()))
			{
				observer->Update(true, map[observer->GetKey()]);
			}
		}

		void UnregisterObserver(Observer<T>* observer)
		{
			auto it = std::find(observers.begin(), observers.end(), observer);
			if (it != observers.end())
			{
				observers.erase(it);
			}
		}

	private:
		std::unordered_map<std::string, T> map;
		std::vector<Observer<T>*> observers;

		void NotifyAll(const std::string& key, bool is_set, const T& value)
		{
			for (auto ob : observers)
			{
				if (ob->GetKey() == key)
				{
					ob->Update(is_set, value);
				}
			}
		}
	};
}