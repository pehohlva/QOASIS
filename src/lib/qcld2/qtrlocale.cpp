#include "qtrlocale.h"
#include "datalanguageprovider.h"
/// use function in lib ony this 2 file
#include "compact_lang_det.h"
#include "encodings.h"
/// use function in lib ony this 2 file
///

using namespace std;
using namespace CLD2;

QString toXexsumm( QString put ) {
   QByteArray  letter = put.toUtf8();
   letter.toHex();
   return  QString(letter.constData());
}

//// count number in array ...
static inline int maxscript(int arr[], int stop, int num)
{
    int result = 0;
    for(int i=0; i<stop; i++)
    {
          if (arr[i] == num) {
            result++;
          }
    }
    return result;
}
//// statistic script() from QChar
int  hit_Script_found( QString text ) {
    const int nox = text.size();
    if (nox < 3) {
        return -1;
      }
    int *array = new int[nox];
    for (int o = 0; o < text.size(); o++) {
      const QChar vox(text.at(o));
      const int typsc = (int)vox.script();
      array[o]=typsc;
     }
    std::map <int,int, std::greater < int > > mhit;
    int NrScript =2; /// start from latin & go up..
    int hitmaxnumber =0;
    do {
          NrScript++;
              int hits = maxscript(array,nox,NrScript);
                if (hits > 0) {
                    hitmaxnumber = qMax(hitmaxnumber,hits);
                    mhit.insert ( std::pair<int,int>(hits,NrScript) );
                }
    }while(NrScript < (sumscritpsLang -2)); /// sum of avaiable script
    /// delete array
    delete[] array;
    std::map<int,int>::iterator it = mhit.begin();
    for (it=mhit.begin(); it!=mhit.end(); ++it) {
        if (it->first == hitmaxnumber) {
            //// qDebug() << "hit is on by:" << it->second;
            return it->second;
          }
      }
   return -1;
   //// qDebug() << "found:" << hits << " by:" << NrScript;
}




bool file_put_contents(const QString fullFileName, QString &xml , int modus) {
    if (fullFileName.contains("/", Qt::CaseInsensitive)) {
    QString ultimacartellaaperta = fullFileName.left(fullFileName.lastIndexOf("/"))+"/";
    QDir dira(ultimacartellaaperta);
    if ( dira.mkpath(ultimacartellaaperta) ) { } else {
    return false;
    }
    }
        QTextCodec *codecx;
        codecx = QTextCodec::codecForMib(106);
        QFile f( fullFileName );
            if (modus == 0) {  //// not append!
                if (f.exists()) {
                    f.remove();
                  }
                if ( f.open(  QIODevice::WriteOnly | QIODevice::Append ) ) {
                    QTextStream sw( &f );
                    sw.setCodec(codecx);
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
                        sw.setCodec(codecx);
                        sw << xml;
                        f.close();
                        if (f.bytesAvailable() > 0) {
                           return true;
                         } else {
                           return false;
                         }
                 }
              }
     return false;
}


QString html_encode(const QString &string) {
  QString encoded;
  for(int i=0;i<string.size();++i) {
    QChar ch = string.at(i);
    if(ch.unicode() > 255)
      encoded += QString("&#%1;").arg((int)ch.unicode());
    else
      encoded += ch;
  }
  return encoded;
}


struct Scrpt {
        QChar::Script script;
        const char *name;
    };


struct HitScript
{
    HitScript(std::string n , int i ,int p)
        :name(n),idscript(i),percento(p)
    {}
    QString print() {
                QString sepa(",");
                QString result = QString::fromStdString(name) + sepa + QString::number(idscript) + sepa + QString("%") + QString::number(percento);
                return result;
        }
    QString namesc() {
                //// QString result =
                return QString::fromStdString(name);
        }


    std::string name;
    int idscript;
    int percento;
};




bool QTrlocale::isLatinLang( QString txt ) {
      bool islatin = false;
      const QString resp = CodingChar(txt);
      if (resp == "LATIN" ) {
          return true; /// only latin not mixed!!!
        }
   return islatin;
}


