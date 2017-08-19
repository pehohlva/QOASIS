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


#ifndef KOODF_STYLE_PROPERTIES_H
#define KOODF_STYLE_PROPERTIES_H

// Qt
#include <QString>
#include <QHash>


#include "koodf2_export.h"
#include "KoXmlStreamReader.h"


class QString;
class KoXmlWriter;


typedef  QHash<QString, QString>  AttributeSet;  // name, value


class KOODF2_EXPORT KoOdfStyleProperties
{
 public:
    KoOdfStyleProperties();
    virtual ~KoOdfStyleProperties();

    QString attribute(const QString &property) const;
    void    setAttribute(const QString &property, const QString &value);

    virtual void clear();

    virtual bool readOdf(KoXmlStreamReader &reader);
    virtual bool saveOdf(const QString &propertySet, KoXmlWriter *writer);

    void copyPropertiesFrom(const KoOdfStyleProperties &sourceProperties);

 protected:
    /// Read all attributes from the XML element.
    /// This function is normally called from readOdf().
    bool readAttributes(KoXmlStreamReader &reader);
    bool saveAttributes(KoXmlWriter *writer);

 private:
    class Private;
    Private * const d;
};


void copyAttributes(KoXmlStreamReader &reader, AttributeSet &attributes);
void saveAttributes(AttributeSet &attributes, KoXmlWriter *writer);


#endif
