/* This file is part of the KDE project
 *
 * Copyright (C) 2013 Inge Wallin <inge@lysator.liu.se>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */


#ifndef KOODF_STYLE_MANAGER_H
#define KOODF_STYLE_MANAGER_H

#include "oo_config.h"

#include <QList>

class QString;
class KoStore;
class KoOdfStyle;
class KoOdfListStyle;
class KoXmlStreamReader;
class KoXmlWriter;

class  KoOdfStyleManager
{
 public:
    KoOdfStyleManager();
    ~KoOdfStyleManager();

    KoOdfStyle *style(const QString &name, const QString &family) const;
    void setStyle(const QString &name, KoOdfStyle *style);

    KoOdfListStyle *listStyle(const QString &name) const;
    void setListStyle(const QString &name, KoOdfListStyle *listStyle);

    KoOdfStyle *defaultStyle(const QString &family) const;
    void setDefaultStyle(const QString &family, KoOdfStyle *style);

    void clear();

    bool loadStyles(KoStore *odfStore);
    bool saveNamedStyles(KoXmlWriter *writer);

    QList<KoOdfStyle*> styles() const;
    QList<KoOdfStyle*> defaultStyles() const;

 private:
    // FIXME: Move to private class.
    void collectStyleSet(KoXmlStreamReader &reader, bool fromStylesXml);

 private:
    class Private;
    Private * const d;
};


#endif
