#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <functional>
#include <iostream>

template<typename T>
class Vector
{
	public:
		Vector() {}
		template<typename InputIterator>
			Vector(InputIterator begin, InputIterator end)
			{
				for(auto i = begin; i != end; ++i)
				{
					std::wcout << *i;
					push_back(*i);
				}
			}
		Vector(int n, const T &val = T())
		{
			resize(n, val);
		}
		Vector(const Vector &x)
		{
			resize(x.size_);
			if(x.data_ != nullptr)
				std::copy(x.data_, x.data_ + size_, data_);
		}
		Vector(Vector &&x)
		{
			data_ = x.data_;
			size_ = x.size_;
			capacity_ = x.capacity_;
			x.data_ = nullptr;
		}
		template<typename InputIterator>
			void read(InputIterator begin, InputIterator end)
			{
				clear();
				for(auto i = begin; i != end; ++i)
					push_back(*i);
			}
		template<typename InputIterator>
			void append(InputIterator begin, InputIterator end)
			{
				for(auto i = begin; i != end; ++i)
					push_back(*i);
			}
		Vector & operator = (const Vector &x)
		{
			resize(x.size());
			if(x.data_ != nullptr)
				std::copy(x.data_, x.data_ + size_, data_);
			return *this;
		}
		Vector & operator = (Vector &&x)
		{
			if(x.data_ == data_)
				return *this;
			delete[] data_;
			data_ = x.data_;
			size_ = x.size_;
			capacity_ = x.capacity_;
			x.data_ = nullptr;
			return *this;
		}
		T * data()
		{
			return data_;
		}
		const T * data() const
		{
			return data_;
		}
		int size() const
		{
			return size_;
		}
		T & back()
		{
			return data_[size_ - 1];
		}
		const T & back() const
		{
			return data_[size_ - 1];
		}
		const T & operator [] (int n) const
		{
			return data_[n];
		}
		T & operator [] (int n)
		{
			return data_[n];
		}
		// Reserve space
		void reserve(int n)
		{
			if(capacity_ >= n)
				return;
			auto previous = data_;
			// New twice the size to improve efficiency
			capacity_ = n << 1;
			data_ = new T[capacity_]();
			if(previous != nullptr)
				std::move(previous, previous + size_, data_);
			delete[] previous;
		}
		void resize(int n)
		{
			reserve(n);
			size_ = n;
		}
		void resize(int n, const T &val)
		{
			reserve(n);
			if(size_ < n)
				std::fill(data_ + size_, data_ + n, val);
			size_ = n;
		}
		void push_back(T val)
		{
			resize(size_ + 1);
			data_[size_ - 1] = std::move(val);
		}
		void insert(int index, T val)
		{
			resize(size_ + 1);
			for(int i = size_ - 2; i >= index; --i)
				data_[i + 1] = data_[i];
			data_[index] = std::move(val);
		}
		int find(const T &val, int pos = 0) const
		{
			for(int i = pos; i < size_; ++i)
				if(data_[i] == val)
					return i;
			return -1;
		}
		int find(std::function<bool(const T &val)> predicate, int pos = 0) const
		{
			for(int i = pos; i < size_; ++i)
				if(predicate(data_[i]))
					return i;
			return -1;
		}
		int rfind(const T &val, int shift = 0) const
		{
			for(int i = size_ - shift - 1; i >= 0 && i < size_; --i)
				if(data_[i] == val)
					return i;
			return -1;
		}
		int rfind(std::function<bool(const T &val)> predicate, int shift = 0) const
		{
			for(int i = size_ - shift - 1; i >= 0 && i < size_; --i)
				if(predicate(data_[i]))
					return i;
			return -1;
		}
		void erase(int index)
		{
			for(int i = index; i + 1 < size_; ++i)
				data_[i] = data_[i + 1];
			resize(size_ - 1);
		}
		void erase(int begin, int end)
		{
			if(begin >= end)
				return;
			for(int i = begin; i + end - begin < size_; ++i)
				data_[i] = data_[i + end - begin];
			resize(size_ - (end - begin));
		}
		void clear()
		{
			size_ = 0;
		}
		~Vector()
		{
			delete[] data_;
		}

	protected:
		T *data_ = nullptr;
		int size_ = 0;
		int capacity_ = 0;
};

template<typename T>
bool operator == (const Vector<T> &lhs, const Vector<T> &rhs)
{
	if(lhs.size() != rhs.size())
		return false;
	for(int i = 0; i < lhs.size(); ++i)
		if(lhs[i] != rhs[i])
			return false;
	return true;
}

template<typename T>
bool operator != (const Vector<T> &lhs, const Vector<T> &rhs)
{
	return !(lhs == rhs);
}

#endif