QSet<QString> QTrlocale::qlocaleList() {

  QList < QLocale > allLocales = QLocale::matchingLocales(
    QLocale::AnyLanguage,
    QLocale::AnyScript,
    QLocale::AnyCountry);

  QSet<QString> isoLanguages;

  for (const QLocale & locale: allLocales) {
    isoLanguages.insert(locale.bcp47Name());
  }

  /// qDebug() << isoLanguages;

  return isoLanguages;
}


void QTrlocale::initScriptMap()
{
    struct Scrpt {
        QChar::Script script;
        const char *name;
    } scripts[] = {
        // general
        { QChar::Script_Unknown,                "Unknown" },
        { QChar::Script_Inherited,              "Inherited" },
        { QChar::Script_Common,                 "Common" },
        // pre-4.0
        { QChar::Script_Latin,                  "Latin" },
        { QChar::Script_Greek,                  "Greek" },
        { QChar::Script_Cyrillic,               "Cyrillic" },
        { QChar::Script_Armenian,               "Armenian" },
        { QChar::Script_Hebrew,                 "Hebrew" },
        { QChar::Script_Arabic,                 "Arabic" },  /// 8
        { QChar::Script_Syriac,                 "Syriac" },
        { QChar::Script_Thaana,                 "Thaana" },
        { QChar::Script_Devanagari,             "Devanagari" },
        { QChar::Script_Bengali,                "Bengali" },
        { QChar::Script_Gurmukhi,               "Gurmukhi" },
        { QChar::Script_Gujarati,               "Gujarati" },
        { QChar::Script_Oriya,                  "Oriya" },
        { QChar::Script_Tamil,                  "Tamil" },
        { QChar::Script_Telugu,                 "Telugu" }, /// 17
        { QChar::Script_Kannada,                "Kannada" },
        { QChar::Script_Malayalam,              "Malayalam" },
        { QChar::Script_Sinhala,                "Sinhala" },
        { QChar::Script_Thai,                   "Thai" },   // 120 language
        { QChar::Script_Lao,                    "Lao" },
        { QChar::Script_Tibetan,                "Tibetan" },
        { QChar::Script_Myanmar,                "Myanmar" },
        { QChar::Script_Georgian,               "Georgian" },
        { QChar::Script_Hangul,                 "Hangul" },   /// korea 26 language
        { QChar::Script_Ethiopic,               "Ethiopic" },
        { QChar::Script_Cherokee,               "Cherokee" },
        { QChar::Script_CanadianAboriginal,     "CanadianAboriginal" },
        { QChar::Script_Ogham,                  "Ogham" },
        { QChar::Script_Runic,                  "Runic" },
        { QChar::Script_Khmer,                  "Khmer" },
        { QChar::Script_Mongolian,              "Mongolian" },
        { QChar::Script_Hiragana,               "Hiragana" },
        { QChar::Script_Katakana,               "Katakana" },
        { QChar::Script_Bopomofo,               "Bopomofo" },
        { QChar::Script_Han,                    "Han" },
        { QChar::Script_Yi,                     "Yi" },
        { QChar::Script_OldItalic,              "OldItalic" },
        { QChar::Script_Gothic,                 "Gothic" },
        { QChar::Script_Deseret,                "Deseret" },
        { QChar::Script_Tagalog,                "Tagalog" },
        { QChar::Script_Hanunoo,                "Hanunoo" },
        { QChar::Script_Buhid,                  "Buhid" },
        { QChar::Script_Tagbanwa,               "Tagbanwa" },
        { QChar::Script_Coptic,                 "Coptic" },
        // 4.0
        { QChar::Script_Limbu,                  "Limbu" },
        { QChar::Script_TaiLe,                  "TaiLe" },
        { QChar::Script_LinearB,                "LinearB" },
        { QChar::Script_Ugaritic,               "Ugaritic" },
        { QChar::Script_Shavian,                "Shavian" },
        { QChar::Script_Osmanya,                "Osmanya" },
        { QChar::Script_Cypriot,                "Cypriot" },
        { QChar::Script_Braille,                "Braille" },
        // 4.1
        { QChar::Script_Buginese,               "Buginese" },
        { QChar::Script_NewTaiLue,              "NewTaiLue" },
        { QChar::Script_Glagolitic,             "Glagolitic" },
        { QChar::Script_Tifinagh,               "Tifinagh" },
        { QChar::Script_SylotiNagri,            "SylotiNagri" },
        { QChar::Script_OldPersian,             "OldPersian" },
        { QChar::Script_Kharoshthi,             "Kharoshthi" },
        // 5.0
        { QChar::Script_Balinese,               "Balinese" },
        { QChar::Script_Cuneiform,              "Cuneiform" },
        { QChar::Script_Phoenician,             "Phoenician" },
        { QChar::Script_PhagsPa,                "PhagsPa" },
        { QChar::Script_Nko,                    "Nko" },
        // 5.1
        { QChar::Script_Sundanese,              "Sundanese" },
        { QChar::Script_Lepcha,                 "Lepcha" },
        { QChar::Script_OlChiki,                "OlChiki" },
        { QChar::Script_Vai,                    "Vai" },
        { QChar::Script_Saurashtra,             "Saurashtra" },
        { QChar::Script_KayahLi,                "KayahLi" },
        { QChar::Script_Rejang,                 "Rejang" },
        { QChar::Script_Lycian,                 "Lycian" },
        { QChar::Script_Carian,                 "Carian" },
        { QChar::Script_Lydian,                 "Lydian" },
        { QChar::Script_Cham,                   "Cham" },
        // 5.2
        { QChar::Script_TaiTham,                "TaiTham" },
        { QChar::Script_TaiViet,                "TaiViet" },
        { QChar::Script_Avestan,                "Avestan" },
        { QChar::Script_EgyptianHieroglyphs,    "EgyptianHieroglyphs" },
        { QChar::Script_Samaritan,              "Samaritan" },
        { QChar::Script_Lisu,                   "Lisu" },
        { QChar::Script_Bamum,                  "Bamum" },
        { QChar::Script_Javanese,               "Javanese" },
        { QChar::Script_MeeteiMayek,            "MeeteiMayek" },
        { QChar::Script_ImperialAramaic,        "ImperialAramaic" },
        { QChar::Script_OldSouthArabian,        "OldSouthArabian" },
        { QChar::Script_InscriptionalParthian,  "InscriptionalParthian" },
        { QChar::Script_InscriptionalPahlavi,   "InscriptionalPahlavi" },
        { QChar::Script_OldTurkic,              "OldTurkic" },
        { QChar::Script_Kaithi,                 "Kaithi" },
        // 6.0
        { QChar::Script_Batak,                  "Batak" },
        { QChar::Script_Brahmi,                 "Brahmi" },
        { QChar::Script_Mandaic,                "Mandaic" },
        // 6.1
        { QChar::Script_Chakma,                 "Chakma" },
        { QChar::Script_MeroiticCursive,        "MeroiticCursive" },
        { QChar::Script_MeroiticHieroglyphs,    "MeroiticHieroglyphs" },
        { QChar::Script_Miao,                   "Miao" },
        { QChar::Script_Sharada,                "Sharada" },
        { QChar::Script_SoraSompeng,            "SoraSompeng" },
        { QChar::Script_Takri,                  "Takri" },
        // 7.0
        { QChar::Script_CaucasianAlbanian,      "CaucasianAlbanian" },
        { QChar::Script_BassaVah,               "BassaVah" },
        { QChar::Script_Duployan,               "Duployan" },
        { QChar::Script_Elbasan,                "Elbasan" },
        { QChar::Script_Grantha,                "Grantha" },
        { QChar::Script_PahawhHmong,            "PahawhHmong" },
        { QChar::Script_Khojki,                 "Khojki" },
        { QChar::Script_LinearA,                "LinearA" },
        { QChar::Script_Mahajani,               "Mahajani" },
        { QChar::Script_Manichaean,             "Manichaean" },
        { QChar::Script_MendeKikakui,           "MendeKikakui" },
        { QChar::Script_Modi,                   "Modi" },
        { QChar::Script_Mro,                    "Mro" },
        { QChar::Script_OldNorthArabian,        "OldNorthArabian" },
        { QChar::Script_Nabataean,              "Nabataean" },
        { QChar::Script_Palmyrene,              "Palmyrene" },
        { QChar::Script_PauCinHau,              "PauCinHau" },
        { QChar::Script_OldPermic,              "OldPermic" },
        { QChar::Script_PsalterPahlavi,         "PsalterPahlavi" },
        { QChar::Script_Siddham,                "Siddham" },
        { QChar::Script_Khudawadi,              "Khudawadi" },
        { QChar::Script_Tirhuta,                "Tirhuta" },
        { QChar::Script_WarangCiti,             "WarangCiti" },
        // 8.0
        { QChar::Script_Ahom,                   "Ahom" },
        { QChar::Script_AnatolianHieroglyphs,   "AnatolianHieroglyphs" },
        { QChar::Script_Hatran,                 "Hatran" },
        { QChar::Script_Multani,                "Multani" },
        { QChar::Script_OldHungarian,           "OldHungarian" },
        { QChar::Script_SignWriting,            "SignWriting" },
        // unhandled
        { QChar::Script_Unknown,                0 }
    };
    /// int mmm =-1;
    Scrpt *p = scripts;
    while (p->name) {
        scriptMap.insert(p->name, p->script);
        ++p;
    }
}




