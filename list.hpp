#ifndef LIST_HPP
#define LIST_HPP

#include <functional>

template<typename T>
class List
{
	public:
		class Node
		{
			public:
				T data;
				Node *next = nullptr;
				Node *prev = nullptr;
		};

		List(): head_(new Node)
		{
			head_->next = head_;
			head_->prev = head_;
		}
		List(const List &x) : head_(new Node)
		{
			head_->next = head_;
			head_->prev = head_;
			insert(end(), x);
		}
		List(List &&x) : head_(new Node)
		{
			head_->next = head_;
			head_->prev = head_;
			insert(end(), std::move(x));
		}
		List & operator = (const List &x)
		{
			auto i = begin(), j = x.begin();
			for(; i != end() && j != x.end(); i = i->next, j = j->next)
				i->data = j->data;
			while(j != x.end())
			{
				insert(end(), j->data);
				j = j->next;
			}
			while(i != end())
			{
				i = erase(i);
			}
			return *this;
		}
		List & operator = (List &&x)
		{
			clear();
			insert(end(), std::move(x));
			return *this;
		}

		bool empty() const
		{
			return head_->next == head_;
		}

		Node * begin()
		{
			return head_->next;
		}
		const Node * begin() const
		{
			return head_->next;
		}
		Node * rbegin()
		{
			return head_->prev;
		}
		const Node * rbegin() const
		{
			return head_->prev;
		}

		Node * end()
		{
			return head_;
		}
		const Node * end() const
		{
			return head_;
		}
		Node * rend()
		{
			return head_;
		}
		const Node * rend() const
		{
			return head_;
		}

		const Node * search(const T &val) const
		{
			auto cur = head_->next;
			while(cur != head_)
			{
				if(cur->data == val)
					return cur;
				cur = cur->next;
			}
			return nullptr;
		}
		
		const Node * search(std::function<bool(const T &val)> pred) const
		{ 
			auto cur = head_->next;
			while(cur != head_)
			{
				if(pred(cur->data))
					return cur;
				cur = cur->next;
			}
			return nullptr;
		}

		Node * search(std::function<bool(const T &val)> pred)
		{ 
			auto cur = head_->next;
			while(cur != head_)
			{
				if(pred(cur->data))
					return cur;
				cur = cur->next;
			}
			return nullptr;
		}

		// Search from index
		Node * search(Node *pos, std::function<bool(const T &val)> pred)
		{ 
			auto cur = pos;
			while(cur != head_)
			{
				if(pred(cur->data))
					return cur;
				cur = cur->next;
			}
			return nullptr;
		}

		Node * search(const T &val)
		{
			auto cur = head_->next;
			while(cur != head_)
			{
				if(cur->data == val)
					return cur;
				cur = cur->next;
			}
			return nullptr;
		}

		Node * insert(Node *pos, T val)
		{
			if(pos == nullptr)
				pos = head_;
			auto node = new Node;
			node->data = std::move(val);
			return insert(pos, node);
		}

		Node * insert(Node *pos, Node *node)
		{
			if(pos == nullptr)
				pos = head_;
			node->next = pos;
			node->prev = pos->prev;
			pos->prev = node;
			node->prev->next = node;
			++size_;
			return node;
		}

		// Insert a whole list
		Node * insert(Node *pos, const List &l)
		{
			for(auto i = l.rbegin(); i != l.rend(); i = i->prev)
				pos = insert(pos, i->data);
			return pos;
		}
		Node * insert(Node *pos, List &&l)
		{
			for(auto i = l.rbegin(); i != l.rend();)
			{
				auto next = i->prev;
				pos = insert(pos, i);
				i = next;
			}
			l.head_->next = l.head_;
			l.head_->prev = l.head_;
			return pos;
		}

		Node * erase(Node *pos)
		{
			if(pos == nullptr)
				return pos;
			auto cur = pos->next;
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;
			--size_;
			delete pos;
			return cur;
		}

		int size() const
		{
			return size_;
		}
		void clear()
		{
			while(head_->next != head_)
				erase(head_->next);
		}

		~List()
		{
			clear();
			delete head_;
		}

	private:
		Node *head_;
		int size_ = 0;
};

#endif
