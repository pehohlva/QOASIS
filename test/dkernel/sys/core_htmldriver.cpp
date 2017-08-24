#include "core_htmldriver.h"

#include "kernel_load.h"
#include "fastrambuffer.h"


HtmlDriver::HtmlDriver()
{
    cacheop =-1;
    fullhtmlnow = QString("textutil -convert .. unable to read! or not mac osx.");
    txtutils = run_which(QStringLiteral("textutil"));
    clean_cache();
    //// qDebug() << "### cacheop dir = " <<  cacheop;
}

HtmlDriver::~HtmlDriver() {
   //// DownDir_RM(CACHEBUFFERDISKTMP);
}

bool HtmlDriver::is_text_tool() {
    return (txtutils.size() > 4)? true : false;
}

void HtmlDriver::clean_cache() {
    DownDir_RM(CACHEBUFFERDISKTMP);
    QDir dirsystem;
    if (dirsystem.mkpath(CACHEBUFFERDISKTMP)) {
        cacheop = 1;
    }
}


void HtmlDriver::rtfd_to_html( const QString file ) {
       clean_cache();
    if (cacheop == 1) {
       disk_textutils(file);
    }
}

/* here only osx mac wo have install textutils by default */
void HtmlDriver::disk_textutils( const QString file ) {
    if (is_file(CACHEFILETMP)) {
        unlink(CACHEFILETMP);
    }
    qDebug() << "### handler use-> " <<  __FUNCTION__ << file;
     if (txtutils.size() < 4) {
         QByteArray simhtml("<h1>Your System not support 'textutil' or is not Install!.<h1/>");
         HTMLCOMPRESSED = qCompress(simhtml,9);
       return;
     }
    //// textutil -convert html bello.odt  -output xxx.html
    QString htmltext;
    QProcess *process = new QProcess(NULL);
    process->setReadChannelMode(QProcess::MergedChannels);
    QStringList cmd_rock;
                cmd_rock << "-convert" << "html" << file << "-output" << CACHEFILETMP;
    qDebug() << "### handler use-> | textutil " <<  cmd_rock.join(" ") <<" |";

    process->start(txtutils,cmd_rock,QIODevice::ReadOnly );
      if (!process->waitForFinished()) {
           htmltext = QString("null");
      } else {
           htmltext = readfile(CACHEFILETMP);
           //// unlink(CACHEFILETMP);
           image_find(htmltext);
      }
}

/*
textutil  -convert html /Volumes/dati/sandbox/dkernelbellotrffoto.rtfd -output /Users/dev/.kernelversion/index.html
*/
void HtmlDriver::image_find( QString html ) {
    QMap<QString,QImage> mappic;
    QRegExp expression("src=[\"\'](.*)[\"\']", Qt::CaseInsensitive);
    expression.setMinimal(true);
    int iPosition = 0;
    int goway =-1;
    //// qDebug() << "### handler use-> " <<  __FUNCTION__;
   ////  qDebug() << "### handler use-> " <<  html;
    while ((iPosition = expression.indexIn(html, iPosition)) != -1) {
        const QString imagesrcx = expression.cap(1); /// this must replaced
        int loengh = imagesrcx.length();
        int repos = imagesrcx.indexOf("=");
        QUrl inserter(imagesrcx);
            if (repos < 1) {
              if ( inserter.isLocalFile()) {
                  QString filen = CACHEBUFFERDISKTMP + inserter.toLocalFile();
                  QImage pio = QImage(filen);
                  if (!pio.isNull()) {
                      qDebug()  << filen << "-> image found :-) ->isNull? "  <<  pio.isNull();
                      mappic.insert(imagesrcx,pio);
                  }
                } else {
                  QImage aufi;
                   mappic.insert(imagesrcx,aufi); /// nullpic!!
                 }

               }       /*
                   if (repos > 0) {
                    const QString key = imagesrcx.mid(repos + 1, loengh - (repos - 1));
                     qDebug()  << key << "-> image found "; //// malformed html
                   }
                   */
        iPosition += expression.matchedLength();
    }
    QMapIterator<QString,QImage> i(mappic);
    while (i.hasNext()) {
             i.next();
             QImage ox = i.value();
             const QString htmlimage = QString(pic_encode(ox).constData());
             html.replace(i.key(),htmlimage);
    }
    fullhtmlnow = html;
    QByteArray chunkk(html.toUtf8());
    HTMLCOMPRESSED = qCompress(chunkk,9);
      /* test image base64 not play in console
    QFile f("testhtml.html");
    if (f.open(QFile::WriteOnly)) {
      f.write(chunkk));
      f.close();
    }
    */
}