QTrlocale::QTrlocale(const int modus, QObject *parent) : QObject(parent),data(new DataLocaleProvider())
{
  d=modus;
  this->initScriptMap();
}

QString QTrlocale::getnameScriptQChar(const ushort unicode) const { //// uniode in

  QChar vox(unicode);
  //// ushort Unn = vox.unicode();
  QString letterqq = QString().append(vox);
  QChar::Script typecha = vox.script();
  QByteArray scriptname = scriptMap.key(typecha);
  const QString scriptid = QString::fromUtf8(scriptname.constData()).toUpper();
  if (scriptid.size() != 0) {
    return scriptid;
  } else {
    qFatal("Unhandled unicode property value: %d", unicode);
  }
  return QString();
}

QString QTrlocale::CodingChar( QString txt ) {
  const int numbero = hit_Script_found(txt);
  //// QString namex;
  int ksize=txt.size();
  if (ksize < 3 || numbero == -1 ) {
      return QString("FAIL");
    }
  int spinn = -1;
  do {
        spinn++;
        const QChar vox(txt.at(spinn));
         const int typsc = (int)vox.script();
          if (numbero == typsc) {
             ksize=spinn - 1; /// stop
             return getnameScriptQChar(vox.unicode());
           }
  }while(spinn < ksize); /// sum of txt
  qFatal("Unable to get script name from value: %d", numbero);
  return QString("FAIL");
}

