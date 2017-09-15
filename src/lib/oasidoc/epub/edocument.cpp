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
#include "edocument.h"
#include "../QmyDom.h"
#include "../kzip.h"
#include <QByteArray>
#include <QImage>
#include <QMap>
#include <QString>
#include <QtCore/QBuffer>
#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/qbytearray.h>
#include <QtCore/qfile.h>
#include <QtCore/qglobal.h>
#include <QtCore/qiodevice.h>
#include <QtCore/qstring.h>
#include <QtXml/QDomDocument>
#include <qstringlist.h>
using namespace Epub;


/* remove a file */
inline bool unlink(const QString fullFileName)
{
    if (fullFileName.size() > 0) {
    QFile f( fullFileName );
        if ( f.exists(fullFileName) ) {
       if (f.remove()) {
        return true;
       }
        }
    }
return false;
}


inline bool file_go_to(const QString fullFileName, QByteArray chunk ) {
    QFileInfo fi(fullFileName);
    if (fullFileName.contains("/", Qt::CaseInsensitive)) {
    QDir dira(fi.absolutePath());
    if ( dira.mkpath(fi.absolutePath()) ) { } else {
    return false;
    }
    }
    unlink(fullFileName); /// if is one make place..
        QFile f( fullFileName );
                if ( f.open(  QIODevice::WriteOnly ) ) {
                    f.write(chunk.constData(),chunk.size());
                    f.close();
                     if (f.bytesAvailable() > 0) {
                        return true;
                      } else {
                        return false;
                      }
                }
    return false;

}


Document::Document(const QString &fileName, const QString &dir )
    : mFileName(fileName)  {
  USEBASEREF = false;
  CoverPager = QString();
  StartIndexPager = QString();
  minNrorder = 10000;
  maxNrorder = 0;
  QFileInfo cc(fileName);
  summerror = 0;
  QString fileini = cc.baseName();
  const QString dirfile = fileini.replace(".","_");
  showsynrorun = true;
  compress_on_ram = false;
  DIRBROWSERBOOK = dir + dirfile + QString("/");
  EPUBDEBUG() << "fileName" << fileName;
  EPUBDEBUG() << "DIRBROWSERBOOK" << DIRBROWSERBOOK;
}

bool Document::open() {

  KZipStream *Kzip = new KZipStream(mFileName);
  QByteArray tableofcontenent;
  QByteArray Filelistener;
  QByteArray METAINFOFILE;
  if (Kzip->canread()) {
    const QStringList entries = Kzip->filelist();

    QMap<QString, QByteArray> allfiles = Kzip->listData();
    QMapIterator<QString, QByteArray> i(allfiles);
    /// 1-/ first step separate image to other file!
    /// 2-/ search the Meta info file: to get table of contenents
    /// 3-/ order all file by order tag playOrder="12"> from toc.nx file
    /// 4-/ relink all file by urlfragment # to enable click to page
    /// 5-/ reinsert all image base64 encoded in the full one html xml file all
    /// page..
    while (i.hasNext()) {
      i.next();
      QByteArray xchunk;
      QByteArray streamxq = i.value();
      if (compress_on_ram) {
      xchunk= qCompress(streamxq);
      } else {
        xchunk = streamxq;
        streamxq.clear();
      }
      QString namex(i.key());
      QString mimex = MimeinFile(namex);
      QString rec = QLatin1String("not");
      if (mimex == QLatin1String("text/html") || mimex == QLatin1String("application/xhtml+xml")) {
        uniqueuris.insert(namex);
        rec = QLatin1String("track");
      }
       if (showsynrorun) {
      EPUBDEBUG() << "file zip  in:" << namex << " reg:" << rec;
       }
      QImage pic = QImage::fromData(i.value());
      if (!pic.isNull()) {
          ////// QByteArray picitem = pic_encode_compressed(pic,compress_on_ram);
          mImages.insert(namex,xchunk);
      } else {
        if (namex == METAINFOCONTAINERFILE) { /// must have otherwise not valid epub
          NEXTFILETOREADXMLCHUNK = xchunk;
          mxcache.insert(namex,xchunk);
        } else {
          mxcache.insert(namex,xchunk);
        }
      }
    }
    Kzip->~KZipStream(); /// tanks e by..
    /// steep 1 one ok...   META-INF/container.xml
    if (NEXTFILETOREADXMLCHUNK.size() < 4) {
      return false;
    } else {
      bool ok = MetaReader(); ///// BASEREFDIR
      if (!BASEREFDIR.isEmpty()) {
          EPUBDEBUG() << "BASEREFDIR:" << BASEREFDIR;
      }
      if (showsynrorun ) {
      EPUBDEBUG() << "rspine:" << rspine; //// order from page id!! not order to menu!
      EPUBDEBUG() << "StartIndexPager:" << StartIndexPager;
      EPUBDEBUG() << "CoverPager:" << CoverPager;
      EPUBDEBUG() << "mFileTitle:" << mFileTitle;
      EPUBDEBUG() << "minNrorder:" << minNrorder;
      EPUBDEBUG() << "maxNrorder:" << maxNrorder;
      EPUBDEBUG() << "PageItem:" << mxPageItem.size();
      EPUBDEBUG() << "MenuItem:" << mxMenuItem.size();
      EPUBDEBUG() << "rspine size:" << rspine.size();
      }
      EPUBDEBUG() << "total error:" << summerror;
      if (summerror > 0) {
      EPUBDEBUG() << "Code error:" << recERROR;
      }

      if (ok && summerror < 3) {
       PageBuilder();
      }

      if (RevisionPageItem.size() > 1 ) {
          return true;
      }

      return false;
    }

  }
  return false;
}

