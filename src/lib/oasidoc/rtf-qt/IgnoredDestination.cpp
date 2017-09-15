/*
    Copyright (C)  2010  Brad Hards <bradh@frogmouth.net>

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "IgnoredDestination.h"

#include "rtfreader.h"

namespace RtfReader
{
    IgnoredDestination::IgnoredDestination( Reader *reader, AbstractRtfOutput *output, const QString &name ) :
      Destination( reader, output, name )
    {
    }

    IgnoredDestination::~IgnoredDestination()
    {
    }

    void IgnoredDestination::handleControlWord( const QString &controlWord, bool hasValue, const int value )
    {
    }

    void IgnoredDestination::handlePlainText( const QString &plainText )
    {
    }

    void IgnoredDestination::aboutToEndDestination()
    {
    }
}