QString QTrlocale::CodingCld( QString txt ) {
   std::string line, text, temp;
   bool is_plain_text = true;
   bool is_reliable =false;  /// ist brauchbar
   /// int valid_prefix_bytes = 0;
   const char* src = txt.toUtf8().constData();
   Language lang = DetectLanguage(src,strlen(src),is_plain_text,&is_reliable);
   if (is_reliable) {
       return QString::fromStdString(LanguageName(lang)).toUpper();
     } else {
       return CodingChar(txt);
     }

}


QLocale QTrlocale::getQlocaleFromText( const QString txt ) {
    QString lang = CodingCld(txt);
    return data->qlocaleFromLanguageUnique(lang);
}


void QTrlocale::ReadFile( const QString file ) {
         /// for large file qfile is not fast
         QTextStream stream(stdout);
         std::string line, text, temp, f;
         f = qPrintable(file);
          std::ifstream ifs(f);
          qint64 parse = 0;
          /////
          QSet<QString> setunique;
          QString tofileend = QString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n");
                  tofileend +=QString("<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n</head><body>\n\n");
          /// int jump = 0;
          //// const int slice = 33;
                 if ( ! ifs.is_open() ) {
                           stream <<" Failed to open:" << file << "\n";
                           return;
                    }
                      while ( !ifs.eof() )  {
                              getline(ifs, line);
                              QString qline = QString::fromStdString(line);
                              if (qline.size() > 130) {
                                  QString zfrom = qline.mid(80);
                                  zfrom.resize(66);
                                  qline = zfrom;
                                }
                              parse++;
                                  const QString rec_lsd = CodingCld(qline);
                                   //// const QString rec_char = CodingChar(qline);
                                   //// QString rechex = toXexsumm(rec_lsd + rec_char);

                                  QString reline = QString("<p>Line nr.") + QString::number(parse) + "-Lan:" + html_encode(rec_lsd) + " - " + html_encode("(" + qline + ") <p/>");
                                      ////// std::cout << parse <<  " - " << qPrintable(CodingCld(qline))  << ","  << qPrintable(CodingChar(qline)) <<  "- ("  << qPrintable(qline) <<  ")\n";
                                      stream <<"HTML:" << qPrintable(reline) << "\n";
                                      tofileend.append(reline);

                          }

        QString footer = QString("</body></html>");
        tofileend.append(footer);
        file_put_contents("aa.html",tofileend);

}