void Document::PageBuilder() {
   Lost_Found_Syncro(); /// debug uniqueuris check if all
   //// file is list from zip lost e found list not linked!
   //// QList<EpubToc> mxMenuItem;
   QSet<QString> UNIQUEURLSET;
   QString zurl,tmp1,tmp2,idref;
   const int pageum =  (maxNrorder - minNrorder) + 2;
   const int sizeepub = mxMenuItem.size();
   const int qustsize  = uniqueuris.size();
   const int qpages_size  = mxPageItem.size();
   EPUBDEBUG() << "PageBuilder tot:" << qpages_size << " diff:" << pageum << ":" << sizeepub << " - remainfile:" << qustsize;
   //// union order & menu && lost found must stay 0000000
   EpubToc coverfox;
    for (int x = 0; x < rspine.count(); x++) {
         idref = rspine.at(x);
         EpubToc fox;
         EpubToc foxMenu;
          GetPageOrder_id(idref,fox);
          fox.orderid = x;
          GetPageKey_md843(fox.md843,foxMenu);
          tmp1 = DIRBROWSERBOOK + fox.qurl();
          QFileInfo fio(tmp1);
          const QString box_uri = fio.absoluteFilePath();
          ///// titel check
          if (fio.exists() && !UNIQUEURLSET.contains(box_uri)) {
              fox.jumpurl = box_uri;
              UNIQUEURLSET.insert(box_uri);
              fox.title = foxMenu.title;
              if (fox.title.isEmpty()) {
                fox.title = QString("Page - Unknow Title / or not set.");
              }
              RevisionPageItem.append(fox);
              EPUBDEBUG() << RevisionPageItem.size() << "/" << idref << ") GOTO REGISTER: " << fox.debug() << "_" << fio.absoluteFilePath();
          }
      }
   int listers = -1;
   QList<EpubToc>::const_iterator x;
   for (x = mxPageItem.constBegin(); x != mxPageItem.constEnd(); ++x) {
        EpubToc fox=*x;
        listers++;
        tmp1 = DIRBROWSERBOOK + fox.qurl();
        QFileInfo fio(tmp1);
        const QString box_uri = fio.absoluteFilePath();
        if (fio.exists() && !UNIQUEURLSET.contains(box_uri)) {
            fox.orderid = RevisionPageItem.count();
            fox.jumpurl = box_uri;
            UNIQUEURLSET.insert(box_uri);
            if (fox.title.isEmpty()) {
              fox.title = QString("Page - Unknow Title / or not set.");
            }
           fox.title = QString("Hidden/Listed page: %1").arg(fox.title);
           RevisionPageItem.append(fox);
        }
        EPUBDEBUG() << RevisionPageItem.size() << "/" << listers << ") GOTO REGISTER2: " << fox.debug() << "_" << fio.absoluteFilePath();
   }



   QStringList lostli = uniqueuris.toList();
   EPUBDEBUG() << "!!!!!!!!Lost & found size->:" << lostli.size();
   for (int x = 0; x < lostli.size(); x++) {
       EPUBDEBUG() << "!!!!!!!!  Lost & found page:" << lostli.at(x);
   }
}
//// to debug + save ram place
void Document::Lost_Found_Syncro() {

    QList<EpubToc>::const_iterator i;
    QList<EpubToc>::const_iterator x;
    for (i = mxPageItem.constBegin(); i != mxPageItem.constEnd(); ++i) {
         EpubToc fox=*i;
         const QString urllzip = fox.qurl();
         if ( uniqueuris.contains( urllzip) ) {
               uniqueuris.remove( urllzip );
         }
         if (showsynrorun) {
         EPUBDEBUG() << "Page item set:" << fox.debug();
         }
    }
    for (x = mxMenuItem.constBegin(); x != mxMenuItem.constEnd(); ++x) {
         EpubToc fox=*x;
         const QString urllzip = fox.qurl();
         if ( uniqueuris.contains( urllzip) ) {
               uniqueuris.remove( urllzip );
         }
          if (showsynrorun) {
         EPUBDEBUG() << "Menu item set:" << fox.debug();
          }
    }

    ///// QMap<QString, QByteArray> mImages;
    ///// QMap<QString, QByteArray> mxcache;  mFileName


    QMapIterator<QString,QByteArray> a(mImages);
    while (a.hasNext()) {
        a.next();
        QString mifile = a.key();
        const QString dest = DIRBROWSERBOOK + mifile;
        //// EPUBDEBUG() << " dest:" << dest;
        file_go_to(dest,a.value());
    }
    QMapIterator<QString,QByteArray> o(mxcache);
    while (o.hasNext()) {
        o.next();
        const QString mcfile = o.key();
        const QString dest = DIRBROWSERBOOK  + mcfile;
        ////EPUBDEBUG() << " dest:" << dest;
        file_go_to(dest,o.value());
    }
    mImages.clear();
    mxcache.clear();
}

