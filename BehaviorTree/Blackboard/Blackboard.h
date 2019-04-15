#pragma once

#include <string>
#include <memory>

namespace BTree
{
	template <typename T>
	class Map;

	template <typename T>
	class Observer;

	class Blackboard
	{
	public:
		Blackboard();
		~Blackboard(); // must have, in order to delete unique_ptr of forward declared type

		template <typename T>
		void Set(const std::string& key, T value);

		template <typename T>
		bool Get(const std::string& key, T& value);

		template <typename T>
		bool Has(const std::string& key);

		template <typename T>
		void Remove(const std::string& key);

		template <typename T>
		void RegisterObserver(Observer<T>* observer);

		template <typename T>
		void UnregisterObserver(Observer<T>* observer);

	private:
		std::unique_ptr<Map<int>> int_map;
		std::unique_ptr<Map<float>> float_map;
		std::unique_ptr<Map<bool>> bool_map;
	};
}