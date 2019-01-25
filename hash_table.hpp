#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "hash.hpp"
#include "list.hpp"
#include "vector.hpp"

template<typename T>
class HashTable
{
	public:
		HashTable() {}
		HashTable(int size) : table_(size) {}
		void resize(int size)
		{
			table_.resize(size);
		}
		bool count(const T &val) const
		{
			auto hash_val = Hash<T>(val);
			return count(val, hash_val);
		}
		bool count(const T &val, size_t hash_val) const
		{
			const auto &l = table_[hash_val % table_.size()];
			return l.search(val) != nullptr;
		}
		void insert(const T &val)
		{
			auto hash_val = Hash<T>(val);
			insert(val, hash_val);
		}
		void insert(const T &val, size_t hash_val)
		{
			if(!count(val, hash_val))
			{
				auto &l = table_[hash_val % table_.size()];
				l.insert(l.begin(), val);
			}
		}
		void erase(const T &val)
		{
			auto hash_val = Hash<T>(val);
			auto &l = table_[hash_val % table_.size()];
			auto pos = l.search(val);
			if(pos != nullptr)
				l.erase(pos);
		}

	private:
		Vector<List<T>> table_;
};

#endif
