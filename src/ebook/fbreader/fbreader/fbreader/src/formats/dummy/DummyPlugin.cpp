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

#include <ZLFile.h>
#include <ZLInputStream.h>

#include "DummyPlugin.h"
#include "DummyMetaInfoReader.h"
#include "DummyBookReader.h"
#include "../../library/Book.h"

DummyPlugin::DummyPlugin() {
}

DummyPlugin::~DummyPlugin() {
}

bool DummyPlugin::providesMetaInfo() const {
	return true;
}

bool DummyPlugin::acceptsFile(const ZLFile &file) const {
	return file.extension() == "dummy";
}

bool DummyPlugin::readMetaInfo(Book &book) const {
	return DummyMetaInfoReader(book).readMetaInfo(ZLFile(path).inputStream());
}

bool DummyPlugin::readModel(BookModel &model) const {
	return DummyBookReader(model).readBook(ZLFile(book.fileName()).inputStream());
}

shared_ptr<ZLImage> DummyPlugin::coverImage(const ZLFile &file) const {
	return DummyCoverReader(file).readCover();
}