/// order for page!!!
void Document::GetPageOrder_id( const QString ref , EpubToc & item ) {
      //// QList<EpubToc> mxMenuItem; /// dax.type toc cover
      QList<EpubToc>::const_iterator i;
      QList<EpubToc>::const_iterator x;
      bool found = false;
      for (i = mxPageItem.constBegin(); i != mxPageItem.constEnd(); ++i) {
           EpubToc fox=*i;
           if (fox.idref == ref) {
              if ( uniqueuris.contains( fox.qurl() ) ) {
                    uniqueuris.remove( fox.qurl() );
              }
              found = true;
              item = fox;
           }
      }
      if (!found) {
          for (x = mxMenuItem.constBegin(); x != mxMenuItem.constEnd(); ++x) {
               EpubToc fox=*i;
               if (fox.idref == ref) {
                  if ( uniqueuris.contains( fox.qurl() ) ) {
                        uniqueuris.remove( fox.qurl() );
                  }
                  found = true;
                  item = fox;
               }
          }
      }
      if (!found) {
      this->setEpubError(QString("Unable to get id from page %1").arg(ref));
      }
}
/// get from Menu toc list
void Document::GetPageKey_md843( const int idmd , EpubToc & item ) {
      //// QList<EpubToc> mxMenuItem; /// dax.type toc cover
      QList<EpubToc>::const_iterator i;
      for (i = mxMenuItem.constBegin(); i != mxMenuItem.constEnd(); ++i) {
           EpubToc fox=*i;
           if (fox.md843 == idmd) {
              if ( uniqueuris.contains( fox.qurl() ) ) {
                    uniqueuris.remove( fox.qurl() );
              }
              item = fox;
           }
      }
}

/// order for menu!!!
void Document::GetMenuOrder_id( const int x , EpubToc & item ) {
      //// QList<EpubToc> mxMenuItem; /// dax.type toc cover
      QList<EpubToc>::const_iterator i;
      for (i = mxMenuItem.constBegin(); i != mxMenuItem.constEnd(); ++i) {
           EpubToc fox=*i;
           if (fox.orderid == x) {
              if ( uniqueuris.contains( fox.qurl() ) ) {
                    uniqueuris.remove( fox.qurl() );
              }
              item = fox;
           }
      }
}

