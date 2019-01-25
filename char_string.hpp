#ifndef CHAR_STRING_HPP
#define CHAR_STRING_HPP

#include "vector.hpp"
#include <cwchar>
#include <algorithm>
#include <istream>
#include <ostream>

class CharString : public Vector<wchar_t>
{
	public:
		// Find the position of substr using KMP algorithm
		int indexOf(const CharString &substr, int pos = 0) const;
		int indexOf(const wchar_t *substr, int pos = 0) const;

		// Get a substring
		CharString substring(int start, int end) const;

		CharString() {}
		template<typename InputIterator>
			CharString(InputIterator begin, InputIterator end)
			: Vector<wchar_t>(begin, end) {}
		template<typename InputIterator>
			CharString(InputIterator begin, InputIterator end, std::wifstream &fin)
			: Vector<wchar_t>(begin, end, fin) {}
		CharString(CharString &&) = default;
		CharString(const CharString &) = default;
		CharString(const wchar_t *str) : Vector<wchar_t>(std::wcslen(str))
		{
			std::copy(str, str + std::wcslen(str), data_);
		}
		CharString & operator += (const CharString &val);
		CharString & operator = (const CharString &) = default;
		CharString & operator = (CharString &&) = default;
		// Convert to C-style string
		const wchar_t * c_str() const
		{
			return data_;
		}
		// Resize one byte more to support c_str()
		void resize(int n, wchar_t v = '\0')
		{
			auto parent = static_cast<Vector<wchar_t> *>(this);
			parent->reserve(n + 1);
			parent->resize(n, v);
			data_[n] = '\0';
		}
};

inline std::wostream & operator << (std::wostream &os, const CharString &str)
{
	for(int i = 0; i < str.size(); ++i)
		os << str[i];
	return os;
}

inline bool operator == (const CharString &lhs, const CharString &rhs)
{
	return static_cast<const Vector<wchar_t> &>(lhs) == static_cast<const Vector<wchar_t> &>(rhs);
}
inline bool operator == (const CharString &lhs, const wchar_t *rhs)
{
	if(lhs.size() != static_cast<int>(std::wcslen(rhs)))
		return false;
	for(int i = 0; i < lhs.size(); ++i)
		if(lhs[i] != rhs[i])
			return false;
	return true;
}

inline bool operator != (const CharString &lhs, const CharString &rhs)
{
	return !(lhs == rhs);
}
inline bool operator != (const CharString &lhs, const wchar_t *rhs)
{
	return !(lhs == rhs);
}

inline bool operator < (const CharString &lhs, const CharString &rhs)
{
	for(int i = 0; i < lhs.size() && i < rhs.size(); ++i)
		if(lhs[i] != rhs[i])
			return lhs[i] < rhs[i];
	return lhs.size() < rhs.size();
}

inline bool operator > (const CharString &lhs, const CharString &rhs)
{
	for(int i = 0; i < lhs.size() && i < rhs.size(); ++i)
		if(lhs[i] != rhs[i])
			return lhs[i] > rhs[i];
	return lhs.size() > rhs.size();
}

#endif
