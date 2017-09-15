/*
    Copyright (C)  2017 Piter K. <pehohlva@gmail.com>

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
#ifndef EPUBBYDOCUMENT_H
#define EPUBBYDOCUMENT_H

#include "../kzip.h"
#include "../QmyDom.h"


#define refill QObject::tr
#define recit2 QString::toStdString

#if 0 //// 1 or 0
#define EPUBDEBUG qDebug
#define STAGE 1
#else
#define EPUBDEBUG                                                              \
  if (0)                                                                       \
  qDebug
#define STAGE 0
#endif




struct EpubToc {

  QString print() {
        QString result = QString("<div><a href='#%1'>").arg(jumpurl) +
                     QString("<h1>") + title + QString("</h1>") +
                     QString("</a></div>\n<!-- Url intern = (%1) ,%2, -->").arg(qurl()).arg(md843);
    return result;
  }
  QString qurl() {
      QString x = zipurl;
      if (x.isEmpty()) {
          x = reserve;
      }
      return x;
  }

  QString debug() {
      QString x = QString("|reserve:%1").arg(reserve);
               x+=QString("|idref:%1").arg(idref);
               x+=QString("|jumpurl:%1").arg(jumpurl);
               x+=QString("|zipurl:%1").arg(zipurl);
               x+=QString("|title:%1").arg(title);
               x+=QString("|type:%1").arg(type);
               x+=QString("|md843:%1").arg(md843);
               x+=QString("|orderid:%1").arg(orderid);
      return x;
  }

  QString reserve; //// filename dest normal!!
  QString jumpurl; //// toc meta id && page link!!
  QString zipurl;
  QString title;
  QString type;
  QString idref;  /// only if content.opf
  int md843;
  int orderid;
};

#define METAINFOCONTAINERFILE QLatin1String("META-INF/container.xml")
#define CONTENENTOPFFILE QLatin1String("content.opf")

namespace Epub {

class Document {
public:
  Document(const QString &fileName , const QString &dir );
  ~Document();
  bool open();
  QList<EpubToc> MenuList() const { return RevisionPageItem; }
  QString lastErrorString() { return recERROR.join(" ; "); }
  private:
  void setEpubError(QString msg);
  QDomElement  Make2Domelement_xml_file(const QByteArray xml); /// return first Doml from stream or nothing
  QMap<QString, QByteArray> images() const;
  QMap<QString, QByteArray> structure() const;
  bool Remove_from_Ram(const QString file_name);
  QByteArray pic_encode_compressed(QImage im , bool press);
  void Lost_Found_Syncro();
  void PageBuilder();
  void GetPageKey_md843( const int idmd , EpubToc & item );
  void GetMenuOrder_id(const int x , EpubToc &item );
  void GetPageOrder_id( const QString ref , EpubToc & item );
  bool MetaReader();
  bool CacheFinder(const QString findfile);
  bool Readmenu(const QDomElement &element);
  QDomNodeList GetPageName(const QString file_name, const QString tag = "body");
  bool FileListRecord(const QDomElement e);
  QStringList recERROR;
  ///// QStringList rec_FILE;
  QStringList rec_IMAGES;
  QStringList rspine;
  QSet<QString> uniqueuris; /// unique filelist! to extract..remove item is found in meta item toc
  QMap<QString, QByteArray> mImages;
  QMap<QString, QByteArray> mxcache;
  QList<EpubToc> mxMenuItem;
  QList<EpubToc> mxPageItem;
  QList<EpubToc> RevisionPageItem; /// set correct cover & start from package/guide xml
  QString mFileName;
  QString mFileTitle;
  QByteArray EContent;
  QString mErrorString;
  QString FLYID;
  QString FLYORDER;
  QString FLYURL;
  QString FLYNAME;
  QString CoverPager;
  QString StartIndexPager;
  QString ROOTFOLLOWFROMFILE;
  QString BASEREFDIR;
  QByteArray NEXTFILETOREADXMLCHUNK;
  QString NEXTFILETOREADCRONO;
  bool USEBASEREF;
  int summerror;
  int minNrorder;
  int maxNrorder;
  bool showsynrorun;
  bool compress_on_ram;
  QString DIRBROWSERBOOK;
};

} // namespace Epub

#endif // DOCUMENT_H
