#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

template<typename T>
class Stack : public List<T>
{
	public:
		void push(T val)
		{
			this->insert(this->begin(), std::move(val));
		}
		void pop()
		{
			this->erase(this->begin());
		}
		T & top()
		{
			return this->begin()->data;
		}
		const T & top() const
		{
			return this->begin()->data;
		}

		/* Other member functions:
		 *
		 * `bool empty() const` is inherited from List<T>
		 */
};

#endif