void QTrlocale::wr_47854g76b64() {

  /*     RangeClass *jobs = new RangeClass();
                                  jobs->wr_47854g76b64();
  *  */

  QStringList langnames;
  QSet < QString > listing = this->qlocaleList();
  /// qDebug() << listing;
  QString dbdump("\n\n\n\n/* Dataprovider to datalanguage.h grep -R \"DATALANGUAGEPROVIDEQT591_H\"  */\nconst LocaleCurrent Rdb_list[] = {    \n");
  QSet < QString >::const_iterator i = listing.constBegin();
  while (i != listing.constEnd()) {
    QString mb37( * i);
    QLocale ax(mb37);
    int sidx = ax.script();
    int dir = ax.textDirection();
    //// int cc = ax.country();
    QString cuba = QLocale::languageToString(ax.language()).toUpper();
    if (!langnames.contains(cuba)) {
        langnames << cuba;
      }

    int idcharslang = idbirthay(cuba);
    QString line = " { " + QString::number(sidx) + " , " + QString::number(dir) + " , \'" + QString(ax.bcp47Name()) + \
      "\' , \'" + cuba + "\' , \'" + QLocale::countryToString(ax.country()) + "\' , " + QString::number((int) ax.language()) + " , " + QString::number(idcharslang) + " }, \r";
    dbdump.append(line);
    ++i;
  }
  dbdump.append("}; \n\n\n");
  qStableSort(langnames.begin(),langnames.end());
  QString languageindex("\n\n\n\n/* Dataprovider to datalanguage.h grep -R \"QTRLOCALE_H\"  */\nconst Localename Rdb_list[] = {    \n");
  for (int x = 0; x < langnames.size(); ++x) {
           const QString langname=langnames.at(x);
           QString nativename, tmp, vline;
           int idcharslang = idbirthay(langname);
           int NUMMERQT = data->qlocaleLanguageIdqt(langname);
           data->get_language_native(NUMMERQT,nativename,tmp); /// tmp is a ocr id.. not need
           if (nativename.size() < 4) { /// not translate native
               vline = " { \'" + langname + "\',\'" + langname.toLower() + "\'," + QString::number(idcharslang) + "," + QString::number(NUMMERQT) + "}, \n ";
             } else {
               vline = " { \'" + langname + "\',\'" + toXexsumm(nativename.toUtf8()) + "\'," + QString::number(idcharslang) + "," + QString::number(NUMMERQT) + "}, \n ";
             }
          languageindex.append(vline);
    }
   dbdump.append(languageindex);
   dbdump.append("}; \n\n\n");
   dbdump.replace(QChar(39),QChar(34)); /// " '
   file_put_contents("rec.cpp",dbdump);
}
