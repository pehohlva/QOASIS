

INCLUDEPATH +=$$PWD/docx/export  $$PWD/docx/import ../xml
DEPENDPATH +=$$PWD/docx/export  $$PWD/docx/import ../xml

# Input
HEADERS += $$PWD/docx/export/DocxExport.h \
           $$PWD/docx/export/DocxExportDebug.h \
           $$PWD/docx/export/DocxFile.h \
           $$PWD/docx/export/DocxStyleHelper.h \
           $$PWD/docx/export/DocxStyleWriter.h \
           $$PWD/docx/export/FileCollector.h \
           $$PWD/docx/export/OdfReaderDocxContext.h \
           $$PWD/docx/export/OdfTextReaderDocxBackend.h \
           $$PWD/docx/export/OdtReaderDocxBackend.h \
           $$PWD/docx/export/OpcContentTypes.h \
           $$PWD/docx/export/OpcRelSet.h \
           $$PWD/docx/export/OpcRelSetManager.h \
           $$PWD/docx/export/UnitConversions.h \
           $$PWD/docx/import/DocxDebug.h \
           $$PWD/docx/import/DocxImport.h \
           $$PWD/docx/import/DocxXmlCommentsReader.h \
           $$PWD/docx/import/DocxXmlDocumentReader.h \
           $$PWD/docx/import/DocxXmlEndnoteReader.h \
           $$PWD/docx/import/DocxXmlFontTableReader.h \
           $$PWD/docx/import/DocxXmlFooterReader.h \
           $$PWD/docx/import/DocxXmlFootnoteReader.h \
           $$PWD/docx/import/DocxXmlHeaderReader.h \
           $$PWD/docx/import/DocxXmlNumberingReader.h \
           $$PWD/docx/import/DocxXmlSettingsReader.h \
           $$PWD/docx/import/DocxXmlStylesReader.h
SOURCES += $$PWD/docx/export/DocxExport.cpp \
           $$PWD/docx/export/DocxExportDebug.cpp \
           $$PWD/docx/export/DocxFile.cpp \
           $$PWD/docx/export/DocxStyleHelper.cpp \
           $$PWD/docx/export/DocxStyleWriter.cpp \
           $$PWD/docx/export/FileCollector.cpp \
           $$PWD/docx/export/OdfReaderDocxContext.cpp \
           $$PWD/docx/export/OdfTextReaderDocxBackend.cpp \
           $$PWD/docx/export/OdtReaderDocxBackend.cpp \
           $$PWD/docx/export/OpcContentTypes.cpp \
           $$PWD/docx/export/OpcRelSet.cpp \
           $$PWD/docx/export/OpcRelSetManager.cpp \
           $$PWD/docx/export/UnitConversions.cpp \
           $$PWD/docx/import/DocxDebug.cpp \
           $$PWD/docx/import/DocxImport.cpp \
           $$PWD/docx/import/DocxXmlCommentsReader.cpp \
           $$PWD/docx/import/DocxXmlDocumentReader.cpp \
           $$PWD/docx/import/DocxXmlEndnoteReader.cpp \
           $$PWD/docx/import/DocxXmlFontTableReader.cpp \
           $$PWD/docx/import/DocxXmlFooterReader.cpp \
           $$PWD/docx/import/DocxXmlFootnoteReader.cpp \
           $$PWD/docx/import/DocxXmlHeaderReader.cpp \
           $$PWD/docx/import/DocxXmlNumberingReader.cpp \
           $$PWD/docx/import/DocxXmlSettingsReader.cpp \
           $$PWD/docx/import/DocxXmlStylesReader.cpp \
           $$PWD/docx/import/OkularDocxGeneratorPlugin.cpp