QByteArray HtmlDriver::pic_encode( QImage im )  {
    int w=im.width();
    int h=im.height();
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
    return orderpic;
    } else {
        return QByteArray("data:image/gif;base64,R0lGODlhAQABAAAAACH5BAEKAAEALAAAAAABAAEAAAICTAEAOw==");
    }
}


/*  Readutf8File file_put_utf8contents */
/* read the contenet of a local file as qstring */
QString readfile(const QString fullFileName )
{
    QString inside = "";
    QFile file(fullFileName);
    if (file.exists()) {
                if (file.open(QFile::ReadOnly | QFile::Text)) {
                    inside = QString( file.readAll().constData() );
                    file.close();
                }
     }
return inside;
}


/* remove dir recursive */
void DownDir_RM(const QString d) {
   QDir dir(d);
    QDir enddir(d);
   if (dir.exists())
   {
      const QFileInfoList list = dir.entryInfoList();
      QFileInfo fi;
      for (int l = 0; l < list.size(); l++)
      {
         fi = list.at(l);
         if (fi.isDir() && fi.fileName() != "." && fi.fileName() != "..")
            DownDir_RM(fi.absoluteFilePath());
         else if (fi.isFile())
         {
            unlink(fi.absoluteFilePath());
         }

      }
         dir.rmdir(d);
   }

   //// return enddir.exists();
}

/* remove a file */
bool unlink(const QString fullFileName)
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

/* check if a int or float nummer */
bool is_numeric(QString incomming)
{
    incomming.replace(QString(" "), QString("")); /* trimm */
    QString str2 = incomming;
    bool ok;
    str2.toFloat(&ok);
return ok;
}

/* encode to name */
QString encodeBase64( QString xml )
{
    QByteArray text;
    text.append(xml);
    return text.toBase64();
}

/* decode to name */
QString decodeBase64( QString xml )
{
    QByteArray xcode("");;
    xcode.append(xml);
    QByteArray precode(QByteArray::fromBase64(xcode));
    QString notetxt = precode.data();
    return notetxt;
}


/* encode to name */
QString encodeBase64( QByteArray chunk )
{
    return chunk.toBase64();
}

/* decode to name */
QString decodeBase64( QByteArray chunk )
{
    QByteArray precode(QByteArray::fromBase64(chunk));
    QString notetxt = precode.data();
    return notetxt;
}


/* copy file from a to b ... if dir not exist make it ...*/
bool copy(const QString inputfile, const  QString outfile)
{
    bool actioncpy = false;
    QString ultimacartellaaperta = outfile.left(outfile.lastIndexOf("/"))+"/";
    QDir dira(ultimacartellaaperta);
    if ( dira.mkpath(ultimacartellaaperta) ) { } else {
    return actioncpy;
    }
    if (is_file(inputfile)) {
           unlink(outfile);
           QFile Imaged(inputfile);
               if (Imaged.copy(outfile)) {
                   actioncpy = true;
                }
    }
return actioncpy;
}


bool is_file(const QString fullFileName)
{
   QFile f( fullFileName );
       if ( f.exists(fullFileName) ) {
   return true;
       } else {
       return false;
   }
}


bool file_put_contents(const QString fullFileName, QString xml , int modus) {
    if (modus == 10) {
        return true; /// no debug!!
    }
    if (fullFileName.contains("/", Qt::CaseInsensitive)) {
    QString ultimacartellaaperta = fullFileName.left(fullFileName.lastIndexOf("/"))+"/";
    QDir dira(ultimacartellaaperta);
    if ( dira.mkpath(ultimacartellaaperta) ) { } else {
    return false;
    }
    }

       if (modus==1) {
           unlink(fullFileName); /// if is one make place..
       }
        QFile f( fullFileName );
            if (modus == 1) {
                if ( f.open(  QIODevice::WriteOnly ) ) {
                    QTextStream sw( &f );
                    sw.setCodec("UTF-8");
                    sw << xml;
                    f.close();
                     if (f.bytesAvailable() > 0) {
                        return true;
                      } else {
                        return false;
                      }
                }
             } else {
                if ( f.open( QFile::Append | QFile::Text ) ) {
                        QTextStream sw( &f );
                        sw.setCodec("UTF-8");
                        sw << xml;
                        f.close();
                        if (f.bytesAvailable() > 0) {
                           return true;
                         } else {
                           return false;
                         }
                 }
              }
}


