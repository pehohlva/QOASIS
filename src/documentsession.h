#ifndef DOCUMENTSESSIONPHPIDNUMC23765H
#define DOCUMENTSESSIONPHPIDNUMC23765H

#include <QObject>
#include <QtGui>
#include <QDebug>
#include <QApplication>
#include <QtGui>
#include <QtCore>
#include <QAbstractSocket>
#include <QFileInfo>
#include <QUrl>
#include <QTimer>
#include <QDomElement>
//// #include <stdio.h>


/* not export if is a lib! this is only a bridge from app to documnts  */
/// RTF & RTFD- Rich Text Format

static inline QString FileFilterHaving()
{
  QString filter;
  filter = "";
  /// filter += QString( "FOP file" ) + " (*.fop *.fop.gz *.fo *.fo.gz *.xml);;";
  //// filter+= QString( "MiniScribus binary stream file" ) + " (*.page);;";
  filter+= QString( "OpenOffice 1.1 file format" ) + " (*.sxw *.stw);;";
  filter+= QString( "OpenOffice 2.4 file format" ) + " (*.odt *.ott);;";
  filter+= QString( "RichText Format " ) + " (*.rtf *.rtfd);;";
  filter+= QString( "XHTML file format" ) + " (*.htm *.html);;";
  //////filter += ")";
  return filter;
}



#define _BG_CHAR_ALPHA_  425
#define _TXT_CHAR_ALPHA_  424


#define POINT_TO_CM(cm) ((cm)/28.3465058)
#define POINT_TO_MM(mm) ((mm)/2.83465058)     ////////  0.352777778
#define POINT_TO_DM(dm) ((dm)/283.465058)
#define POINT_TO_INCH(inch) ((inch)/72.0)
#define POINT_TO_PI(pi) ((pi)/12)
#define POINT_TO_DD(dd) ((dd)/154.08124)
#define POINT_TO_CC(cc) ((cc)/12.840103)
////------------------------------------
#define MM_TO_POINT(mm) ((mm)*2.83465058)
#define CM_TO_POINT(cm) ((cm)*28.3465058)     ///// 28.346456693
#define DM_TO_POINT(dm) ((dm)*283.465058)
#define INCH_TO_POINT(inch) ((inch)*72.0)
#define PI_TO_POINT(pi) ((pi)*12)
#define DD_TO_POINT(dd) ((dd)*154.08124)
#define CC_TO_POINT(cc) ((cc)*12.840103)

static const int InterSpace = 15;  /* distance from page 1 to 2 */
static const int SliderTopHeight = 28;
static const int SliderLeftHeight = 28;
static const int MaximumPages = 99;
static const int BorderShadow = 5;
static const qreal FrameMarginBottomBugDraw = 2.8;
static const int DocumentBugSpace = 15;
static const int ObjectName = 853;
static const int FlashReferenceID = 322;
static const int TextFloatObjectName = 20;
static const int FooterHeaderPadding = 2;
static const int FooterHeaderMaxBlocks = 3;

#define _PAGE_NUMERATION_ \
             QString("#Page#")



class DocSession {
public:
        static DocSession* instance();
  ~DocSession();


  inline QMap<int,M_PageSize> mpages() { return history_page_norms; }
  bool coreSave( M_PageSize e );   /* to restore original from dlg pageformat */
   M_PageSize FindPagePsize( const QRect paper );
  void AppendPaper( M_PageSize cur , bool enableregion = false );
  bool is_OnChain( M_PageSize e );
  inline QStringList  FontList() { return FF_db.families(); }
  inline M_PageSize CurrentPageFormat() { return current_Page_Format; }
  inline void SetPageFormat( M_PageSize e ) { current_Page_Format = e; }
  inline QMap<QString, int> uniqueID() const { return uniqueid; }
  QString validateUnique( const QString idkei );
  bool validKey( const QString idkei ) const;
  void clearKey();

  qreal maximumPage();
    QPrinter *pdev;
    ///QRectF SceneViewPort;
    int CurrentDocWidth;
    QMap<int,QString> LastCharOpen;
    QMap<QString,QByteArray> saveImageFile;
    QMap<int,QString> LastBlockOpen;
    QMap<QString,QByteArray> SvgList;
    QMap<int,QPicture> pagecache;  /* cache pages images */
    QMap<int,QMimeData*> mime_story;
    //// QMap<QString,SPics> ImagePageList;   /* image on all documents cache */
    QSettings setter;
    int SessionID;
    M_PageSize current_Page_Format;
    QByteArray bokMarkDom;


private:
  DocSession();
  QMap<QString, int> uniqueid;
  static DocSession* st_;
  void FormatRegister( const QString txt , QPrinter::PageSize pp );
  QFontDatabase FF_db;
  QMap<int,M_PageSize> history_page_norms;

};








#endif // DOCUMENTSESSION_H
