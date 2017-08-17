/*
 * Copyright (C) 2008-2010 Geometer Plus <contact@geometerplus.com>
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

#ifndef __ZLPOPUPDATA_H__
#define __ZLPOPUPDATA_H__

#include <string>

#include <ZLResource.h>

class ZLPopupData {

public:
	virtual ~ZLPopupData();

	virtual size_t id() const = 0;
	virtual size_t count() const = 0;
	virtual const std::string text(size_t index) = 0;
	virtual void run(size_t index) = 0;

	static const ZLResource &resource(const std::string &actionId);
};

inline ZLPopupData::~ZLPopupData() {
}

#endif /* __ZLPOPUPDATA_H__ */
