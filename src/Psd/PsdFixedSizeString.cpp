// Copyright 2011-2020, Molecular Matters GmbH <office@molecular-matters.com>
// See LICENSE.txt for licensing details (2-clause BSD License: https://opensource.org/licenses/BSD-2-Clause)

#include "PsdPch.h"
#include "PsdAssert.h"
#include "PsdBitUtil.h"
#include "PsdFixedSizeString.h"
#include "PsdSyncFileReader.h"
#include "PsdSyncFileUtil.h"

#include <cstdarg>
#include <cctype>
#include <cstring>


PSD_NAMESPACE_BEGIN

namespace util
{
	FixedSizeString<char> ReadPascalString(SyncFileReader& reader, size_t aPadding)
	{
		char buffer[FixedSizeString<char>::CAPACITY];
		const uint8_t length = fileUtil::ReadFromFileBE<uint8_t>(reader);
		const uint32_t paddedNameLength = bitUtil::RoundUpToMultiple(length+1u, aPadding);
		if (paddedNameLength > 0)
		{
			reader.Read(buffer, paddedNameLength);
		}
		FixedSizeString<char> value;
		value.Assign(buffer);

		return value;
	}

	FixedSizeString<char16_t> ReadUnicodeString(SyncFileReader& reader) 
	{
		char16_t buffer[FixedSizeString<char16_t>::CAPACITY];

		size_t i = 0;
		do 
		{
			reader.Read(&buffer[i], 1);
		} while (buffer[i] != u'\0');
		FixedSizeString<char16_t> value;
		value.Assign(buffer);

		return value;
	}
}

PSD_NAMESPACE_END
