#ifndef DATALANGUAGEPROVIDER_H
#define DATALANGUAGEPROVIDER_H

#include "qtrlocale.h"

static inline int idbirthay( const QString name ) {
    int base = 0;
    int xsize = name.size();
    if (xsize > 10 ) {
        xsize = 10;
      }
    if (name.contains("KAZAKH")) {
        return (int)2018; /// combine on german? /// trink?
      }

    for (int o = 0; o < xsize; o++) {
         const QChar vox(name.at(o));
          const int unico = (int)vox.unicode();
          base +=unico;
      }
  base +=2017; /// on update chance on  grep -R "DATALANGUAGEPROVIDEQT591_H"
  return base;
}

////  { "ENGLISH" , 2539 },
static struct QLANGassociate {
        //// left to right
        const char *language;
        const char *nativelang;
        int lang_key; /// key from the first 10 letter language like md5 to associate on google results also search
        int qt_idx;
    } combinegooglerec[] = {
 { "AFAR","afar",2299,4},
 { "AFRIKAANS","afrikaans",2673,5},
 { "AGHEM","aghem",2371,237},
 { "AKAN","akan",2300,146},
 { "AKOOSE","akoose",2467,312},
 { "ALBANIAN","albanian",2583,6},
 { "AMHARIC","amharic",2518,7},
 { "ARABIC","الْعَرَبيّة",2435,8},
 { "ARMENIAN","armenian",2604,9},
 { "ASSAMESE","assamese",2611,10},
 { "ASTURIAN","asturian",2632,122},
 { "ASU","asu",2250,158},
 { "ATSAM","atsam",2391,156},
 { "AZERBAIJANI","azerbaijani",2744,12},
 { "BAFIA","bafia",2356,243},
 { "BAMBARA","bambara",2503,188},
 { "BASAA","basaa",2361,238},
 { "BASHKIR","bashkir",2533,13},
 { "BASQUE","basque",2466,14},
 { "BELARUSIAN","belarusian",2759,22},
 { "BEMBA","bemba",2360,195},
 { "BENA","bena",2295,186},
 { "BENGALI","bengali",2515,15},
 { "BLIN","blin",2310,152},
 { "BODO","bodo",2309,215},
 { "BOSNIAN","english",2539,31},
 { "BRETON","breton",2475,19},
 { "BULGARIAN","bulgarian",2678,20},
 { "BURMESE","burmese",2548,21},
 { "CANTONESE","cantonese",2689,357},
 { "CATALAN","catalan",2517,24},
 { "CENTRAL KURDISH","kurdish",2730,316},
 { "CENTRAL MOROCCO TAMAZIGHT","central morocco tamazight",2726,212},
 { "CHECHEN","chechen",2511,218},
 { "CHEROKEE","cherokee",2599,190},
 { "CHIGA","chiga",2365,211},
 { "CHINESE","汉语",2528,25},
 { "CHURCH","church",2462,169},
 { "CHUVASH","chuvash",2547,220},
 { "COLOGNIAN","colognian",2683,201},
 { "CORNISH","castellà",2551,111},
 { "CORSICAN","corsican",2611,10},
 { "CROATIAN","croatian",2610,27},
 { "CZECH","čeština",2382,28},
 { "DANISH","dansk",2456,29},
 { "DIVEHI","divehi",2458,143},
 { "DUALA","duala",2376,240},
 { "DUTCH","Nederlands",2393,30},
 { "DZONGKHA","dzongkha",2615,16},
 { "EMBU","embu",2314,189},
 { "ENGLISH","english",2539,31},
 { "ESTONIAN","estonian",2626,33},
 { "EWE","ewe",2242,161},
 { "EWONDO","ewondo",2477,124},
 { "FAROESE","faroese",2534,34},
 { "FILIPINO","filipino",2619,166},
 { "FINNISH","suomi",2544,36},
 { "FRENCH","français",2455,37},
 { "FRIULIAN","friulian",2619,166},
 { "FULAH","fulah",2385,177},
 { "GA","ga",2153,148},
 { "GAELIC","gaelic",2438,39},
 { "GALICIAN","galician",2585,40},
 { "GANDA","ganda",2364,194},
 { "GEEZ","geez",2316,153},
 { "GEORGIAN","georgian",2605,41},
 { "GERMAN","Deusch",2459,42},
 { "GREEK","ελληνική",2383,43},
 { "GREENLANDIC","greenlandic",2746,44},
 { "GUARANI","guarani",2536,121},
 { "GUJARATI","gujarati",2616,46},
 { "GUSII","gusii",2402,131},
 { "HAUSA","hausa",2387,47},
 { "HAWAIIAN","hawaiian",2595,163},
 { "HEBREW","hebrew",2462,169},
 { "HINDI","हिन्दी",2381,49},
 { "HUNGARIAN","Magyar",2686,50},
 { "ICELANDIC","icelandic",2653,51},
 { "IGBO","igbo",2306,149},
 { "INARI SAMI","inari sami",2718,326},
 { "INDONESIAN","bahasa Indonesia",2761,52},
 { "INTERLINGUA","interlingua",2786,53},
 { "INUKTITUT","inuktitut",2738,55},
 { "IRISH","irish",2400,57},
 { "ITALIAN","italiano",2531,58},
 { "JAPANESE","日本語",2600,59},
 { "JAVANESE","javanese",2606,60},
 { "JJU","jju",2250,158},
 { "JOLAFONYI","jolafonyi",2700,241},
 { "KABUVERDIANU","kabuverdianu",2751,196},
 { "KABYLE","kabyle",2457,184},
 { "KAKO","ภาษาไทย",2311,120},
 { "KALENJIN","kalenjin",2605,41},
 { "KAMBA","kamba",2365,211},
 { "KANNADA","kannada",2511,218},
 { "KASHMIRI","kashmiri",2617,62},
 { "KAZAKH","kazakh",2018,63},
 { "KENYANG","kenyang",2542,319},
 { "KHMER","khmer",2392,117},
 { "KICHE","kiche",2373,323},
 { "KIKUYU","kikuyu",2499,178},
 { "KINYARWANDA","kinyarwanda",2777,141},
 { "KIRGHIZ","kirghiz",2553,65},
 { "KONKANI","konkani",2540,147},
 { "KOREAN","한국어",2465,66},
 { "KOYRA CHIINI","koyra chiini",2724,208},
 { "KOYRABORO SENNI","koyraboro senni",2745,213},
 { "KPELLE","kpelle",2462,169},
 { "KURDISH","kurdish",2555,67},
 { "KWASIO","kwasio",2479,103},
 { "LAKOTA","lakota",2461,313},
 { "LANGI","langi",2380,202},
 { "LAO","lao",2237,69},
 { "LATVIAN","suomi",2544,36},
 { "LINGALA","lingala",2521,72},
 { "LITHUANIAN","lithuanian",2766,73},
 { "LOW GERMAN","low german",2733,171},
 { "LOWERSORBIAN","lowersorbian",2793,317},
 { "LUBAKATANGA","lubakatanga",2747,230},
 { "LULE SAMI","lule sami",2653,51},
 { "LUO","luo",2257,210},
 { "LUXEMBOURGISH","luxembourgish",2795,231},
 { "LUYIA","luyia",2405,204},
 { "MACEDONIAN","macedonian",2736,74},
 { "MACHAME","machame",2509,200},
 { "MAKHUWAMEETTO","makhuwameetto",2758,244},
 { "MAKONDE","汉语",2528,25},
 { "MALAGASY","malagasy",2608,75},
 { "MALAY","malay",2389,76},
 { "MALAYALAM","malayalam",2672,77},
 { "MALTESE","maltese",2540,147},
 { "MANX","manx",2325,144},
 { "MAORI","Nederlands",2393,30},
 { "MAPUCHE","mapuche",2532,315},
 { "MARATHI","marathi",2535,80},
 { "MASAI","masai",2380,202},
 { "MAZANDERANI","mazanderani",2754,346},
 { "MERU","meru",2330,197},
 { "META","meta",2312,180},
 { "MOHAWK","mohawk",2472,123},
 { "MONGOLIAN","mongolian",2693,82},
 { "MORISYEN","morisyen",2647,191},
 { "MUNDANG","english",2539,31},
 { "NAMA","nama",2302,199},
 { "NEPALI","nepali",2458,143},
 { "NGIEMBOON","ngiemboon",2687,260},
 { "NGOMBA","ngomba",2453,257},
 { "NKO","nko",2249,321},
 { "NORTH NDEBELE","north ndebele",2725,181},
 { "NORTHERN LURI","northern luri",2749,349},
 { "NORTHERN SAMI","northern sami",2756,173},
 { "NORTHERN SOTHO","northern sotho",2756,173},
 { "NORWEGIANBOKMAL","norsk",2765,85},
 { "NORWEGIANNYNORSK","norsk",2777,141},
 { "NUER","nuer",2331,247},
 { "NYANJA","nyanja",2466,14},
 { "NYANKOLE","nyankole",2626,33},
 { "OCCITAN","occitan",2530,86},
 { "ORIYA","oriya",2405,204},
 { "OROMO","oromo",2413,3},
 { "OSSETIC","ossetic",2555,67},
 { "PASHTO","polski",2480,90},
 { "PERSIAN","persian",2547,220},
 { "POLISH","polski",2480,90},
 { "PORTUGUESE","português",2804,91},
 { "PUNJABI","punjabi",2538,92},
 { "QUECHUA","quechua",2541,93},
 { "ROMANIAN","română",2614,95},
 { "ROMANSH","romansh",2553,65},
 { "ROMBO","rombo",2400,57},
 { "RUNDI","rundi",2403,68},
 { "RUSSIAN","ру́сский",2566,96},
 { "RWA","rwa",2251,209},
 { "SAHO","saho",2316,153},
 { "SAKHA","sakha",2377,248},
 { "SAMBURU","samburu",2560,179},
 { "SANGO","Nederlands",2393,30},
 { "SANGU","sangu",2399,249},
 { "SANSKRIT","sanskrit",2640,99},
 { "SENA","sena",2312,180},
 { "SERBIAN","serbian",2533,13},
 { "SHAMBALA","shambala",2586,214},
 { "SHONA","shona",2394,104},
 { "SICHUAN YI","sichuan yi",2734,168},
 { "SIDAMO","sidamo",2462,169},
 { "SINDHI","sindhi",2464,105},
 { "SINHALA","sinhala",2529,106},
 { "SKOLT SAMI","skolt sami",2744,12},
 { "SLOVAK","slovak",2481,174},
 { "SLOVENIAN","slovenian",2704,109},
 { "SOGA","soga",2315,203},
 { "SOMALI","somali",2470,110},
 { "SOUTH NDEBELE","south ndebele",2733,171},
 { "SOUTHERN SAMI","southern sami",2764,324},
 { "SOUTHERN SOTHO","southern sotho",2764,324},
 { "SPANISH","castellà",2551,111},
 { "STANDARD MOROCCAN TAMAZIGHT","moroccan tamazight",2719,314},
 { "SWAHILI","swahili",2546,113},
 { "SWATI","swati",2409,107},
 { "SWEDISH","svenska",2552,114},
 { "SWISS GERMAN","schwiizerdütsch",2757,167},
 { "SYRIAC","syriac",2476,151},
 { "TACHELHIT","tachelhit",2679,183},
 { "TAITA","taita",2388,176},
 { "TAJIK","tajik",2388,176},
 { "TAMIL","tamil",2392,117},
 { "TAROKO","taroko",2481,174},
 { "TASAWAQ","tasawaq",2547,220},
 { "TATAR","tatar",2397,118},
 { "TELUGU","telugu",2487,119},
 { "TESO","teso",2332,206},
 { "THAI","ภาษาไทย",2311,120},
 { "TIBETAN","tibetan",2536,121},
 { "TIGRE","tigre",2396,157},
 { "TIGRINYA","tigrinya",2632,122},
 { "TONGAN","tongan",2472,123},
 { "TSONGA","tsonga",2477,124},
 { "TSWANA","tswana",2479,103},
 { "TURKISH","Türkçe",2571,125},
 { "TURKMEN","turkmen",2567,126},
 { "TYAP","tyap",2335,164},
 { "UIGHUR","uighur",2485,128},
 { "UKRAINIAN","ukrainian",2691,129},
 { "UPPERSORBIAN","uppersorbian",2796,318},
 { "URDU","urdu",2337,130},
 { "UZBEK","uzbek",2402,131},
 { "VAI","vai",2241,252},
 { "VENDA","ελληνική",2383,43},
 { "VIETNAMESE","vietnamese",2770,132},
 { "VUNJO","vunjo",2419,187},
 { "WALAMO","walamo",2466,14},
 { "WALLOON","walloon",2557,236},
 { "WALSER","walser",2479,103},
 { "WARLPIRI","warlpiri",2635,328},
 { "WELSH","welsh",2404,134},
 { "WESTERN FRISIAN","western frisian",2753,38},
 { "WOLOF","wolof",2408,135},
 { "XHOSA","xhosa",2404,134},
 { "YANGBEN","yangben",2533,13},
 { "YORUBA","yoruba",2483,138},
 { "ZARMA","zarma",2396,157},
 { "ZULU","zulu",2353,140},
 };




class DataLocaleProvider
{
public:
  DataLocaleProvider() {};
  QLocale qlocaleFromLanguageUnique( const QString lang);
  QString getLanguageNameForScript( const int nr );
  QStringList getCountryNameForScript( const int nr );
  QStringList getCountryNamefromLanguage( QString lang );
  QStringList getidlocaleidForScript( const int nr  );  //// to build QLocale
  QList<QLocale> qlocaleFromLanguage( const QString lang);
  /// id from QLocale .. int nr = (int)locale.language()

  int qlocaleLanguageIdqt( const QString lang);
  void get_language_native(int id , QString & nt  , QString & ctess );
  private:
};

















#endif // DATALANGUAGEPROVIDER_H
