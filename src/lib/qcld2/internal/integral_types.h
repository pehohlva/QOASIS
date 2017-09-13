// Copyright 2013 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.



#include <QtCore/qglobal.h>
/// ompatible on all system 
// Cheap version qint16


/*  
namespace CLD2 {
typedef qint8 uint8;
typedef qint16 uint16;
typedef qint32 uint32;
typedef qint64 uint64;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int int64;

typedef int32 char32;
}       // End namespace CLD2

 */


namespace CLD2 {

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long int uint64;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int int64;

typedef int32 char32;

}       // End namespace CLD2