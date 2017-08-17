/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __PALMDOCSTREAM_H__
#define __PALMDOCSTREAM_H__

#include "PalmDocLikeStream.h"

class ZLFile;
class HuffDecompressor;

class PalmDocStream : public PalmDocLikeStream {

public:
	PalmDocStream(const ZLFile &file);
	~PalmDocStream();
	
	std::pair<int,int> imageLocation(const PdbHeader &header, int index) const;
	bool hasExtraSections() const;
	int firstImageLocationIndex(const std::string &fileName);

private:
	bool processRecord();
	bool processZeroRecord();

private:
	unsigned short myCompressionVersion;
	unsigned long  myTextLength; //TODO: Warning: isn't used
	unsigned short myTextRecordNumber;

	shared_ptr<HuffDecompressor> myHuffDecompressorPtr;
};

#endif /* __PALMDOCSTREAM_H__ */
