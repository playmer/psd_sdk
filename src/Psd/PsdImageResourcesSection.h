// Copyright 2011-2020, Molecular Matters GmbH <office@molecular-matters.com>
// See LICENSE.txt for licensing details (2-clause BSD License: https://opensource.org/licenses/BSD-2-Clause)

#pragma once


PSD_NAMESPACE_BEGIN

struct AlphaChannel;
struct Thumbnail;

struct Fixed
{
	Fixed() = default;
	Fixed(int32_t aFixed) : mFixed{ aFixed } {};

	float toFloat()
	{
		return mFixed / 65536.0f;
	}
	int32_t mFixed;
};

struct ResolutionInfo
{
	Fixed hRes = 0;
	int16_t hResUnit = 0;
	int16_t widthUnit = 0;
	Fixed vRes = 0;
	int16_t vResUnit = 0;
	int16_t heightUnit = 0;
};

/// \ingroup Sections
/// \class ImageResourcesSection
/// \brief A struct representing the information extracted from the Image Resources section.
/// \sa AlphaChannel
struct ImageResourcesSection
{
	ResolutionInfo* resolutionInfo;		///< The resolution information for the canvas.
	AlphaChannel* alphaChannels;			///< An array of alpha channels, having alphaChannelCount entries.
	unsigned int alphaChannelCount;			///< The number of alpha channels stored in the array.

	uint8_t* iccProfile;					///< Raw data of the ICC profile.
	uint32_t sizeOfICCProfile;

	uint8_t* exifData;						///< Raw EXIF data.
	uint32_t sizeOfExifData;

	bool containsRealMergedData;			///< Whether the PSD contains real merged data.

	char* xmpMetadata;						///< Raw XMP metadata.

	Thumbnail* thumbnail;					///< JPEG thumbnail.
};

PSD_NAMESPACE_END