/* here only read META-INF/container.xml & follow its */
bool Document::MetaReader() {
  EPUBDEBUG() << "Meta Reader only read & follow:" << METAINFOCONTAINERFILE << " line:" <<  __LINE__;
  const QByteArray xml = NEXTFILETOREADXMLCHUNK;
  NEXTFILETOREADCRONO = METAINFOCONTAINERFILE;
  bool xvalid = false;
  QString tmp0,tmp1,tmp2,uricontents;
  QDomElement root = Make2Domelement_xml_file(NEXTFILETOREADXMLCHUNK);
  QDomNodeList der = root.elementsByTagName("rootfile");
  if (der.count() < 1) {
    EPUBDEBUG() << __FUNCTION__ << " ERROR: der.count():" << der.count() << " line:" <<  __LINE__;
    setEpubError(QString("Unable to get place from file content.opf, inside META-INF/container.xml"));
    return xvalid;
  }
  //// disovery place from "content.opf" meta give only this info not more...
     Remove_from_Ram(NEXTFILETOREADCRONO);
  for (int x = 0; x < der.count(); x++) {
    QDomElement node = der.at(x).toElement();
    NEXTFILETOREADCRONO = node.attribute("full-path");
    EPUBDEBUG() << "Start on file:" << NEXTFILETOREADCRONO << __LINE__;
  }
  if (NEXTFILETOREADCRONO.size() < 1) {
    setEpubError(QString("Unable to get place from file content.opf, inside META-INF/container.xml"));
    return false;
  }
    if (NEXTFILETOREADCRONO.contains("/")) {
      BASEREFDIR = NEXTFILETOREADCRONO.left(NEXTFILETOREADCRONO.lastIndexOf("/")) + "/";
    }
    QDomNodeList itemlist = GetPageName(NEXTFILETOREADCRONO, QString("item"));
    for (int x = 0; x < itemlist.count(); x++) {
      QDomElement nodepager = itemlist.at(x).toElement();
              if (FileListRecord(nodepager)) {
                xvalid = true;
              } else {
                return false;
              }
      }

    //// now get the toc.nx
    if (USEBASEREF) {
      NEXTFILETOREADCRONO = BASEREFDIR + QString("toc.ncx");
    } else {
      NEXTFILETOREADCRONO = QString("toc.ncx");
    }
    /// Readmenu
    EPUBDEBUG() << "get toc from  " << NEXTFILETOREADCRONO << __LINE__;
    QDomNodeList reffitems = GetPageName(NEXTFILETOREADCRONO, "docTitle");
    QDomNodeList navitom = GetPageName(NEXTFILETOREADCRONO, "navMap");
    if (reffitems.count() == 1) {
      QDomElement er = reffitems.at(0).toElement();
      QDomElement ed = er.firstChildElement();
      mFileTitle = ed.firstChild().toText().data();
    }
    if (navitom.count() == 1) {
      QDomElement erlem = navitom.at(0).toElement();
      xvalid = Readmenu(erlem);
    }
    EPUBDEBUG() << "get toc.ncx  end delete navMap " << NEXTFILETOREADCRONO << __LINE__;
    this->Remove_from_Ram(NEXTFILETOREADCRONO);
    NEXTFILETOREADCRONO = BASEREFDIR + CONTENENTOPFFILE; //// if use base ref??
    EPUBDEBUG() << "search  " << CONTENENTOPFFILE << __LINE__;
     if (CacheFinder(CONTENENTOPFFILE)) {
         NEXTFILETOREADCRONO = CONTENENTOPFFILE;
     } else if  ( CacheFinder( NEXTFILETOREADCRONO)) {
        xvalid = true;
     } else {
         this->setEpubError(QString("Unable to find file : %1").arg(CONTENENTOPFFILE));
         return false;
     }
     //// EPUBDEBUG() << "Found at   " << NEXTFILETOREADCRONO  << ":" <<   CONTENENTOPFFILE  << __LINE__;
     QDomNodeList dcover = GetPageName(NEXTFILETOREADCRONO,"reference");
     if (dcover.count() > 0) {
       for (int x = 0; x < dcover.count(); x++) {
         QDomElement node = dcover.at(x).toElement();
         /*  QString reserve;
              QString jumpurl;
              QString zipurl; //// filename dest normal!!
              QString title;
              QString type;
              int md843;
              int orderid; */
         if ( node.tagName() == QLatin1String("reference") ) {
                EpubToc dax;
                QString typee = node.attribute("type");
                QString hrefi = node.attribute("href");
                dax.idref = node.attribute("id");
                if (uniqueuris.contains(hrefi)) {
                    uniqueuris.remove(hrefi);
                }
                dax.reserve = hrefi;
                if (USEBASEREF) {
                    hrefi = BASEREFDIR + node.attribute("href");
                }
                if (uniqueuris.contains(hrefi)) {
                    uniqueuris.remove(hrefi);
                }

                dax.title =node.attribute("title");
                dax.jumpurl = QLatin1String("top");
                dax.zipurl = hrefi;
                dax.md843 = genkeyurl(hrefi); /// dax.type toc cover
                if (typee == QLatin1String("toc")) {
                    dax.type = QString("toc");
                    dax.orderid =2; /// go to second from itemref
                    StartIndexPager = dax.title + QString("|") + dax.zipurl;
                } else if (typee == QLatin1String("cover")) {
                    dax.type = QString("cover");
                    dax.orderid =1; /// go to first from itemref
                    CoverPager = dax.title + QString("|") + dax.zipurl;
                }
                mxMenuItem.append(dax);
         }
       }
     }

     QDomNodeList dspine = GetPageName(NEXTFILETOREADCRONO,"itemref");
     if (dspine.count() > 0) {
       for (int x = 0; x < dspine.count(); x++) {
         QDomElement node = dspine.at(x).toElement();
          if (node.tagName() == QLatin1String("itemref")) {
                 QString orderidx = node.attribute("idref");
                 if (orderidx.isEmpty()) {
                    this->setEpubError(QString("Not found  idref to over or init page!"));
                     return false;
                 }
                 if (rspine.size() < mxPageItem.size()) {
                 rspine << orderidx;  /// update mxPageItem page first 2
                 }
          }
       }
     }




     this->Remove_from_Ram(NEXTFILETOREADCRONO);
     if (CoverPager.isEmpty()) {
        this->setEpubError(QString("Coverpage or StartPage variable is not full! from file %1").arg(NEXTFILETOREADCRONO));
     } else {
        xvalid = true;
     }
             if (StartIndexPager.isEmpty()) {
                 StartIndexPager = QString("takefirstpage_cmd");
              }
              if (CoverPager.isEmpty()) {
                  CoverPager = QString("makecoer_cmd");
               }
  return xvalid;
}

