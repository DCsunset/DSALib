#include "char_string.hpp"
#include <algorithm>

// KMP algorithm
int CharString::indexOf(const CharString &substr, int pos) const
{
	Vector<int> next(substr.size());
	next[0] = -1;
	// Get next[] value
	for(int i = 0, j = -1; i < substr.size() - 1; )
	{
		if(j == -1 || substr[i] == substr[j])
		{
			++i;
			++j;
			if(substr[i] != substr[j])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}

	// Match
	const CharString &cur = *this; // this
	for(int i = pos, j = 0; i < size_ && j < substr.size_; )
	{
		if(j == -1 || cur[i] == substr[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
		
		// Succeed
		if(j >= substr.size())
			return i - substr.size();
	}

	// Fail
	return -1;
}

// KMP algorithm
int CharString::indexOf(const wchar_t *substr, int pos) const
{
	int length = std::wcslen(substr);
	Vector<int> next(length);
	next[0] = -1;
	// Get next[] value
	for(int i = 0, j = -1; i < length - 1; )
	{
		if(j == -1 || substr[i] == substr[j])
		{
			++i;
			++j;
			if(substr[i] != substr[j])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}

	// Match
	const CharString &cur = *this; // this
	for(int i = pos, j = 0; i < size_ && j < length; )
	{
		if(j == -1 || cur[i] == substr[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
		
		// Succeed
		if(j >= length)
			return i - length;
	}

	// Fail
	return -1;
}

CharString CharString::substring(int start, int end) const
{
	if(end == -1)
		end = size_;
	CharString t;
	if(start < 0 || start >= end)
		return t;
	t.resize(end - start);
	std::copy(data_ + start, data_ + end, t.data_);
	return t;
}

CharString & CharString::operator += (const CharString &val)
{
	auto origial_size = size_;
	resize(size_ + val.size_);
	std::copy(val.data_, val.data_ + val.size_, data_ + origial_size);
	return *this;
}

