#ifndef CHAR_STRING_LINK_HPP
#define CHAR_STRING_LINK_HPP

#include "char_string.hpp"
#include "list.hpp"

class CharStringLink : public List<CharString>
{
	public:
		void add(Node *pos, CharString str)
		{
			this->insert(pos, std::move(str));
		}

		/* Other member functions:
		 *
		 * `void remove(Node *pos)` is inherited from List<CharString>
		 *
		 * `Node * search(CharString val)` is inherited from List<CharString>
		 *
		 */
};

#endif