QDomNodeList Document::GetPageName(const QString file_name, const QString tag) {
     if (showsynrorun) {
   EPUBDEBUG() << "Request GetPageName: file_name/tag" <<   file_name << ":" << tag <<  " current actioncycle.";
     }
  QDomNodeList defineterror;
  QString tmp;
  QMap<QString, QByteArray>::Iterator it;
  for (it = mxcache.begin(); it != mxcache.end(); ++it) {
    if (it.key() == file_name) {
      QByteArray chunx = it.value();
      QDomElement e = Make2Domelement_xml_file(chunx);
        tmp = e.tagName();
      QDomNodeList der = e.elementsByTagName(tag);
      QDomNodeList dera = e.elementsByTagName(e.tagName());
      if (der.count() > 0) {
        return der;
      } else if (dera.count() > 0 ) {
        return dera;
      }
    }
  }
  EPUBDEBUG() << "Request Error:" << file_name << ":" << tag << " export FAIL!....";
  return defineterror;
}

bool Document::Remove_from_Ram(const QString file_name) {
    QMap<QString, QByteArray>::Iterator it;
     if (showsynrorun) {
    EPUBDEBUG() << "remove file:" << file_name << " .";
     }
    bool remove = false;
    int rec = 0;
    for (it = mxcache.begin(); it != mxcache.end(); ++it) {
      if (it.key() == file_name) {
         remove = true;
      }
    }
    if (remove) {
      rec = mxcache.remove(file_name);
      if (rec != 1) {
       setEpubError(QString("Unable to remove = %2 from ram cache file: %1").arg(file_name).arg(rec));
      } else {
           if (showsynrorun) {
        EPUBDEBUG() << "Success remove from Ram file:" << file_name << " .";
           }
      }
    }

   return (rec == 1)? true : false;
}



