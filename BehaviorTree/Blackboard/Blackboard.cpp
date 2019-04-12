#include "Blackboard.h"

namespace BTree
{
	// int
	template<>
	void Blackboard::Set<int>(const std::string& key, int value)
	{
		int_map.Set(key, value);
	}

	template<>
	bool Blackboard::Get(const std::string& key, int& value)
	{
		return int_map.Get(key, value);
	}

	template<>
	bool Blackboard::Has<int>(const std::string& key)
	{
		return int_map.Has(key);
	}

	template<>
	void Blackboard::Remove<int>(const std::string& key)
	{
		return int_map.Remove(key);
	}

	template<>
	void Blackboard::RegisterObserver(Observer<int>* observer)
	{
		int_map.RegisterObserver(observer);
	}

	template<>
	void Blackboard::UnregisterObserver(Observer<int>* observer)
	{
		int_map.UnregisterObserver(observer);
	}

	// float
	template<>
	void Blackboard::Set<float>(const std::string& key, float value)
	{
		float_map.Set(key, value);
	}

	template<>
	bool Blackboard::Get(const std::string& key, float& value)
	{
		return float_map.Get(key, value);
	}

	template<>
	bool Blackboard::Has<float>(const std::string& key)
	{
		return float_map.Has(key);
	}

	template<>
	void Blackboard::Remove<float>(const std::string& key)
	{
		return float_map.Remove(key);
	}

	template<>
	void Blackboard::RegisterObserver(Observer<float>* observer)
	{
		float_map.RegisterObserver(observer);
	}

	template<>
	void Blackboard::UnregisterObserver(Observer<float>* observer)
	{
		float_map.UnregisterObserver(observer);
	}

	// bool
	template<>
	void Blackboard::Set<bool>(const std::string& key, bool value)
	{
		bool_map.Set(key, value);
	}

	template<>
	bool Blackboard::Get(const std::string& key, bool& value)
	{
		return bool_map.Get(key, value);
	}

	template<>
	bool Blackboard::Has<bool>(const std::string& key)
	{
		return bool_map.Has(key);
	}

	template<>
	void Blackboard::Remove<bool>(const std::string& key)
	{
		return bool_map.Remove(key);
	}

	template<>
	void Blackboard::RegisterObserver(Observer<bool>* observer)
	{
		bool_map.RegisterObserver(observer);
	}

	template<>
	void Blackboard::UnregisterObserver(Observer<bool>* observer)
	{
		bool_map.UnregisterObserver(observer);
	}
}