/*
 *  Copyright (c) 2010 Carlos Licea <carlos@kdab.com>
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published
 *  by the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "KoRawCellChild.h"

#include <KoGenStyles.h>
#include <KoXmlWriter.h>

KoRawCellChild::KoRawCellChild(const QByteArray& content)
: m_content(content)
{
}

KoRawCellChild::~KoRawCellChild()
{
}

void KoRawCellChild::saveOdf(KoXmlWriter& writer, KoGenStyles& styles) const
{
    Q_UNUSED(styles)

    writer.addCompleteElement(m_content.data());
}