bool Document::FileListRecord(const QDomElement e) {

  if (e.tagName() != QLatin1String("item")) {
    return false;
  }
  ///// BASEREFDIR
  const QString xid = e.attribute("id");
  const QString xhref = e.attribute("href");
  const QString basexhref = BASEREFDIR + e.attribute("href");
  const QString xmedia = e.attribute("media-type");

  if (xid.isEmpty()) {
    setEpubError(QString(
        "Not found attributes id in item tag from content.opf"));
  }

  if (xmedia.isEmpty()) {
    setEpubError(QString(
        "Not found attributes media-type in item tag from content.opf"));
  }
  if (xhref.isEmpty()) {
    setEpubError(
        QString("Not found attributes href in item tag from content.opf"));
  }
  if (xmedia.isEmpty()) {
    setEpubError(QString(
        "Not found attributes media-type in item tag from content.opf"));
  }

  if (xmedia.contains(QLatin1String("image/"))) {
    //// cheeck if exist
    if (mImages.contains(xhref)) {
      rec_IMAGES << xhref;
    } else {
      if (mImages.contains(basexhref)) {
        USEBASEREF = true;
      } else {
        setEpubError(QString("Nofile: %2 from META-INF/container.xml:-> !!%1")
                         .arg(xhref)
                         .arg(ROOTFOLLOWFROMFILE));
      }
    }
  } else if (xmedia.contains(QLatin1String("application/xhtml"))) {
    if (mxcache.contains(xhref)) {
      //// super.. mxPageItem; here is list all file to play.. in order???
        EpubToc dax;
        dax.title = QLatin1String("Unknow Title");
        dax.type = QLatin1String("xhtml");
        dax.jumpurl = xid;
        dax.idref = xid;
        dax.md843 = genkeyurl(xhref);
        dax.zipurl = xhref;
        dax.reserve = xhref;
        dax.orderid = 0; ///cover e toc all
        mxPageItem.append(dax);

    } else {
      if (mxcache.contains(basexhref)) {
         USEBASEREF = true;
         EpubToc dax;
         dax.title = QLatin1String("Unknow Title");
         dax.type = QLatin1String("xhtml");
         dax.jumpurl = xid;
         dax.idref = xid;
         dax.md843 = genkeyurl(basexhref);
         dax.zipurl = basexhref;
         dax.reserve = xhref;
         dax.orderid = 0; ///cover e toc all
         mxPageItem.append(dax);
      } else {
        setEpubError(QString("Nofile: %2 from META-INF/container.xml:-> !!%1")
                         .arg(xhref)
                         .arg(ROOTFOLLOWFROMFILE));
      }
    }
  }
  return true;
}

