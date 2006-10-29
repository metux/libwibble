#ifndef WIBBLE_REGEXP_H
#define WIBBLE_REGEXP_H

/*
 * OO wrapper for regular expression functions
 * 
 * Copyright (C) 2003--2006  Enrico Zini <enrico@debian.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include <wibble/exception.h>
#include <sys/types.h>
#include <regex.h>

namespace wibble {
namespace exception {

////// wibble::exception::Regexp

class Regexp : public wibble::exception::Generic
{
protected:
	int m_code;
	std::string m_message;

public:
	Regexp(const regex_t& re, int code, const std::string& context)
		throw ();
	~Regexp() throw () {}

	/// Get the regexp error code associated to the exception
	virtual int code() const throw () { return m_code; }

	virtual const char* type() const throw () { return "Regexp"; }
	virtual std::string desc() const throw () { return m_message; }
};

}

class Regexp
{
protected:
	regex_t re;
	regmatch_t* pmatch;
	int nmatch;
	std::string lastMatch;

public:
	Regexp(const std::string& expr, int match_count = 0, int flags = 0) throw (wibble::exception::Regexp);
	~Regexp() throw ();

	bool match(const std::string& str, int flags = 0) throw (wibble::exception::Regexp);
	
	std::string operator[](int idx) throw (wibble::exception::OutOfRange);

	size_t matchStart(int idx) throw (wibble::exception::OutOfRange);
	size_t matchEnd(int idx) throw (wibble::exception::OutOfRange);
	size_t matchLength(int idx) throw (wibble::exception::OutOfRange);
};

class ERegexp : public Regexp
{
public:
	ERegexp(const std::string& expr, int match_count = 0, int flags = 0) throw (wibble::exception::Regexp)
		: Regexp(expr, match_count, flags | REG_EXTENDED) {}
};

class Tokenizer
{
	const std::string& str;
	wibble::Regexp re;

public:
	class const_iterator
	{
		Tokenizer& tok;
		size_t beg, end;
	public:
		const_iterator(Tokenizer& tok) : tok(tok), beg(0), end(0) { operator++(); }
		const_iterator(Tokenizer& tok, bool) : tok(tok), beg(tok.str.size()), end(tok.str.size()) {}

		const_iterator& operator++();

		std::string operator*() const
		{
			return tok.str.substr(beg, end-beg);
		}
		bool operator==(const const_iterator& ti) const
		{
			return beg == ti.beg && end == ti.end;
		}
		bool operator!=(const const_iterator& ti) const
		{
			return beg != ti.beg || end != ti.end;
		}
	};

	Tokenizer(const std::string& str, const std::string& re, int flags)
		: str(str), re(re, 1, flags) {}

	const_iterator begin() { return const_iterator(*this); }
	const_iterator end() { return const_iterator(*this, false); }
};

}

// vim:set ts=4 sw=4:
#endif