// Copyright 2011-2020, Molecular Matters GmbH <office@molecular-matters.com>
// See LICENSE.txt for licensing details (2-clause BSD License: https://opensource.org/licenses/BSD-2-Clause)

#pragma once

#include "PsdAssert.h"
#include <string>


PSD_NAMESPACE_BEGIN

class SyncFileReader;

namespace util
{
	/// \ingroup Util
	/// \class FixedSizeString
	/// \brief A class representing a string containing a fixed number of characters.
	/// \details This class offers functionality similar to other string implementations, such as std::string.
	/// However, as the name implies, a FixedSizeString will never grow, shrink, or allocate any memory dynamically. It can
	/// often be used in situations where the maximum length of a string can be limited, such as when dealing with filenames,
	/// in the logging system, when parsing files, etc. A FixedSizeString should be preferred to other implementations
	/// in such cases.
	template <typename tChar = char>
	class FixedSizeString
	{
	public:
		/// A constant denoting the capacity of the string.
		static const size_t CAPACITY = 1024;


		/// \brief Clears the string such that GetLength() yields 0.
		/// \remark After calling Clear(), no assumptions about the characters stored in the internal array should be made.
		void Clear(void)
		{
			m_length = 0;
			m_string[0] = '\0';
		}

		/// Assigns a string.
		void Assign(const tChar* const str)
		{
			m_length = std::char_traits<tChar>::length(str);;
			PSD_ASSERT(m_length < CAPACITY, "String does not fit into FixedSizeString.");

			memcpy(m_string, str, m_length+1);
		}

		/// Appends a string.
		void Append(const tChar* str)
		{
			Append(str, strlen(str));
		}

		/// Appends part of another string.
		void Append(const tChar* str, size_t count)
		{
			PSD_ASSERT(m_length + count < CAPACITY, "Cannot append character(s) from string \"%s\". Not enough space left.", str);
			memcpy(m_string + m_length, str, count);
			m_length += count;
			m_string[m_length] = '\0';
		}

		/// Returns whether the string equals a given string.
		bool IsEqual(const tChar* other) const
		{
			return (strcmp(m_string, other) == 0);
		}


		/// Returns the i-th character.
		inline tChar& operator[](size_t i)
		{
			// allow access to the null terminator
			PSD_ASSERT(i <= m_length, "Character cannot be accessed. Subscript out of range.");
			return m_string[i];
		}

		/// Returns the i-th character.
		inline const tChar& operator[](size_t i) const
		{
			// allow access to the null terminator
			PSD_ASSERT(i <= m_length, "Character cannot be accessed. Subscript out of range.");
			return m_string[i];
		}

		/// Returns the C-style string.
		inline const tChar* c_str(void) const
		{
			return m_string;
		}

		/// Returns the length of the string, not counting the terminating null.
		inline size_t GetLength(void) const
		{
			return m_length;
		}

	private:
		tChar m_string[CAPACITY];
		size_t m_length;
	};

	FixedSizeString<char> ReadPascalString(SyncFileReader& reader, size_t aPadding = 0);
	FixedSizeString<char16_t> ReadUnicodeString(SyncFileReader& reader);
}

PSD_NAMESPACE_END