bool Document::Readmenu(const QDomElement &element) {
  QDomElement child = element.firstChildElement();

  while (!child.isNull()) {
    ////// EPUBDEBUG() << child.tagName() <<  " loop here..";
    if (child.tagName() == QLatin1String("navPoint")) {
      FLYID = child.attribute("id");
      FLYORDER = child.attribute("playOrder");
      Readmenu(child);
    } else if (child.tagName() == QLatin1String("content")) {
      if (USEBASEREF) {
        FLYURL = BASEREFDIR + child.attribute("src");
      } else {
        FLYURL = child.attribute("src");
        if (uniqueuris.contains(FLYURL)) {
            uniqueuris.remove(FLYURL);
        }
      }
      bool ok;
      const int idx = FLYORDER.toInt(&ok);
      QString keyuu, urti,tmpurl;
      if (ok) {
        if (FLYURL.contains("#")) {
          keyuu = FLYURL.left(FLYURL.lastIndexOf("#")); //// giusto
          QStringList io = FLYURL.split(QString("#"));
          urti = io.at(1);
          if (uniqueuris.contains(urti)) {
              uniqueuris.remove(urti);
          }
          if (uniqueuris.contains(keyuu)) {
              uniqueuris.remove(keyuu);
          }
        } else {
          keyuu = FLYURL;
          urti = QString("toc") + QString::number(genkeyurl(FLYURL));
        }
        /*  QString reserve;
             QString jumpurl;
             QString zipurl; //// filename dest normal!!
             QString title;
             QString type;
             int md843;
             int orderid; */
        if (uniqueuris.contains(keyuu)) {
            uniqueuris.remove(keyuu);
        }
        EpubToc dax;
        dax.title = FLYNAME;
        dax.type = QLatin1String("toclist");
        dax.jumpurl = urti;
        dax.zipurl = keyuu;
        dax.reserve = FLYURL;
        dax.orderid = idx + 2; ///cover e toc
        dax.md843 = genkeyurl(keyuu);
        mxMenuItem.prepend(dax);
        minNrorder = qMin(minNrorder, idx);
        maxNrorder = qMax(maxNrorder, idx);
        //// EPUBDEBUG() << dax.print();
      } else {
        EPUBDEBUG() << FLYNAME << " to int fail not insert...";
      }
      Readmenu(child);
    } else if (child.tagName() == QLatin1String("navLabel")) {
      Readmenu(child);
    } else if (child.tagName() == QLatin1String("text")) {
      FLYNAME = child.firstChild().toText().data();
    } else if (child.isText()) {
      EPUBDEBUG() << "ERROR...!";
    } else if (child.tagName() == QLatin1String("manifest")) {
      Readmenu(child);
    } else if (child.tagName() == QLatin1String("item")) {
      FileListRecord(child);
    } else {
      EPUBDEBUG() << "not know tag  :" << child.tagName();
    }

    child = child.nextSiblingElement();
  }

  return true;
}

QDomElement Document::Make2Domelement_xml_file(const QByteArray xml) {
     if (showsynrorun) {
    EPUBDEBUG() << "Make2Domelement_xml_file file:" << NEXTFILETOREADCRONO;
     }

  QDomDocument droot;
  if (xml.size() < 5) {
    return droot.createElement("root");
  }
  QDomElement exnode;
  QXmlSimpleReader reader;
  //// reader.setNamespaceProcessing(false);
  QXmlInputSource source;
  if (compress_on_ram) {
     source.setData(qUncompress(xml));
  } else {
     source.setData(xml);
  }
  QString EErrorMsg, tmp1, tmp2;
  QDomDocument document;
  /////  document.createProcessingInstruction()
  if (document.setContent(&source, &reader, &EErrorMsg)) {
    exnode = document.documentElement();
    ////exnode.setAttribute("xmlns",0);
     if (showsynrorun) {
    EPUBDEBUG() << "Success Make2Domelement_xml_file first tagname:" << exnode.tagName();
     }
    return exnode;
  } else {
    setEpubError(QString("Make2Domelement_xml_file Unable to read xml file...%1 ").arg(EErrorMsg));
    return droot.createElement("root");
  }
}

void Document::setEpubError(QString msg) {
  EPUBDEBUG() << "New error:" << msg;
  summerror++;
  recERROR << msg;
}

bool Document::CacheFinder( const QString findfile ) {
    QMap<QString, QByteArray>::Iterator it;
     if (showsynrorun) {
    EPUBDEBUG() << "CacheFinder:" << findfile << " .";
     }
    bool havigness = false;
    //// int rec = 0;
    for (it = mxcache.begin(); it != mxcache.end(); ++it) {
      if (it.key() == findfile) {
         havigness = true;
      }
    }
    return havigness;
}



Document::~Document() {}

QMap<QString, QByteArray> Document::structure() const { return mxcache; }

QMap<QString, QByteArray> Document::images() const { return mImages; }

/// ram place qCompress & qUncompress
QByteArray Document::pic_encode_compressed( QImage im , bool press )  {
    int w=im.width();
    //// int h=im.height();
    QByteArray bytes;
    if (w > 550 ) {
        im.scaled(550,550, Qt::KeepAspectRatio);
    }
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    im.save(&buffer, "PNG");
    if (bytes.size() > 0) {
    QByteArray blueimag = bytes.toBase64();
    QByteArray orderpic("data:image/png;base64,");
    orderpic.append(blueimag);
        if (press) {
        return qCompress(orderpic);
        } else {
         return orderpic;
        }
    } else {
        if (press) {
           return qCompress(QByteArray("data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw=="));
        } else {
           return QByteArray("data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==");
        }

    }
}



