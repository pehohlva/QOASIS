#include "datalanguageprovider.h"


/// use function in lib ony this 2 file
#include "compact_lang_det.h"
#include "encodings.h"
/// use function in lib ony this 2 file

static inline QString QTUTF8decode( const char* t ) {
   //// qWarning() << "Not secure here!." << __FUNCTION__<<":" <<  __FILE__ << ":" << __LINE__;
   return QObject::trUtf8(t);
}

/* find nummer in a vector
  https://stackoverflow.com/questions/5917877/how-to-use-find-algorithm-for-a-vector */


/* enum struct 2kb database
 * Generated from RangeClass to by go fast to have results not excel only system pointer
 * Dataprovider to datalanguage.h grep -R "DATALANGUAGEPROVIDEQT591_H"  */
struct QLocale2017 {
        //// left to right
        int scr_id; //// script from qchar <-> qlocale
        int write_direction; //// how to write...
        const char *bcp47name; //// QLocale loc(bcp47name); /// to init fast a Qlocale
        const char *language;
        const char *country;
        int index_language; /// qt number
        int lang_key; /// key from the first 10 letter language to associate on google results also search
    } combinelist[] = {
{ 1 , 1 , "ar" , "ARABIC" , "Egypt" , 8 , 2435 },
{ 11 , 0 , "as" , "ASSAMESE" , "India" , 10 , 2611 },
{ 7 , 0 , "en-ZM" , "ENGLISH" , "Zambia" , 31 , 2539 },
{ 7 , 0 , "az" , "AZERBAIJANI" , "Azerbaijan" , 12 , 2744 },
{ 7 , 0 , "en-ZW" , "ENGLISH" , "Zimbabwe" , 31 , 2539 },
{ 2 , 0 , "ba" , "BASHKIR" , "Russia" , 13 , 2533 },
{ 2 , 0 , "be" , "BELARUSIAN" , "Belarus" , 22 , 2759 },
{ 2 , 0 , "bg" , "BULGARIAN" , "Bulgaria" , 20 , 2678 },
{ 7 , 0 , "ff-GN" , "FULAH" , "Guinea" , 177 , 2385 },
{ 7 , 0 , "nus" , "NUER" , "SouthSudan" , 247 , 2331 },
{ 14 , 0 , "gez" , "GEEZ" , "Ethiopia" , 153 , 2316 },
{ 7 , 0 , "bm" , "BAMBARA" , "Mali" , 188 , 2503 },
{ 11 , 0 , "bn" , "BENGALI" , "Bangladesh" , 15 , 2515 },
{ 31 , 0 , "bo" , "TIBETAN" , "China" , 121 , 2536 },
{ 7 , 0 , "fr-PF" , "FRENCH" , "FrenchPolynesia" , 37 , 2455 },
{ 1 , 1 , "uz-AF" , "UZBEK" , "Afghanistan" , 131 , 2402 },
{ 7 , 0 , "br" , "BRETON" , "France" , 19 , 2475 },
{ 7 , 0 , "bs" , "BOSNIAN" , "BosniaAndHerzegowina" , 142 , 2539 },
{ 7 , 0 , "fr-PM" , "FRENCH" , "SaintPierreAndMiquelon" , 37 , 2455 },
{ 7 , 0 , "gsw-FR" , "SWISS GERMAN" , "France" , 167 , 2757 },
{ 7 , 0 , "da-GL" , "DANISH" , "Greenland" , 29 , 2456 },
{ 13 , 0 , "kok" , "KONKANI" , "India" , 147 , 2540 },
{ 7 , 0 , "jmc" , "MACHAME" , "Tanzania" , 200 , 2509 },
{ 7 , 0 , "ca" , "CATALAN" , "Spain" , 24 , 2517 },
{ 7 , 0 , "ha-GH" , "HAUSA" , "Ghana" , 47 , 2387 },
{ 2 , 0 , "ce" , "CHECHEN" , "Russia" , 218 , 2511 },
{ 6 , 0 , "zh-MO" , "CHINESE" , "Macau" , 25 , 2528 },
{ 1 , 1 , "lrc" , "NORTHERN LURI" , "Iran" , 349 , 2749 },
{ 7 , 0 , "co" , "CORSICAN" , "France" , 26 , 2611 },
{ 2 , 0 , "sr-XK" , "SERBIAN" , "Kosovo" , 100 , 2533 },
{ 1 , 1 , "ar-IL" , "ARABIC" , "Israel" , 8 , 2435 },
{ 7 , 0 , "cs" , "CZECH" , "CzechRepublic" , 28 , 2382 },
{ 7 , 0 , "kpe" , "KPELLE" , "Liberia" , 169 , 2462 },
{ 2 , 0 , "cu" , "CHURCH" , "Russia" , 219 , 2462 },
{ 2 , 0 , "cv" , "CHUVASH" , "Russia" , 220 , 2547 },
{ 7 , 0 , "ebu" , "EMBU" , "Kenya" , 189 , 2314 },
{ 1 , 1 , "ar-IQ" , "ARABIC" , "Iraq" , 8 , 2435 },
{ 7 , 0 , "cy" , "WELSH" , "UnitedKingdom" , 134 , 2404 },
{ 7 , 0 , "shi-Latn" , "TACHELHIT" , "Morocco" , 183 , 2679 },
{ 2 , 0 , "sah" , "SAKHA" , "Russia" , 248 , 2377 },
{ 7 , 0 , "mua" , "MUNDANG" , "Cameroon" , 245 , 2539 },
{ 7 , 0 , "da" , "DANISH" , "Denmark" , 29 , 2456 },
{ 7 , 0 , "de" , "GERMAN" , "Germany" , 42 , 2459 },
{ 1 , 1 , "ms-Arab" , "MALAY" , "Malaysia" , 76 , 2389 },
{ 7 , 0 , "saq" , "SAMBURU" , "Kenya" , 179 , 2560 },
{ 7 , 0 , "pt-GQ" , "PORTUGUESE" , "EquatorialGuinea" , 91 , 2804 },
{ 7 , 0 , "fr-RE" , "FRENCH" , "Reunion" , 37 , 2455 },
{ 7 , 0 , "pt-GW" , "PORTUGUESE" , "GuineaBissau" , 91 , 2804 },
{ 1 , 1 , "ar-JO" , "ARABIC" , "Jordan" , 8 , 2435 },
{ 29 , 1 , "dv" , "DIVEHI" , "Maldives" , 143 , 2458 },
{ 7 , 0 , "sv-FI" , "SWEDISH" , "Finland" , 114 , 2552 },
{ 7 , 0 , "ca-AD" , "CATALAN" , "Andorra" , 24 , 2517 },
{ 7 , 0 , "es-MX" , "SPANISH" , "Mexico" , 111 , 2551 },
{ 31 , 0 , "dz" , "DZONGKHA" , "Bhutan" , 16 , 2615 },
{ 7 , 0 , "dav" , "TAITA" , "Kenya" , 176 , 2388 },
{ 7 , 0 , "fr-RW" , "FRENCH" , "Rwanda" , 37 , 2455 },
{ 7 , 0 , "hr-BA" , "CROATIAN" , "BosniaAndHerzegowina" , 27 , 2610 },
{ 7 , 0 , "ee" , "EWE" , "Ghana" , 161 , 2242 },
{ 7 , 0 , "sbp" , "SANGU" , "Tanzania" , 249 , 2399 },
{ 7 , 0 , "es-NI" , "SPANISH" , "Nicaragua" , 111 , 2551 },
{ 16 , 0 , "el" , "GREEK" , "Greece" , 43 , 2383 },
{ 7 , 0 , "fr-SC" , "FRENCH" , "Seychelles" , 37 , 2455 },
{ 1 , 1 , "ur-IN" , "URDU" , "India" , 130 , 2337 },
{ 7 , 0 , "en" , "ENGLISH" , "UnitedStates" , 31 , 2539 },
{ 7 , 0 , "es" , "SPANISH" , "Spain" , 111 , 2551 },
{ 1 , 1 , "ar-KM" , "ARABIC" , "Comoros" , 8 , 2435 },
{ 7 , 0 , "et" , "ESTONIAN" , "Estonia" , 33 , 2626 },
{ 7 , 0 , "eu" , "BASQUE" , "Spain" , 14 , 2466 },
{ 7 , 0 , "fr-SN" , "FRENCH" , "Senegal" , 37 , 2455 },
{ 31 , 0 , "bo-IN" , "TIBETAN" , "India" , 121 , 2536 },
{ 1 , 1 , "lrc-IQ" , "NORTHERN LURI" , "Iraq" , 349 , 2749 },
{ 7 , 0 , "teo" , "TESO" , "Uganda" , 206 , 2332 },
{ 1 , 1 , "ar-KW" , "ARABIC" , "Kuwait" , 8 , 2435 },
{ 1 , 1 , "fa" , "PERSIAN" , "Iran" , 89 , 2547 },
{ 7 , 0 , "fr-SY" , "FRENCH" , "Syria" , 37 , 2455 },
{ 7 , 0 , "sw-KE" , "SWAHILI" , "Kenya" , 113 , 2546 },
{ 7 , 0 , "nyn" , "NYANKOLE" , "Uganda" , 185 , 2626 },
{ 7 , 0 , "ff" , "FULAH" , "Senegal" , 177 , 2385 },
{ 1 , 1 , "ar-LB" , "ARABIC" , "Lebanon" , 8 , 2435 },
{ 5 , 0 , "zh-Hans-MO" , "CHINESE" , "Macau" , 25 , 2528 },
{ 7 , 0 , "fi" , "FINNISH" , "Finland" , 36 , 2544 },
{ 7 , 0 , "fr-TD" , "FRENCH" , "Chad" , 37 , 2455 },
{ 7 , 0 , "fo" , "FAROESE" , "FaroeIslands" , 34 , 2534 },
{ 7 , 0 , "fr-TG" , "FRENCH" , "Togo" , 37 , 2455 },
{ 7 , 0 , "ksb" , "SHAMBALA" , "Tanzania" , 214 , 2586 },
{ 7 , 0 , "fr" , "FRENCH" , "France" , 37 , 2455 },
{ 7 , 0 , "xog" , "SOGA" , "Uganda" , 203 , 2315 },
{ 7 , 0 , "ksf" , "BAFIA" , "Cameroon" , 243 , 2356 },
{ 7 , 0 , "luo" , "LUO" , "Kenya" , 210 , 2257 },
{ 7 , 0 , "fr-TN" , "FRENCH" , "Tunisia" , 37 , 2455 },
{ 7 , 0 , "ksh" , "COLOGNIAN" , "Germany" , 201 , 2683 },
{ 7 , 0 , "fy" , "WESTERN FRISIAN" , "Netherlands" , 38 , 2753 },
{ 7 , 0 , "sq-XK" , "ALBANIAN" , "Kosovo" , 6 , 2583 },
{ 1 , 1 , "ar-LY" , "ARABIC" , "Libya" , 8 , 2435 },
{ 7 , 0 , "ga" , "IRISH" , "Ireland" , 57 , 2400 },
{ 7 , 0 , "luy" , "LUYIA" , "Kenya" , 204 , 2405 },
{ 7 , 0 , "es-PA" , "SPANISH" , "Panama" , 111 , 2551 },
{ 7 , 0 , "gd" , "GAELIC" , "UnitedKingdom" , 39 , 2438 },
{ 7 , 0 , "es-PE" , "SPANISH" , "Peru" , 111 , 2551 },
{ 1 , 1 , "ar-MA" , "ARABIC" , "Morocco" , 8 , 2435 },
{ 7 , 0 , "es-PH" , "SPANISH" , "Philippines" , 111 , 2551 },
{ 7 , 0 , "it-SM" , "ITALIAN" , "SanMarino" , 58 , 2531 },
{ 7 , 0 , "om-KE" , "OROMO" , "Kenya" , 3 , 2413 },
{ 7 , 0 , "gl" , "GALICIAN" , "Spain" , 40 , 2585 },
{ 7 , 0 , "gn" , "GUARANI" , "Paraguay" , 45 , 2536 },
{ 7 , 0 , "es-PR" , "SPANISH" , "PuertoRico" , 111 , 2551 },
{ 17 , 0 , "gu" , "GUJARATI" , "India" , 46 , 2616 },
{ 7 , 0 , "gv" , "MANX" , "IsleOfMan" , 144 , 2325 },
{ 1 , 1 , "ar-MR" , "ARABIC" , "Mauritania" , 8 , 2435 },
{ 14 , 0 , "ti-ER" , "TIGRINYA" , "Eritrea" , 122 , 2632 },
{ 7 , 0 , "es-PY" , "SPANISH" , "Paraguay" , 111 , 2551 },
{ 7 , 0 , "seh" , "SENA" , "Mozambique" , 180 , 2312 },
{ 1 , 1 , "ha-Arab" , "HAUSA" , "Nigeria" , 47 , 2387 },
{ 7 , 0 , "tr-CY" , "TURKISH" , "Cyprus" , 125 , 2571 },
{ 7 , 0 , "ha" , "HAUSA" , "Nigeria" , 47 , 2387 },
{ 18 , 1 , "he" , "HEBREW" , "Israel" , 48 , 2462 },
{ 7 , 0 , "fil" , "FILIPINO" , "Philippines" , 166 , 2619 },
{ 13 , 0 , "hi" , "HINDI" , "India" , 49 , 2381 },
{ 7 , 0 , "ses" , "KOYRABORO SENNI" , "Mali" , 213 , 2745 },
{ 7 , 0 , "gsw-LI" , "SWISS GERMAN" , "Liechtenstein" , 167 , 2757 },
{ 7 , 0 , "ff-MR" , "FULAH" , "Mauritania" , 177 , 2385 },
{ 13 , 0 , "ne-IN" , "NEPALI" , "India" , 84 , 2458 },
{ 7 , 0 , "hr" , "CROATIAN" , "Croatia" , 27 , 2610 },
{ 7 , 0 , "hu" , "HUNGARIAN" , "Hungary" , 50 , 2686 },
{ 10 , 0 , "hy" , "ARMENIAN" , "Armenia" , 9 , 2604 },
{ 7 , 0 , "cch" , "ATSAM" , "Nigeria" , 156 , 2391 },
{ 5 , 0 , "zh-SG" , "CHINESE" , "Singapore" , 25 , 2528 },
{ 7 , 0 , "fr-VU" , "FRENCH" , "Vanuatu" , 37 , 2455 },
{ 7 , 0 , "ia" , "INTERLINGUA" , "France" , 53 , 2786 },
{ 7 , 0 , "yo-BJ" , "YORUBA" , "Benin" , 138 , 2483 },
{ 7 , 0 , "id" , "INDONESIAN" , "Indonesia" , 52 , 2761 },
{ 1 , 1 , "az-IR" , "AZERBAIJANI" , "Iran" , 12 , 2744 },
{ 7 , 0 , "ig" , "IGBO" , "Nigeria" , 149 , 2306 },
{ 27 , 0 , "ta-LK" , "TAMIL" , "SriLanka" , 117 , 2392 },
{ 34 , 0 , "ii" , "SICHUAN YI" , "China" , 168 , 2734 },
{ 11 , 0 , "bn-IN" , "BENGALI" , "India" , 15 , 2515 },
{ 7 , 0 , "bas" , "BASAA" , "Cameroon" , 238 , 2361 },
{ 1 , 1 , "mzn" , "MAZANDERANI" , "Iran" , 346 , 2754 },
{ 7 , 0 , "fr-WF" , "FRENCH" , "WallisAndFutunaIslands" , 37 , 2455 },
{ 7 , 0 , "pt-LU" , "PORTUGUESE" , "Luxembourg" , 91 , 2804 },
{ 1 , 1 , "ar-OM" , "ARABIC" , "Oman" , 8 , 2435 },
{ 7 , 0 , "is" , "ICELANDIC" , "Iceland" , 51 , 2653 },
{ 7 , 0 , "it" , "ITALIAN" , "Italy" , 58 , 2531 },
{ 14 , 0 , "tig" , "TIGRE" , "Eritrea" , 157 , 2396 },
{ 7 , 0 , "nl-AW" , "DUTCH" , "Aruba" , 30 , 2393 },
{ 44 , 0 , "iu" , "INUKTITUT" , "Canada" , 55 , 2738 },
{ 7 , 0 , "en-AG" , "ENGLISH" , "AntiguaAndBarbuda" , 31 , 2539 },
{ 7 , 0 , "en-AI" , "ENGLISH" , "Anguilla" , 31 , 2539 },
{ 7 , 0 , "ha-NE" , "HAUSA" , "Niger" , 47 , 2387 },
{ 19 , 0 , "ja" , "JAPANESE" , "Japan" , 59 , 2600 },
{ 7 , 0 , "en-AS" , "ENGLISH" , "AmericanSamoa" , 31 , 2539 },
{ 7 , 0 , "nl-BE" , "DUTCH" , "Belgium" , 30 , 2393 },
{ 7 , 0 , "en-AT" , "ENGLISH" , "Austria" , 31 , 2539 },
{ 7 , 0 , "en-AU" , "ENGLISH" , "Australia" , 31 , 2539 },
{ 7 , 0 , "ca-FR" , "CATALAN" , "France" , 24 , 2517 },
{ 6 , 0 , "yue" , "CANTONESE" , "HongKong" , 357 , 2689 },
{ 7 , 0 , "pt-MO" , "PORTUGUESE" , "Macau" , 91 , 2804 },
{ 7 , 0 , "se-SE" , "NORTHERN SAMI" , "Sweden" , 173 , 2756 },
{ 6 , 0 , "zh-TW" , "CHINESE" , "Taiwan" , 25 , 2528 },
{ 7 , 0 , "nl-BQ" , "DUTCH" , "Bonaire" , 30 , 2393 },
{ 7 , 0 , "en-BB" , "ENGLISH" , "Barbados" , 31 , 2539 },
{ 7 , 0 , "en-BE" , "ENGLISH" , "Belgium" , 31 , 2539 },
{ 7 , 0 , "jv" , "JAVANESE" , "Indonesia" , 60 , 2606 },
{ 27 , 0 , "ta-MY" , "TAMIL" , "Malaysia" , 117 , 2392 },
{ 7 , 0 , "pt-MZ" , "PORTUGUESE" , "Mozambique" , 91 , 2804 },
{ 7 , 0 , "es-SV" , "SPANISH" , "ElSalvador" , 111 , 2551 },
{ 7 , 0 , "en-BI" , "ENGLISH" , "Burundi" , 31 , 2539 },
{ 1 , 1 , "ar-PS" , "ARABIC" , "PalestinianTerritories" , 8 , 2435 },
{ 7 , 0 , "en-BM" , "ENGLISH" , "Bermuda" , 31 , 2539 },
{ 7 , 0 , "ro-MD" , "ROMANIAN" , "Moldova" , 95 , 2614 },
{ 7 , 0 , "ms-SG" , "MALAY" , "Singapore" , 76 , 2389 },
{ 9 , 0 , "shi" , "TACHELHIT" , "Morocco" , 183 , 2679 },
{ 15 , 0 , "ka" , "GEORGIAN" , "Georgia" , 41 , 2605 },
{ 7 , 0 , "sr-Latn-BA" , "SERBIAN" , "BosniaAndHerzegowina" , 100 , 2533 },
{ 7 , 0 , "en-BS" , "ENGLISH" , "Bahamas" , 31 , 2539 },
{ 1 , 1 , "ar-QA" , "ARABIC" , "Qatar" , 8 , 2435 },
{ 7 , 0 , "en-BW" , "ENGLISH" , "Botswana" , 31 , 2539 },
{ 7 , 0 , "ki" , "KIKUYU" , "Kenya" , 178 , 2499 },
{ 7 , 0 , "en-BZ" , "ENGLISH" , "Belize" , 31 , 2539 },
{ 2 , 0 , "kk" , "KAZAKH" , "Kazakhstan" , 63 , 2018 },
{ 7 , 0 , "kl" , "GREENLANDIC" , "Greenland" , 44 , 2746 },
{ 20 , 0 , "km" , "KHMER" , "Cambodia" , 23 , 2392 },
{ 21 , 0 , "kn" , "KANNADA" , "India" , 61 , 2511 },
{ 22 , 0 , "ko" , "KOREAN" , "SouthKorea" , 66 , 2465 },
{ 7 , 0 , "en-CA" , "ENGLISH" , "Canada" , 31 , 2539 },
{ 7 , 0 , "en-CC" , "ENGLISH" , "CocosIslands" , 31 , 2539 },
{ 1 , 1 , "ks" , "KASHMIRI" , "India" , 62 , 2617 },
{ 7 , 0 , "ku" , "KURDISH" , "Turkey" , 67 , 2555 },
{ 7 , 0 , "nl-CW" , "DUTCH" , "CuraSao" , 30 , 2393 },
{ 7 , 0 , "kw" , "CORNISH" , "UnitedKingdom" , 145 , 2551 },
{ 7 , 0 , "en-CH" , "ENGLISH" , "Switzerland" , 31 , 2539 },
{ 2 , 0 , "ky" , "KIRGHIZ" , "Kyrgyzstan" , 65 , 2553 },
{ 7 , 0 , "sid" , "SIDAMO" , "Ethiopia" , 155 , 2462 },
{ 7 , 0 , "en-CK" , "ENGLISH" , "CookIslands" , 31 , 2539 },
{ 7 , 0 , "en-CM" , "ENGLISH" , "Cameroon" , 31 , 2539 },
{ 7 , 0 , "fr-YT" , "FRENCH" , "Mayotte" , 37 , 2455 },
{ 7 , 0 , "lb" , "LUXEMBOURGISH" , "Luxembourg" , 231 , 2795 },
{ 7 , 0 , "lg" , "GANDA" , "Uganda" , 194 , 2364 },
{ 7 , 0 , "en-CX" , "ENGLISH" , "ChristmasIsland" , 31 , 2539 },
{ 7 , 0 , "en-CY" , "ENGLISH" , "Cyprus" , 31 , 2539 },
{ 7 , 0 , "ln" , "LINGALA" , "CongoKinshasa" , 72 , 2521 },
{ 23 , 0 , "lo" , "LAO" , "Laos" , 69 , 2237 },
{ 7 , 0 , "mas-TZ" , "MASAI" , "Tanzania" , 202 , 2380 },
{ 7 , 0 , "en-DE" , "ENGLISH" , "Germany" , 31 , 2539 },
{ 7 , 0 , "lt" , "LITHUANIAN" , "Lithuania" , 73 , 2766 },
{ 8 , 0 , "mn-CN" , "MONGOLIAN" , "China" , 82 , 2693 },
{ 7 , 0 , "lu" , "LUBAKATANGA" , "CongoKinshasa" , 230 , 2747 },
{ 7 , 0 , "es-US" , "SPANISH" , "UnitedStates" , 111 , 2551 },
{ 7 , 0 , "en-DG" , "ENGLISH" , "DiegoGarcia" , 31 , 2539 },
{ 7 , 0 , "lv" , "LATVIAN" , "Latvia" , 71 , 2544 },
{ 7 , 0 , "cgg" , "CHIGA" , "Uganda" , 211 , 2365 },
{ 7 , 0 , "en-DK" , "ENGLISH" , "Denmark" , 31 , 2539 },
{ 7 , 0 , "es-UY" , "SPANISH" , "Uruguay" , 111 , 2551 },
{ 7 , 0 , "en-DM" , "ENGLISH" , "Dominica" , 31 , 2539 },
{ 1 , 1 , "pa-PK" , "PUNJABI" , "Pakistan" , 92 , 2538 },
{ 2 , 0 , "ru-BY" , "RUSSIAN" , "Belarus" , 96 , 2566 },
{ 7 , 0 , "es-VE" , "SPANISH" , "Venezuela" , 111 , 2551 },
{ 7 , 0 , "mg" , "MALAGASY" , "Madagascar" , 75 , 2608 },
{ 1 , 1 , "ar-SA" , "ARABIC" , "SaudiArabia" , 8 , 2435 },
{ 7 , 0 , "bem" , "BEMBA" , "Zambia" , 195 , 2360 },
{ 7 , 0 , "mi" , "MAORI" , "NewZealand" , 79 , 2393 },
{ 1 , 1 , "ar-SD" , "ARABIC" , "Sudan" , 8 , 2435 },
{ 2 , 0 , "mk" , "MACEDONIAN" , "Macedonia" , 74 , 2736 },
{ 7 , 0 , "ca-IT" , "CATALAN" , "Italy" , 24 , 2517 },
{ 7 , 0 , "hsb" , "UPPERSORBIAN" , "Germany" , 318 , 2796 },
{ 24 , 0 , "ml" , "MALAYALAM" , "India" , 77 , 2672 },
{ 2 , 0 , "mn" , "MONGOLIAN" , "Mongolia" , 82 , 2693 },
{ 1 , 1 , "fa-AF" , "PERSIAN" , "Afghanistan" , 89 , 2547 },
{ 7 , 0 , "dje" , "ZARMA" , "Niger" , 239 , 2396 },
{ 7 , 0 , "pt-PT" , "PORTUGUESE" , "Portugal" , 91 , 2804 },
{ 13 , 0 , "mr" , "MARATHI" , "India" , 80 , 2535 },
{ 7 , 0 , "ms" , "MALAY" , "Malaysia" , 76 , 2389 },
{ 7 , 0 , "mt" , "MALTESE" , "Malta" , 78 , 2540 },
{ 7 , 0 , "bez" , "BENA" , "Tanzania" , 186 , 2295 },
{ 1 , 1 , "ar-SO" , "ARABIC" , "Somalia" , 8 , 2435 },
{ 25 , 0 , "my" , "BURMESE" , "Myanmar" , 21 , 2548 },
{ 1 , 1 , "ar-SS" , "ARABIC" , "SouthSudan" , 8 , 2435 },
{ 1 , 1 , "ar-SY" , "ARABIC" , "Syria" , 8 , 2435 },
{ 7 , 0 , "en-ER" , "ENGLISH" , "Eritrea" , 31 , 2539 },
{ 7 , 0 , "nb" , "NORWEGIANBOKMAL" , "Norway" , 85 , 2765 },
{ 7 , 0 , "nd" , "NORTH NDEBELE" , "Zimbabwe" , 181 , 2725 },
{ 12 , 0 , "chr" , "CHEROKEE" , "UnitedStates" , 190 , 2599 },
{ 13 , 0 , "ne" , "NEPALI" , "Nepal" , 84 , 2458 },
{ 1 , 1 , "ar-TD" , "ARABIC" , "Chad" , 8 , 2435 },
{ 7 , 0 , "nl" , "DUTCH" , "Netherlands" , 30 , 2393 },
{ 7 , 0 , "nn" , "NORWEGIANNYNORSK" , "Norway" , 141 , 2777 },
{ 2 , 0 , "sr-BA" , "SERBIAN" , "BosniaAndHerzegowina" , 100 , 2533 },
{ 7 , 0 , "nr" , "SOUTH NDEBELE" , "SouthAfrica" , 171 , 2733 },
{ 1 , 1 , "ar-TN" , "ARABIC" , "Tunisia" , 8 , 2435 },
{ 3 , 0 , "en-Dsrt" , "ENGLISH" , "UnitedStates" , 31 , 2539 },
{ 7 , 0 , "en-FI" , "ENGLISH" , "Finland" , 31 , 2539 },
{ 7 , 0 , "en-FJ" , "ENGLISH" , "Fiji" , 31 , 2539 },
{ 7 , 0 , "ny" , "NYANJA" , "Malawi" , 165 , 2466 },
{ 7 , 0 , "en-FK" , "ENGLISH" , "FalklandIslands" , 31 , 2539 },
{ 7 , 0 , "en-FM" , "ENGLISH" , "Micronesia" , 31 , 2539 },
{ 7 , 0 , "oc" , "OCCITAN" , "France" , 86 , 2530 },
{ 2 , 0 , "uz-Cyrl" , "UZBEK" , "Uzbekistan" , 131 , 2402 },
{ 7 , 0 , "om" , "OROMO" , "Ethiopia" , 3 , 2413 },
{ 7 , 0 , "naq" , "NAMA" , "Namibia" , 199 , 2302 },
{ 7 , 0 , "en-GB" , "ENGLISH" , "UnitedKingdom" , 31 , 2539 },
{ 26 , 0 , "or" , "ORIYA" , "India" , 87 , 2405 },
{ 7 , 0 , "en-GD" , "ENGLISH" , "Grenada" , 31 , 2539 },
{ 2 , 0 , "os" , "OSSETIC" , "Georgia" , 101 , 2555 },
{ 7 , 0 , "en-GG" , "ENGLISH" , "Guernsey" , 31 , 2539 },
{ 7 , 0 , "en-GH" , "ENGLISH" , "Ghana" , 31 , 2539 },
{ 7 , 0 , "sma" , "SOUTHERN SAMI" , "Sweden" , 324 , 2764 },
{ 7 , 0 , "en-GI" , "ENGLISH" , "Gibraltar" , 31 , 2539 },
{ 7 , 0 , "en-GM" , "ENGLISH" , "Gambia" , 31 , 2539 },
{ 4 , 0 , "pa" , "PUNJABI" , "India" , 92 , 2538 },
{ 7 , 0 , "smj" , "LULE SAMI" , "Sweden" , 325 , 2653 },
{ 27 , 0 , "ta-SG" , "TAMIL" , "Singapore" , 117 , 2392 },
{ 7 , 0 , "en-GU" , "ENGLISH" , "Guam" , 31 , 2539 },
{ 7 , 0 , "smn" , "INARI SAMI" , "Finland" , 326 , 2718 },
{ 7 , 0 , "sw-UG" , "SWAHILI" , "Uganda" , 113 , 2546 },
{ 7 , 0 , "en-GY" , "ENGLISH" , "Guyana" , 31 , 2539 },
{ 7 , 0 , "gsw" , "SWISS GERMAN" , "Switzerland" , 167 , 2757 },
{ 7 , 0 , "sms" , "SKOLT SAMI" , "Finland" , 327 , 2744 },
{ 7 , 0 , "pl" , "POLISH" , "Poland" , 90 , 2480 },
{ 7 , 0 , "de-AT" , "GERMAN" , "Austria" , 42 , 2459 },
{ 7 , 0 , "pt-ST" , "PORTUGUESE" , "SaoTomeAndPrincipe" , 91 , 2804 },
{ 1 , 1 , "ps" , "PASHTO" , "Afghanistan" , 88 , 2480 },
{ 7 , 0 , "pt" , "PORTUGUESE" , "Brazil" , 91 , 2804 },
{ 1 , 1 , "ckb" , "CENTRAL KURDISH" , "Iraq" , 316 , 2730 },
{ 7 , 0 , "af-NA" , "AFRIKAANS" , "Namibia" , 5 , 2673 },
{ 7 , 0 , "en-HK" , "ENGLISH" , "HongKong" , 31 , 2539 },
{ 7 , 0 , "de-BE" , "GERMAN" , "Belgium" , 42 , 2459 },
{ 7 , 0 , "pt-TL" , "PORTUGUESE" , "EastTimor" , 91 , 2804 },
{ 7 , 0 , "vun" , "VUNJO" , "Tanzania" , 187 , 2419 },
{ 7 , 0 , "en-IE" , "ENGLISH" , "Ireland" , 31 , 2539 },
{ 7 , 0 , "agq" , "AGHEM" , "Cameroon" , 237 , 2371 },
{ 7 , 0 , "qu" , "QUECHUA" , "Peru" , 93 , 2541 },
{ 7 , 0 , "mas" , "MASAI" , "Kenya" , 202 , 2380 },
{ 7 , 0 , "en-IL" , "ENGLISH" , "Israel" , 31 , 2539 },
{ 7 , 0 , "en-IM" , "ENGLISH" , "IsleOfMan" , 31 , 2539 },
{ 2 , 0 , "az-Cyrl" , "AZERBAIJANI" , "Azerbaijan" , 12 , 2744 },
{ 7 , 0 , "en-IN" , "ENGLISH" , "India" , 31 , 2539 },
{ 7 , 0 , "en-IO" , "ENGLISH" , "BritishIndianOceanTerritory" , 31 , 2539 },
{ 7 , 0 , "de-CH" , "GERMAN" , "Switzerland" , 42 , 2459 },
{ 7 , 0 , "guz" , "GUSII" , "Kenya" , 175 , 2402 },
{ 7 , 0 , "rm" , "ROMANSH" , "Switzerland" , 94 , 2553 },
{ 7 , 0 , "rn" , "RUNDI" , "Burundi" , 68 , 2403 },
{ 7 , 0 , "ro" , "ROMANIAN" , "Romania" , 95 , 2614 },
{ 7 , 0 , "nds" , "LOW GERMAN" , "Germany" , 170 , 2733 },
{ 7 , 0 , "en-JE" , "ENGLISH" , "Jersey" , 31 , 2539 },
{ 2 , 0 , "ru" , "RUSSIAN" , "Russia" , 96 , 2566 },
{ 7 , 0 , "rw" , "KINYARWANDA" , "Rwanda" , 64 , 2777 },
{ 7 , 0 , "ln-AO" , "LINGALA" , "Angola" , 72 , 2521 },
{ 7 , 0 , "en-JM" , "ENGLISH" , "Jamaica" , 31 , 2539 },
{ 75 , 1 , "bm-Nkoo" , "BAMBARA" , "Mali" , 188 , 2503 },
{ 13 , 0 , "sa" , "SANSKRIT" , "India" , 99 , 2640 },
{ 1 , 1 , "sd" , "SINDHI" , "Pakistan" , 105 , 2464 },
{ 7 , 0 , "trv" , "TAROKO" , "Taiwan" , 174 , 2481 },
{ 7 , 0 , "se" , "NORTHERN SAMI" , "Norway" , 173 , 2756 },
{ 7 , 0 , "sg" , "SANGO" , "CentralAfricanRepublic" , 98 , 2393 },
{ 16 , 0 , "el-CY" , "GREEK" , "Cyprus" , 43 , 2383 },
{ 32 , 0 , "si" , "SINHALA" , "SriLanka" , 106 , 2529 },
{ 7 , 0 , "sk" , "SLOVAK" , "Slovakia" , 108 , 2481 },
{ 1 , 1 , "ar-YE" , "ARABIC" , "Yemen" , 8 , 2435 },
{ 7 , 0 , "sl" , "SLOVENIAN" , "Slovenia" , 109 , 2704 },
{ 7 , 0 , "sn" , "SHONA" , "Zimbabwe" , 104 , 2394 },
{ 7 , 0 , "so" , "SOMALI" , "Somalia" , 110 , 2470 },
{ 7 , 0 , "sq" , "ALBANIAN" , "Albania" , 6 , 2583 },
{ 7 , 0 , "sr-Latn" , "SERBIAN" , "Serbia" , 100 , 2533 },
{ 2 , 0 , "sr" , "SERBIAN" , "Serbia" , 100 , 2533 },
{ 7 , 0 , "ss" , "SWATI" , "SouthAfrica" , 107 , 2409 },
{ 7 , 0 , "en-KE" , "ENGLISH" , "Kenya" , 31 , 2539 },
{ 7 , 0 , "st" , "SOUTHERN SOTHO" , "SouthAfrica" , 102 , 2764 },
{ 7 , 0 , "sv" , "SWEDISH" , "Sweden" , 114 , 2552 },
{ 7 , 0 , "lag" , "LANGI" , "Tanzania" , 193 , 2380 },
{ 7 , 0 , "sw" , "SWAHILI" , "Tanzania" , 113 , 2546 },
{ 7 , 0 , "en-KI" , "ENGLISH" , "Kiribati" , 31 , 2539 },
{ 7 , 0 , "en-KN" , "ENGLISH" , "SaintKittsAndNevis" , 31 , 2539 },
{ 27 , 0 , "ta" , "TAMIL" , "India" , 117 , 2392 },
{ 7 , 0 , "rof" , "ROMBO" , "Tanzania" , 182 , 2400 },
{ 28 , 0 , "te" , "TELUGU" , "India" , 119 , 2487 },
{ 2 , 0 , "tg" , "TAJIK" , "Tajikistan" , 116 , 2388 },
{ 30 , 0 , "th" , "THAI" , "Thailand" , 120 , 2311 },
{ 7 , 0 , "en-KY" , "ENGLISH" , "CaymanIslands" , 31 , 2539 },
{ 14 , 0 , "ti" , "TIGRINYA" , "Ethiopia" , 122 , 2632 },
{ 7 , 0 , "tk" , "TURKMEN" , "Turkmenistan" , 126 , 2567 },
{ 7 , 0 , "fur" , "FRIULIAN" , "Italy" , 159 , 2619 },
{ 7 , 0 , "tn" , "TSWANA" , "SouthAfrica" , 103 , 2479 },
{ 7 , 0 , "to" , "TONGAN" , "Tonga" , 123 , 2472 },
{ 7 , 0 , "en-LC" , "ENGLISH" , "SaintLucia" , 31 , 2539 },
{ 7 , 0 , "tr" , "TURKISH" , "Turkey" , 125 , 2571 },
{ 7 , 0 , "ln-CF" , "LINGALA" , "CentralAfricanRepublic" , 72 , 2521 },
{ 7 , 0 , "ts" , "TSONGA" , "SouthAfrica" , 124 , 2477 },
{ 7 , 0 , "ln-CG" , "LINGALA" , "CongoBrazzaville" , 72 , 2521 },
{ 2 , 0 , "tt" , "TATAR" , "Russia" , 118 , 2397 },
{ 7 , 0 , "qu-BO" , "QUECHUA" , "Bolivia" , 93 , 2541 },
{ 7 , 0 , "en-LR" , "ENGLISH" , "Liberia" , 31 , 2539 },
{ 7 , 0 , "en-LS" , "ENGLISH" , "Lesotho" , 31 , 2539 },
{ 1 , 1 , "ug" , "UIGHUR" , "China" , 128 , 2485 },
{ 2 , 0 , "uk" , "UKRAINIAN" , "Ukraine" , 129 , 2691 },
{ 2 , 0 , "ru-KG" , "RUSSIAN" , "Kyrgyzstan" , 96 , 2566 },
{ 1 , 1 , "ur" , "URDU" , "Pakistan" , 130 , 2337 },
{ 7 , 0 , "en-MG" , "ENGLISH" , "Madagascar" , 31 , 2539 },
{ 7 , 0 , "fr-BE" , "FRENCH" , "Belgium" , 37 , 2455 },
{ 7 , 0 , "en-MH" , "ENGLISH" , "MarshallIslands" , 31 , 2539 },
{ 7 , 0 , "fr-BF" , "FRENCH" , "BurkinaFaso" , 37 , 2455 },
{ 7 , 0 , "mer" , "MERU" , "Kenya" , 197 , 2330 },
{ 7 , 0 , "kab" , "KABYLE" , "Algeria" , 184 , 2457 },
{ 7 , 0 , "uz" , "UZBEK" , "Uzbekistan" , 131 , 2402 },
{ 7 , 0 , "fr-BI" , "FRENCH" , "Burundi" , 37 , 2455 },
{ 7 , 0 , "fr-BJ" , "FRENCH" , "Benin" , 37 , 2455 },
{ 7 , 0 , "fr-BL" , "FRENCH" , "Saint Barthelemy" , 37 , 2455 },
{ 7 , 0 , "en-MO" , "ENGLISH" , "Macau" , 31 , 2539 },
{ 7 , 0 , "en-MP" , "ENGLISH" , "NorthernMarianaIslands" , 31 , 2539 },
{ 2 , 0 , "ru-KZ" , "RUSSIAN" , "Kazakhstan" , 96 , 2566 },
{ 7 , 0 , "kaj" , "JJU" , "Nigeria" , 158 , 2250 },
{ 7 , 0 , "en-MS" , "ENGLISH" , "Montserrat" , 31 , 2539 },
{ 7 , 0 , "en-MT" , "ENGLISH" , "Malta" , 31 , 2539 },
{ 7 , 0 , "en-MU" , "ENGLISH" , "Mauritius" , 31 , 2539 },
{ 7 , 0 , "ve" , "VENDA" , "SouthAfrica" , 160 , 2383 },
{ 7 , 0 , "kam" , "KAMBA" , "Kenya" , 150 , 2365 },
{ 7 , 0 , "en-MW" , "ENGLISH" , "Malawi" , 31 , 2539 },
{ 7 , 0 , "en-MY" , "ENGLISH" , "Malaysia" , 31 , 2539 },
{ 7 , 0 , "vi" , "VIETNAMESE" , "Vietnam" , 132 , 2770 },
{ 7 , 0 , "dsb" , "LOWERSORBIAN" , "Germany" , 317 , 2793 },
{ 7 , 0 , "mfe" , "MORISYEN" , "Mauritius" , 191 , 2647 },
{ 7 , 0 , "ssy" , "SAHO" , "Eritrea" , 207 , 2316 },
{ 7 , 0 , "en-NA" , "ENGLISH" , "Namibia" , 31 , 2539 },
{ 7 , 0 , "fr-CA" , "FRENCH" , "Canada" , 37 , 2455 },
{ 7 , 0 , "en-NF" , "ENGLISH" , "NorfolkIsland" , 31 , 2539 },
{ 7 , 0 , "fr-CD" , "FRENCH" , "CongoKinshasa" , 37 , 2455 },
{ 7 , 0 , "en-NG" , "ENGLISH" , "Nigeria" , 31 , 2539 },
{ 7 , 0 , "fr-CF" , "FRENCH" , "CentralAfricanRepublic" , 37 , 2455 },
{ 7 , 0 , "fr-CG" , "FRENCH" , "CongoBrazzaville" , 37 , 2455 },
{ 7 , 0 , "fr-CH" , "FRENCH" , "Switzerland" , 37 , 2455 },
{ 7 , 0 , "fr-CI" , "FRENCH" , "IvoryCoast" , 37 , 2455 },
{ 7 , 0 , "en-NL" , "ENGLISH" , "Netherlands" , 31 , 2539 },
{ 7 , 0 , "fr-CM" , "FRENCH" , "Cameroon" , 37 , 2455 },
{ 7 , 0 , "wa" , "WALLOON" , "Belgium" , 236 , 2557 },
{ 7 , 0 , "en-NR" , "ENGLISH" , "Nauru" , 31 , 2539 },
{ 7 , 0 , "en-NU" , "ENGLISH" , "Niue" , 31 , 2539 },
{ 2 , 0 , "ru-MD" , "RUSSIAN" , "Moldova" , 96 , 2566 },
{ 7 , 0 , "en-NZ" , "ENGLISH" , "NewZealand" , 31 , 2539 },
{ 7 , 0 , "wo" , "WOLOF" , "Senegal" , 135 , 2408 },
{ 7 , 0 , "qu-EC" , "QUECHUA" , "Ecuador" , 93 , 2541 },
{ 7 , 0 , "mgh" , "MAKHUWAMEETTO" , "Mozambique" , 244 , 2758 },
{ 7 , 0 , "mgo" , "META" , "Cameroon" , 259 , 2312 },
{ 7 , 0 , "fr-DJ" , "FRENCH" , "Djibouti" , 37 , 2455 },
{ 7 , 0 , "kcg" , "TYAP" , "Nigeria" , 164 , 2335 },
{ 7 , 0 , "twq" , "TASAWAQ" , "Niger" , 251 , 2547 },
{ 7 , 0 , "yav" , "YANGBEN" , "Cameroon" , 254 , 2533 },
{ 7 , 0 , "xh" , "XHOSA" , "SouthAfrica" , 136 , 2404 },
{ 7 , 0 , "dua" , "DUALA" , "Cameroon" , 240 , 2376 },
{ 7 , 0 , "fr-DZ" , "FRENCH" , "Algeria" , 37 , 2455 },
{ 7 , 0 , "it-CH" , "ITALIAN" , "Switzerland" , 58 , 2531 },
{ 7 , 0 , "ewo" , "EWONDO" , "Cameroon" , 242 , 2477 },
{ 7 , 0 , "en-PG" , "ENGLISH" , "PapuaNewGuinea" , 31 , 2539 },
{ 7 , 0 , "en-PH" , "ENGLISH" , "Philippines" , 31 , 2539 },
{ 7 , 0 , "en-PK" , "ENGLISH" , "Pakistan" , 31 , 2539 },
{ 7 , 0 , "kde" , "MAKONDE" , "Tanzania" , 192 , 2528 },
{ 7 , 0 , "en-PN" , "ENGLISH" , "Pitcairn" , 31 , 2539 },
{ 7 , 0 , "en-PR" , "ENGLISH" , "PuertoRico" , 31 , 2539 },
{ 7 , 0 , "en-PW" , "ENGLISH" , "Palau" , 31 , 2539 },
{ 7 , 0 , "yo" , "YORUBA" , "Nigeria" , 138 , 2483 },
{ 7 , 0 , "sr-ME" , "SERBIAN" , "Montenegro" , 100 , 2533 },
{ 7 , 0 , "kea" , "KABUVERDIANU" , "CapeVerde" , 196 , 2751 },
{ 7 , 0 , "es-AR" , "SPANISH" , "Argentina" , 111 , 2551 },
{ 7 , 0 , "ken" , "KENYANG" , "Cameroon" , 319 , 2542 },
{ 5 , 0 , "zh" , "CHINESE" , "China" , 25 , 2528 },
{ 7 , 0 , "iu-Latn" , "INUKTITUT" , "Canada" , 55 , 2738 },
{ 7 , 0 , "fr-GA" , "FRENCH" , "Gabon" , 37 , 2455 },
{ 13 , 0 , "brx" , "BODO" , "India" , 215 , 2309 },
{ 7 , 0 , "zu" , "ZULU" , "SouthAfrica" , 140 , 2353 },
{ 7 , 0 , "fr-GF" , "FRENCH" , "FrenchGuiana" , 37 , 2455 },
{ 7 , 0 , "ee-TG" , "EWE" , "Togo" , 161 , 2242 },
{ 7 , 0 , "es-BO" , "SPANISH" , "Bolivia" , 111 , 2551 },
{ 7 , 0 , "tzm" , "CENTRAL MOROCCO TAMAZIGHT" , "Morocco" , 212 , 2726 },
{ 7 , 0 , "es-BR" , "SPANISH" , "Brazil" , 111 , 2551 },
{ 7 , 0 , "fr-GN" , "FRENCH" , "Guinea" , 37 , 2455 },
{ 7 , 0 , "de-LI" , "GERMAN" , "Liechtenstein" , 42 , 2459 },
{ 7 , 0 , "fr-GP" , "FRENCH" , "Guadeloupe" , 37 , 2455 },
{ 7 , 0 , "fr-GQ" , "FRENCH" , "EquatorialGuinea" , 37 , 2455 },
{ 7 , 0 , "so-DJ" , "SOMALI" , "Djibouti" , 110 , 2470 },
{ 7 , 0 , "nmg" , "KWASIO" , "Cameroon" , 246 , 2479 },
{ 7 , 0 , "en-RW" , "ENGLISH" , "Rwanda" , 31 , 2539 },
{ 2 , 0 , "os-RU" , "OSSETIC" , "Russia" , 101 , 2555 },
{ 9 , 0 , "zgh" , "STANDARD MOROCCAN TAMAZIGHT" , "Morocco" , 314 , 2719 },
{ 7 , 0 , "bss" , "AKOOSE" , "Cameroon" , 312 , 2467 },
{ 7 , 0 , "de-LU" , "GERMAN" , "Luxembourg" , 42 , 2459 },
{ 7 , 0 , "ms-BN" , "MALAY" , "Brunei" , 76 , 2389 },
{ 7 , 0 , "nl-SR" , "DUTCH" , "Suriname" , 30 , 2393 },
{ 7 , 0 , "en-SB" , "ENGLISH" , "SolomonIslands" , 31 , 2539 },
{ 7 , 0 , "en-SC" , "ENGLISH" , "Seychelles" , 31 , 2539 },
{ 7 , 0 , "en-SD" , "ENGLISH" , "Sudan" , 31 , 2539 },
{ 7 , 0 , "en-SE" , "ENGLISH" , "Sweden" , 31 , 2539 },
{ 7 , 0 , "es-CL" , "SPANISH" , "Chile" , 111 , 2551 },
{ 7 , 0 , "en-SG" , "ENGLISH" , "Singapore" , 31 , 2539 },
{ 7 , 0 , "nl-SX" , "DUTCH" , "SintMaarten" , 30 , 2393 },
{ 7 , 0 , "en-SH" , "ENGLISH" , "SaintHelena" , 31 , 2539 },
{ 7 , 0 , "en-SI" , "ENGLISH" , "Slovenia" , 31 , 2539 },
{ 7 , 0 , "es-CO" , "SPANISH" , "Colombia" , 111 , 2551 },
{ 7 , 0 , "en-SL" , "ENGLISH" , "SierraLeone" , 31 , 2539 },
{ 7 , 0 , "es-CR" , "SPANISH" , "CostaRica" , 111 , 2551 },
{ 7 , 0 , "es-CU" , "SPANISH" , "Cuba" , 111 , 2551 },
{ 7 , 0 , "en-SS" , "ENGLISH" , "SouthSudan" , 31 , 2539 },
{ 7 , 0 , "wae" , "WALSER" , "Switzerland" , 253 , 2479 },
{ 7 , 0 , "teo-KE" , "TESO" , "Kenya" , 206 , 2332 },
{ 7 , 0 , "fr-HT" , "FRENCH" , "Haiti" , 37 , 2455 },
{ 7 , 0 , "en-SX" , "ENGLISH" , "SintMaarten" , 31 , 2539 },
{ 7 , 0 , "nnh" , "NGIEMBOON" , "Cameroon" , 260 , 2687 },
{ 33 , 1 , "syr" , "SYRIAC" , "Iraq" , 151 , 2476 },
{ 14 , 0 , "wal" , "WALAMO" , "Ethiopia" , 162 , 2466 },
{ 7 , 0 , "rwk" , "RWA" , "Tanzania" , 209 , 2251 },
{ 7 , 0 , "en-SZ" , "ENGLISH" , "Swaziland" , 31 , 2539 },
{ 7 , 0 , "quc" , "KICHE" , "Guatemala" , 323 , 2373 },
{ 2 , 0 , "bs-Cyrl" , "BOSNIAN" , "BosniaAndHerzegowina" , 142 , 2539 },
{ 7 , 0 , "so-ET" , "SOMALI" , "Ethiopia" , 110 , 2470 },
{ 7 , 0 , "arn" , "MAPUCHE" , "Chile" , 315 , 2532 },
{ 7 , 0 , "en-TC" , "ENGLISH" , "TurksAndCaicosIslands" , 31 , 2539 },
{ 1 , 1 , "ar-AE" , "ARABIC" , "UnitedArabEmirates" , 8 , 2435 },
{ 7 , 0 , "dyo" , "JOLAFONYI" , "Senegal" , 241 , 2700 },
{ 7 , 0 , "es-DO" , "SPANISH" , "DominicanRepublic" , 111 , 2551 },
{ 7 , 0 , "en-TK" , "ENGLISH" , "Tokelau" , 31 , 2539 },
{ 7 , 0 , "nb-SJ" , "NORWEGIANBOKMAL" , "SvalbardAndJanMayenIslands" , 85 , 2765 },
{ 7 , 0 , "en-TO" , "ENGLISH" , "Tonga" , 31 , 2539 },
{ 2 , 0 , "sr-Cyrl-ME" , "SERBIAN" , "Montenegro" , 100 , 2533 },
{ 7 , 0 , "en-TT" , "ENGLISH" , "TrinidadAndTobago" , 31 , 2539 },
{ 7 , 0 , "asa" , "ASU" , "Tanzania" , 205 , 2250 },
{ 7 , 0 , "en-TV" , "ENGLISH" , "Tuvalu" , 31 , 2539 },
{ 7 , 0 , "sq-MK" , "ALBANIAN" , "Macedonia" , 6 , 2583 },
{ 7 , 0 , "haw" , "HAWAIIAN" , "UnitedStates" , 163 , 2595 },
{ 7 , 0 , "en-TZ" , "ENGLISH" , "Tanzania" , 31 , 2539 },
{ 7 , 0 , "khq" , "KOYRA CHIINI" , "Mali" , 208 , 2724 },
{ 7 , 0 , "es-EA" , "SPANISH" , "CeutaAndMelilla" , 111 , 2551 },
{ 7 , 0 , "es-EC" , "SPANISH" , "Ecuador" , 111 , 2551 },
{ 7 , 0 , "wbp" , "WARLPIRI" , "Australia" , 328 , 2635 },
{ 7 , 0 , "en-UG" , "ENGLISH" , "Uganda" , 31 , 2539 },
{ 1 , 1 , "ar-BH" , "ARABIC" , "Bahrain" , 8 , 2435 },
{ 7 , 0 , "ast" , "ASTURIAN" , "Spain" , 256 , 2632 },
{ 7 , 0 , "en-UM" , "ENGLISH" , "UnitedStatesMinorOutlyingIslands" , 31 , 2539 },
{ 7 , 0 , "lkt" , "LAKOTA" , "UnitedStates" , 313 , 2461 },
{ 35 , 0 , "vai" , "VAI" , "Liberia" , 252 , 2241 },
{ 7 , 0 , "jgo" , "NGOMBA" , "Cameroon" , 257 , 2453 },
{ 7 , 0 , "en-VC" , "ENGLISH" , "SaintVincentAndTheGrenadines" , 31 , 2539 },
{ 7 , 0 , "en-VG" , "ENGLISH" , "BritishVirginIslands" , 31 , 2539 },
{ 7 , 0 , "se-FI" , "NORTHERN SAMI" , "Finland" , 173 , 2756 },
{ 7 , 0 , "en-VI" , "ENGLISH" , "UnitedStatesVirginIslands" , 31 , 2539 },
{ 7 , 0 , "gaa" , "GA" , "Ghana" , 148 , 2153 },
{ 7 , 0 , "fr-KM" , "FRENCH" , "Comoros" , 37 , 2455 },
{ 7 , 0 , "en-VU" , "ENGLISH" , "Vanuatu" , 31 , 2539 },
{ 2 , 0 , "ru-UA" , "RUSSIAN" , "Ukraine" , 96 , 2566 },
{ 6 , 0 , "zh-HK" , "CHINESE" , "HongKong" , 25 , 2528 },
{ 7 , 0 , "sw-CD" , "SWAHILI" , "CongoKinshasa" , 113 , 2546 },
{ 75 , 1 , "nqo" , "NKO" , "Guinea" , 321 , 2249 },
{ 7 , 0 , "moh" , "MOHAWK" , "Canada" , 320 , 2472 },
{ 7 , 0 , "ff-CM" , "FULAH" , "Cameroon" , 177 , 2385 },
{ 7 , 0 , "pt-AO" , "PORTUGUESE" , "Angola" , 91 , 2804 },
{ 1 , 1 , "ar-DJ" , "ARABIC" , "Djibouti" , 8 , 2435 },
{ 7 , 0 , "es-GQ" , "SPANISH" , "EquatorialGuinea" , 111 , 2551 },
{ 7 , 0 , "es-GT" , "SPANISH" , "Guatemala" , 111 , 2551 },
{ 7 , 0 , "en-WS" , "ENGLISH" , "Samoa" , 31 , 2539 },
{ 7 , 0 , "kkj" , "KAKO" , "Cameroon" , 258 , 2311 },
{ 7 , 0 , "fr-LU" , "FRENCH" , "Luxembourg" , 37 , 2455 },
{ 1 , 1 , "ar-DZ" , "ARABIC" , "Algeria" , 8 , 2435 },
{ 7 , 0 , "fr-MA" , "FRENCH" , "Morocco" , 37 , 2455 },
{ 7 , 0 , "fr-MC" , "FRENCH" , "Monaco" , 37 , 2455 },
{ 1 , 1 , "ar-EH" , "ARABIC" , "WesternSahara" , 8 , 2435 },
{ 7 , 0 , "es-HN" , "SPANISH" , "Honduras" , 111 , 2551 },
{ 7 , 0 , "fr-MF" , "FRENCH" , "Saint Martin" , 37 , 2455 },
{ 7 , 0 , "fr-MG" , "FRENCH" , "Madagascar" , 37 , 2455 },
{ 7 , 0 , "fr-ML" , "FRENCH" , "Mali" , 37 , 2455 },
{ 1 , 1 , "ar-ER" , "ARABIC" , "Eritrea" , 8 , 2435 },
{ 7 , 0 , "fr-MQ" , "FRENCH" , "Martinique" , 37 , 2455 },
{ 7 , 0 , "fr-MR" , "FRENCH" , "Mauritania" , 37 , 2455 },
{ 7 , 0 , "kln" , "KALENJIN" , "Kenya" , 198 , 2605 },
{ 7 , 0 , "fr-MU" , "FRENCH" , "Mauritius" , 37 , 2455 },
{ 14 , 0 , "byn" , "BLIN" , "Eritrea" , 152 , 2310 },
{ 7 , 0 , "sr-Latn-XK" , "SERBIAN" , "Kosovo" , 100 , 2533 },
{ 7 , 0 , "pt-CH" , "PORTUGUESE" , "Switzerland" , 91 , 2804 },
{ 7 , 0 , "es-IC" , "SPANISH" , "CanaryIslands" , 111 , 2551 },
{ 7 , 0 , "nso" , "NORTHERN SOTHO" , "SouthAfrica" , 172 , 2756 },
{ 7 , 0 , "sv-AX" , "SWEDISH" , "AlandIslands" , 114 , 2552 },
{ 22 , 0 , "ko-KP" , "KOREAN" , "NorthKorea" , 66 , 2465 },
{ 7 , 0 , "fr-NC" , "FRENCH" , "NewCaledonia" , 37 , 2455 },
{ 7 , 0 , "vai-Latn" , "VAI" , "Liberia" , 252 , 2241 },
{ 7 , 0 , "fr-NE" , "FRENCH" , "Niger" , 37 , 2455 },
{ 7 , 0 , "pt-CV" , "PORTUGUESE" , "CapeVerde" , 91 , 2804 },
{ 1 , 1 , "ckb-IR" , "CENTRAL KURDISH" , "Iran" , 316 , 2730 },
{ 7 , 0 , "so-KE" , "SOMALI" , "Kenya" , 110 , 2470 },
{ 7 , 0 , "aa" , "AFAR" , "Ethiopia" , 4 , 2299 },
{ 7 , 0 , "fo-DK" , "FAROESE" , "Denmark" , 34 , 2534 },
{ 5 , 0 , "zh-Hans-HK" , "CHINESE" , "HongKong" , 25 , 2528 },
{ 7 , 0 , "af" , "AFRIKAANS" , "SouthAfrica" , 5 , 2673 },
{ 7 , 0 , "es-419" , "SPANISH" , "LatinAmericaAndTheCaribbean" , 111 , 2551 },
{ 7 , 0 , "en-ZA" , "ENGLISH" , "SouthAfrica" , 31 , 2539 },
{ 7 , 0 , "ak" , "AKAN" , "Ghana" , 146 , 2300 },
{ 14 , 0 , "am" , "AMHARIC" , "Ethiopia" , 7 , 2518 },
  };


//// static const int Rdb_list_2017_size = 551;  //// sizeof(Rdb_list)/sizeof(Rdb_list[0]);
/* tot. 552   -> 9.8.2017  */


/*  struct QLocale2017 {
        //// left to right
        int scr_id; //// script from qchar <-> qlocale
        int write_direction; //// how to write...
        const char *bcp47name; //// QLocale loc(bcp47name); /// go make all.
        const char *language;
        const char *country;
        int index_language; PORTUGUESE
    };
  */

int DataLocaleProvider::qlocaleLanguageIdqt( const QString lang) {
     QString idlang = lang.toUpper();
     const int idx = idbirthay(idlang);
     QLocale2017 *p = combinelist;
     while (p->language) {
         if (p->lang_key == idx ) {
             return p->index_language;
           }
          ++p;
     }
   return -1;
}

QLocale DataLocaleProvider::qlocaleFromLanguageUnique( const QString lang) {
     QString idlang = lang.toUpper();
     const int idx = idbirthay(idlang);
     QLocale2017 *p = combinelist;
     while (p->language) {
         if (p->lang_key == idx ) {
             const QString idnameqt = QString::fromStdString(p->bcp47name );
             /// qDebug() << idnameqt;
             const QLocale park= QLocale(idnameqt);
             return park;
           }
          ++p;
     }
   return QLocale::system();
}

QList < QLocale > DataLocaleProvider::qlocaleFromLanguage( const QString lang) {

  QString idlang = lang.toUpper();
  QList < QLocale > parter;
  parter.insert(0,QLocale::system());
  const int idx = idbirthay(idlang);
  int j = 0;
  QLocale2017 *p = combinelist;
  while (p->language) {

      if (p->lang_key == idx ) {
          j++;
          const QString idnameqt = QString::fromStdString(p->bcp47name );
          qDebug() << idnameqt;
          QLocale park= QLocale(idnameqt);
          parter.insert(j,park);
        }
       ++p;
  }

  return parter;
}

QStringList DataLocaleProvider::getidlocaleidForScript( const int nr  )
{
  QStringList rec;
  rec << QString("EARTH");

  int j = -1;
  QLocale2017 *p = combinelist;
  while (p->language) {
      j++;
      if (p->scr_id == nr ) {
          rec << QString::fromStdString(p->bcp47name);
        }
       ++p;
  }
  if (rec.size() > 1 ) {
      rec.removeFirst();
    }

  qStableSort(rec.begin(), rec.end());
  return rec;
}


QStringList DataLocaleProvider::getCountryNamefromLanguage( QString lang )
{
     QString idlang = lang.toUpper(); /// CHECHEN
     QStringList rec;
     rec << QString("EARTH-MILKY-WAY-GALAXY");
     const int idx = idbirthay(idlang);
     int j = -1;
     QLocale2017 *p = combinelist;
     while (p->language) {
         j++;
         if (p->lang_key == idx ) {
             rec << QString::fromStdString(p->country).toUpper() + "-" + QString::fromStdString(p->language ).toUpper();
           }
          ++p;
     }
     if (rec.size() > 1 ) {
         rec.removeFirst();
       }
     qStableSort(rec.begin(), rec.end());

    return rec;
}

QStringList DataLocaleProvider::getCountryNameForScript( const int nr )
{
    QStringList rec;
    rec << QString("EARTH-MILKY-WAY-GALAXY");

    int j = -1;
    QLocale2017 *p = combinelist;
    while (p->language) {
        j++;
        if (p->scr_id == nr ) {
            rec << QString::fromStdString(p->country).toUpper() + "-" + QString::fromStdString(p->language ).toUpper();
          }
         ++p;
    }
    if (rec.size() > 1 ) {
        rec.removeFirst();
      }

    qStableSort(rec.begin(), rec.end());
    return rec;
}

QString DataLocaleProvider::getLanguageNameForScript( const int nr )
{
    /// const int summ = Rdb_list_2017_size;
    if ( nr == 7 ) {
        return QString("LATIN");
      }

    QLocale2017 *p = combinelist;
    while (p->language) {
          if ( p->scr_id == nr  ) {
            return QString::fromStdString(p->language).toUpper();
           }
         ++p;
    }
    return QString("UNKNOWLANG"); /// or assert!!
}


void DataLocaleProvider::get_language_native(int id , QString & nt , QString & ctess ) {

  /*  Tesseract has unicode (UTF-8) support, and can recognize more than 100 languages "out of the box".
      download link generator (QString & ctess)     */
  switch(id) {
      /* 8 - Arabic  الْعَرَبيّة  */
      case 8 : nt = QTUTF8decode("\xD8\xA7\xD9\x84\xD9\x92\xD8\xB9\xD9\x8E\xD8\xB1\xD9\x8E\xD8\xA8\xD9\x8A\xD9\x91\xD8\xA9");
               ctess= QStringLiteral("ara");
               break;
      /* 28 - Czech  čeština */
      case 28 : nt = QTUTF8decode("\xC4\x8D\x65\xC5\xA1\x74\x69\x6E\x61");
                ctess= QStringLiteral("ces");
               break;
      /* 29 - Danish dansk */
      case 29 : nt = QTUTF8decode("\x64\x61\x6E\x73\x6B");
               ctess= QStringLiteral("dan");
               break;
      /* 42 - German  deusch */
      case 42 : nt = QTUTF8decode("\x44\x65\x75\x73\x63\x68");
                ctess= QStringLiteral("deu");
              break;
      /* el - 43 - Greek - Greece     ελληνική/0  \xCE\xB5\xCE\xBB\xCE\xBB\xCE\xB7\xCE\xBD\xCE\xB9\xCE\xBA\xCE\xAE */
      case 43 : nt = QTUTF8decode("\xCE\xB5\xCE\xBB\xCE\xBB\xCE\xB7\xCE\xBD\xCE\xB9\xCE\xBA\xCE\xAE");
               ctess= QStringLiteral("ita_old"); //// not having dir get old italian!
               break;
      /* 31 - English  */
      case 31 : nt = QTUTF8decode("\x65\x6E\x67\x6C\x69\x73\x68");
              ctess= QStringLiteral("eng");
              break;
      /* 111 - Spanish castellà */
      case 111 : nt = QTUTF8decode("\x63\x61\x73\x74\x65\x6C\x6C\xC3\xA0");
              ctess= QStringLiteral("spa");
              break;
      /* 36 - Finnish  suomi */
      case 36 : nt = QTUTF8decode("\x73\x75\x6F\x6D\x69");
              ctess= QStringLiteral("fin");
               break;
      /* 37 - French   français */
      case 37 : nt = QTUTF8decode("\x66\x72\x61\x6E\xC3\xA7\x61\x69\x73");
              ctess= QStringLiteral("fra");
              break;
      /* he - 48 - Hebrew      עִברִית/heb  */
      case 48 : nt = QTUTF8decode("\xD7\xA2\xD6\xB4\xD7\x91\xD7\xA8\xD6\xB4\xD7\x99\xD7\xAA");
              ctess= QStringLiteral("heb");
              break;
      /* hi - 49 - Hindi - India     हिन्दी/hin */
      case 49 : nt = QTUTF8decode("\xE0\xA4\xB9\xE0\xA4\xBF\xE0\xA4\xA8\xE0\xA5\x8D\xE0\xA4\xA6\xE0\xA5\x80");
              ctess= QStringLiteral("hin");
              break;
      /* id - 52 - Indonesian - Indonesia   bahasa_indonesia/ind    \x62\x61\x68\x61\x73\x61\x20\x49\x6E\x64\x6F\x6E\x65\x73\x69\x61 */
      case 52 : nt = QTUTF8decode("\x62\x61\x68\x61\x73\x61\x20\x49\x6E\x64\x6F\x6E\x65\x73\x69\x61");
              ctess= QStringLiteral("ind");
              break;
      /* it - 58 - Italian - Italy  italiano/ita   \x69\x74\x61\x6C\x69\x61\x6E\x6F */
      case 58 : nt = QTUTF8decode("\x69\x74\x61\x6C\x69\x61\x6E\x6F");
              ctess= QStringLiteral("ita");
              break;
      /* ja - 59 - Japanese - Japan   日本語/jpn             \xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E */
      case 59 : nt = QTUTF8decode("\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E");
              ctess= QStringLiteral("jpn");
              break;
      /* ko - 66 - Korean - SouthKorea    한국어/kor   \xED\x95\x9C\xEA\xB5\xAD\xEC\x96\xB4 */
      case 66 : nt = QTUTF8decode("\xED\x95\x9C\xEA\xB5\xAD\xEC\x96\xB4");
              ctess= QStringLiteral("kor");
              break;
      /*nb - 85 - NorwegianBokmal - Norway   norsk/nor \x6E\x6F\x72\x73\x6B */
      case 85 : nt = QTUTF8decode("\x6E\x6F\x72\x73\x6B");
             ctess= QStringLiteral("nor");
              break;
      /*nl - 30 - Dutch - Netherlands  Nederlands/nld  \x4E\x65\x64\x65\x72\x6C\x61\x6E\x64\x73 */
      case 30 : nt = QTUTF8decode("\x4E\x65\x64\x65\x72\x6C\x61\x6E\x64\x73");
            ctess= QStringLiteral("nld");
            break;
      /*pl - 90 - Polish - Poland    polski/pol  \x70\x6F\x6C\x73\x6B\x69 */
      case 90 : nt = QTUTF8decode("\x70\x6F\x6C\x73\x6B\x69");
            ctess= QStringLiteral("pol");
            break;
     /*pt - 91 - Portuguese - Brazil+Portigal   português/por   \x70\x6F\x72\x74\x75\x67\x75\xC3\xAA\x73 */
      case 91 : nt = QTUTF8decode("\x70\x6F\x72\x74\x75\x67\x75\xC3\xAA\x73");
            ctess= QStringLiteral("por");
            break;
      /*ro - 95 - Romanian - Romania  română/ron   \x72\x6F\x6D\xC3\xA2\x6E\xC4\x83 */
      case 95 : nt = QTUTF8decode("\x72\x6F\x6D\xC3\xA2\x6E\xC4\x83");
            ctess= QStringLiteral("ron");
            break;
      /*ru - 96 - Russian - Russia   ру́сский/rus     \xD1\x80\xD1\x83\xCC\x81\xD1\x81\xD1\x81\xD0\xBA\xD0\xB8\xD0\xB9 */
      case 96 : nt = QTUTF8decode("\xD1\x80\xD1\x83\xCC\x81\xD1\x81\xD1\x81\xD0\xBA\xD0\xB8\xD0\xB9");
            ctess= QStringLiteral("rus");
            break;
      /*sk - 108 - Slovak - Slovakia  slovenský/slk   \x73\x6C\x6F\x76\x65\x6E\x73\x6B\xC3\xBD */
      case 108 : nt = QTUTF8decode("\x73\x6C\x6F\x76\x65\x6E\x73\x6B\xC3\xBD");
            ctess= QStringLiteral("slk");
            break;
      /*sv - 114 - Swedish - Sweden   svenska/swe     \x73\x76\x65\x6E\x73\x6B\x61 */
      case 114 : nt = QTUTF8decode("\x73\x76\x65\x6E\x73\x6B\x61");
            ctess= QStringLiteral("swe");
            break;
      /*th - 120 - Thai - Thailand   ภาษาไทย/tha         \xE0\xB8\xA0\xE0\xB8\xB2\xE0\xB8\xA9\xE0\xB8\xB2\xE0\xB9\x84\xE0\xB8\x97\xE0\xB8\xA2 */
      case 120 : nt = QTUTF8decode("\xE0\xB8\xA0\xE0\xB8\xB2\xE0\xB8\xA9\xE0\xB8\xB2\xE0\xB9\x84\xE0\xB8\x97\xE0\xB8\xA2");
            ctess= QStringLiteral("tha");
            break;
      /*tr - 125 - Turkish - Turkey   Türkçe/tur        \x54\xC3\xBC\x72\x6B\xC3\xA7\x65 */
      case 125 : nt = QTUTF8decode("\x54\xC3\xBC\x72\x6B\xC3\xA7\x65");
            ctess= QStringLiteral("tur");
            break;
      /*zh - 25 - Chinese - China   汉语/chi_sim  chi_vert chi_tra  chi_tra_vert         \xE6\xB1\x89\xE8\xAF\xAD */
      case 25 : nt = QTUTF8decode("\xE6\xB1\x89\xE8\xAF\xAD");
            ctess= QStringLiteral("chi_sim");
            break;
      /* hu - 50 - Hungarian - Hungary     magyar/hun        \x4D\x61\x67\x79\x61\x72 */
      case 50 : nt = QTUTF8decode("\x4D\x61\x67\x79\x61\x72");
          ctess= QStringLiteral("hun");
          break;
      default:  nt = QStringLiteral("no"); //// not having dir or function
                ctess = QStringLiteral("null"); //// not having dir

  }
}



 /* latin ALANDISLANDS-SWEDISH,ALBANIA-ALBANIAN,ALGERIA-FRENCH,ALGERIA-KABYLE,AMERICANSAMOA-ENGLISH,ANDORRA-CATALAN,
  * ANGOLA-LINGALA,ANGOLA-PORTUGUESE,ANGUILLA-ENGLISH,ANTIGUAANDBARBUDA-ENGLISH,ARGENTINA-SPANISH,ARUBA-DUTCH,
  * AUSTRALIA-ENGLISH,AUSTRALIA-WARLPIRI,AUSTRIA-ENGLISH,AUSTRIA-GERMAN,AZERBAIJAN-AZERBAIJANI,BAHAMAS-ENGLISH,
  * BARBADOS-ENGLISH,BELGIUM-DUTCH,BELGIUM-ENGLISH,BELGIUM-FRENCH,BELGIUM-GERMAN,BELGIUM-WALLOON,BELIZE-ENGLISH,
  * BENIN-FRENCH,BENIN-YORUBA,BERMUDA-ENGLISH,BOLIVIA-QUECHUA,BOLIVIA-SPANISH,BONAIRE-DUTCH,BOSNIAANDHERZEGOWINA-BOSNIAN,
  * BOSNIAANDHERZEGOWINA-CROATIAN,BOSNIAANDHERZEGOWINA-SERBIAN,BOTSWANA-ENGLISH,BRAZIL-PORTUGUESE,BRAZIL-SPANISH,
  * BRITISHINDIANOCEANTERRITORY-ENGLISH,BRITISHVIRGINISLANDS-ENGLISH,BRUNEI-MALAY,BURKINAFASO-FRENCH,BURUNDI-ENGLISH,
  * BURUNDI-FRENCH,BURUNDI-RUNDI,CAMEROON-AGHEM,CAMEROON-AKOOSE,CAMEROON-BAFIA,CAMEROON-BASAA,CAMEROON-DUALA,CAMEROON-ENGLISH,
  * CAMEROON-EWONDO,CAMEROON-FRENCH,CAMEROON-FULAH,CAMEROON-KAKO,CAMEROON-KENYANG,CAMEROON-KWASIO,CAMEROON-META,CAMEROON-MUNDANG,
  * CAMEROON-NGIEMBOON,CAMEROON-NGOMBA,CAMEROON-YANGBEN,CANADA-ENGLISH,CANADA-FRENCH,CANADA-INUKTITUT,CANADA-MOHAWK,CANARYISLANDS-SPANISH,
  * CAPEVERDE-KABUVERDIANU,CAPEVERDE-PORTUGUESE,CAYMANISLANDS-ENGLISH,CENTRALAFRICANREPUBLIC-FRENCH,CENTRALAFRICANREPUBLIC-LINGALA,
  * CENTRALAFRICANREPUBLIC-SANGO,CEUTAANDMELILLA-SPANISH,CHAD-FRENCH,CHILE-MAPUCHE,CHILE-SPANISH,CHRISTMASISLAND-ENGLISH,COCOSISLANDS-ENGLISH,
  * COLOMBIA-SPANISH,COMOROS-FRENCH,CONGOBRAZZAVILLE-FRENCH,CONGOBRAZZAVILLE-LINGALA,CONGOKINSHASA-FRENCH,CONGOKINSHASA-LINGALA,
  * CONGOKINSHASA-LUBAKATANGA,CONGOKINSHASA-SWAHILI,COOKISLANDS-ENGLISH,COSTARICA-SPANISH,CROATIA-CROATIAN,CUBA-SPANISH,CURASAO-DUTCH,
  * CYPRUS-ENGLISH,CYPRUS-TURKISH,CZECHREPUBLIC-CZECH,DENMARK-DANISH,DENMARK-ENGLISH,DENMARK-FAROESE,DIEGOGARCIA-ENGLISH,DJIBOUTI-FRENCH,
  * DJIBOUTI-SOMALI,DOMINICA-ENGLISH,DOMINICANREPUBLIC-SPANISH,EASTTIMOR-PORTUGUESE,ECUADOR-QUECHUA,ECUADOR-SPANISH,ELSALVADOR-SPANISH,
  * EQUATORIALGUINEA-FRENCH,EQUATORIALGUINEA-PORTUGUESE,EQUATORIALGUINEA-SPANISH,ERITREA-ENGLISH,ERITREA-SAHO,ESTONIA-ESTONIAN,ETHIOPIA-AFAR,
  * ETHIOPIA-OROMO,ETHIOPIA-SIDAMO,ETHIOPIA-SOMALI,FALKLANDISLANDS-ENGLISH,FAROEISLANDS-FAROESE,FIJI-ENGLISH,FINLAND-ENGLISH,FINLAND-FINNISH,
  * FINLAND-INARI SAMI,FINLAND-NORTHERN SAMI,FINLAND-SKOLT SAMI,FINLAND-SWEDISH,FRANCE-BRETON,FRANCE-CATALAN,FRANCE-CORSICAN,FRANCE-FRENCH,
  * FRANCE-INTERLINGUA,FRANCE-OCCITAN,FRANCE-SWISS GERMAN,FRENCHGUIANA-FRENCH,FRENCHPOLYNESIA-FRENCH,GABON-FRENCH,GAMBIA-ENGLISH,
  * GERMANY-COLOGNIAN,GERMANY-ENGLISH,GERMANY-GERMAN,GERMANY-LOW GERMAN,GERMANY-LOWERSORBIAN,GERMANY-UPPERSORBIAN,GHANA-AKAN,GHANA-ENGLISH,
  * GHANA-EWE,GHANA-GA,GHANA-HAUSA,GIBRALTAR-ENGLISH,GREENLAND-DANISH,GREENLAND-GREENLANDIC,GRENADA-ENGLISH,GUADELOUPE-FRENCH,GUAM-ENGLISH,
  * GUATEMALA-KICHE,GUATEMALA-SPANISH,GUERNSEY-ENGLISH,GUINEA-FRENCH,GUINEA-FULAH,GUINEABISSAU-PORTUGUESE,GUYANA-ENGLISH,HAITI-FRENCH,
  * HONDURAS-SPANISH,HONGKONG-ENGLISH,HUNGARY-HUNGARIAN,ICELAND-ICELANDIC,INDIA-ENGLISH,INDONESIA-INDONESIAN,INDONESIA-JAVANESE,
  * IRELAND-ENGLISH,IRELAND-IRISH,ISLEOFMAN-ENGLISH,ISLEOFMAN-MANX,ISRAEL-ENGLISH,ITALY-CATALAN,ITALY-FRIULIAN,ITALY-ITALIAN,
  * IVORYCOAST-FRENCH,JAMAICA-ENGLISH,JERSEY-ENGLISH,KENYA-EMBU,KENYA-ENGLISH,KENYA-GUSII,KENYA-KALENJIN,KENYA-KAMBA,KENYA-KIKUYU,
  * KENYA-LUO,KENYA-LUYIA,KENYA-MASAI,KENYA-MERU,KENYA-OROMO,KENYA-SAMBURU,KENYA-SOMALI,KENYA-SWAHILI,KENYA-TAITA,KENYA-TESO,
  * KIRIBATI-ENGLISH,KOSOVO-ALBANIAN,KOSOVO-SERBIAN,LATINAMERICAANDTHECARIBBEAN-SPANISH,LATVIA-LATVIAN,LESOTHO-ENGLISH,LIBERIA-ENGLISH,
  * LIBERIA-KPELLE,LIBERIA-VAI,LIECHTENSTEIN-GERMAN,LIECHTENSTEIN-SWISS GERMAN,LITHUANIA-LITHUANIAN,LUXEMBOURG-FRENCH,LUXEMBOURG-GERMAN,
  * LUXEMBOURG-LUXEMBOURGISH,LUXEMBOURG-PORTUGUESE,MACAU-ENGLISH,MACAU-PORTUGUESE,MACEDONIA-ALBANIAN,MADAGASCAR-ENGLISH,MADAGASCAR-FRENCH,
  * MADAGASCAR-MALAGASY,MALAWI-ENGLISH,MALAWI-NYANJA,MALAYSIA-ENGLISH,MALAYSIA-MALAY,MALI-BAMBARA,MALI-FRENCH,MALI-KOYRA CHIINI,
  * MALI-KOYRABORO SENNI,MALTA-ENGLISH,MALTA-MALTESE,MARSHALLISLANDS-ENGLISH,MARTINIQUE-FRENCH,MAURITANIA-FRENCH,MAURITANIA-FULAH,
  * MAURITIUS-ENGLISH,MAURITIUS-FRENCH,MAURITIUS-MORISYEN,MAYOTTE-FRENCH,MEXICO-SPANISH,MICRONESIA-ENGLISH,MOLDOVA-ROMANIAN,MONACO-FRENCH,
  * MONTENEGRO-SERBIAN,MONTSERRAT-ENGLISH,MOROCCO-CENTRAL MOROCCO TAMAZIGHT,MOROCCO-FRENCH,MOROCCO-TACHELHIT,MOZAMBIQUE-MAKHUWAMEETTO,
  * MOZAMBIQUE-PORTUGUESE,MOZAMBIQUE-SENA,NAMIBIA-AFRIKAANS,NAMIBIA-ENGLISH,NAMIBIA-NAMA,NAURU-ENGLISH,NETHERLANDS-DUTCH,NETHERLANDS-ENGLISH,
  * NETHERLANDS-WESTERN FRISIAN,NEWCALEDONIA-FRENCH,NEWZEALAND-ENGLISH,NEWZEALAND-MAORI,NICARAGUA-SPANISH,NIGER-FRENCH,NIGER-HAUSA,NIGER-TASAWAQ,
  * NIGER-ZARMA,NIGERIA-ATSAM,NIGERIA-ENGLISH,NIGERIA-HAUSA,NIGERIA-IGBO,NIGERIA-JJU,NIGERIA-TYAP,NIGERIA-YORUBA,NIUE-ENGLISH,
  * NORFOLKISLAND-ENGLISH,NORTHERNMARIANAISLANDS-ENGLISH,NORWAY-NORTHERN SAMI,NORWAY-NORWEGIANBOKMAL,NORWAY-NORWEGIANNYNORSK,PAKISTAN-ENGLISH,
  * PALAU-ENGLISH,PANAMA-SPANISH,PAPUANEWGUINEA-ENGLISH,PARAGUAY-GUARANI,PARAGUAY-SPANISH,PERU-QUECHUA,PERU-SPANISH,PHILIPPINES-ENGLISH,
  * PHILIPPINES-FILIPINO,PHILIPPINES-SPANISH,PITCAIRN-ENGLISH,POLAND-POLISH,PORTUGAL-PORTUGUESE,PUERTORICO-ENGLISH,PUERTORICO-SPANISH,REUNION-FRENCH,
  * ROMANIA-ROMANIAN,RWANDA-ENGLISH,RWANDA-FRENCH,RWANDA-KINYARWANDA,SAINT BARTHELEMY-FRENCH,SAINT MARTIN-FRENCH,SAINTHELENA-ENGLISH,SAINTKITTSANDNEVIS-ENGLISH,
  * SAINTLUCIA-ENGLISH,SAINTPIERREANDMIQUELON-FRENCH,SAINTVINCENTANDTHEGRENADINES-ENGLISH,SAMOA-ENGLISH,SANMARINO-ITALIAN,SAOTOMEANDPRINCIPE-PORTUGUESE,
  * SENEGAL-FRENCH,SENEGAL-FULAH,SENEGAL-JOLAFONYI,SENEGAL-WOLOF,SERBIA-SERBIAN,SEYCHELLES-ENGLISH,SEYCHELLES-FRENCH,SIERRALEONE-ENGLISH,SINGAPORE-ENGLISH,
  * SINGAPORE-MALAY,SINTMAARTEN-DUTCH,SINTMAARTEN-ENGLISH,SLOVAKIA-SLOVAK,SLOVENIA-ENGLISH,SLOVENIA-SLOVENIAN,SOLOMONISLANDS-ENGLISH,SOMALIA-SOMALI,
  * SOUTHAFRICA-AFRIKAANS,SOUTHAFRICA-ENGLISH,SOUTHAFRICA-NORTHERN SOTHO,SOUTHAFRICA-SOUTH NDEBELE,SOUTHAFRICA-SOUTHERN SOTHO,SOUTHAFRICA-SWATI,SOUTHAFRICA-TSONGA,
  * SOUTHAFRICA-TSWANA,SOUTHAFRICA-VENDA,SOUTHAFRICA-XHOSA,SOUTHAFRICA-ZULU,SOUTHSUDAN-ENGLISH,SOUTHSUDAN-NUER,SPAIN-ASTURIAN,SPAIN-BASQUE,SPAIN-CATALAN,SPAIN-GALICIAN,
  * SPAIN-SPANISH,SUDAN-ENGLISH,SURINAME-DUTCH,SVALBARDANDJANMAYENISLANDS-NORWEGIANBOKMAL,SWAZILAND-ENGLISH,SWEDEN-ENGLISH,SWEDEN-LULE SAMI,SWEDEN-NORTHERN SAMI,
  * SWEDEN-SOUTHERN SAMI,SWEDEN-SWEDISH,SWITZERLAND-ENGLISH,SWITZERLAND-FRENCH,SWITZERLAND-GERMAN,SWITZERLAND-ITALIAN,SWITZERLAND-PORTUGUESE,SWITZERLAND-ROMANSH,
  * SWITZERLAND-SWISS GERMAN,SWITZERLAND-WALSER,SYRIA-FRENCH,TAIWAN-TAROKO,TANZANIA-ASU,TANZANIA-BENA,TANZANIA-ENGLISH,TANZANIA-LANGI,TANZANIA-MACHAME,TANZANIA-MAKONDE,
  * TANZANIA-MASAI,TANZANIA-ROMBO,TANZANIA-RWA,TANZANIA-SANGU,TANZANIA-SHAMBALA,TANZANIA-SWAHILI,TANZANIA-VUNJO,TOGO-EWE,TOGO-FRENCH,TOKELAU-ENGLISH,TONGA-ENGLISH,TONGA-TONGAN,TRINIDADANDTOBAGO-ENGLISH,TUNISIA-FRENCH,TURKEY-KURDISH,TURKEY-TURKISH,TURKMENISTAN-TURKMEN,TURKSANDCAICOSISLANDS-ENGLISH,TUVALU-ENGLISH,UGANDA-CHIGA,UGANDA-ENGLISH,UGANDA-GANDA,UGANDA-NYANKOLE,UGANDA-SOGA,UGANDA-SWAHILI,UGANDA-TESO,UNITEDKINGDOM-CORNISH,UNITEDKINGDOM-ENGLISH,
  * UNITEDKINGDOM-GAELIC,UNITEDKINGDOM-WELSH,UNITEDSTATES-ENGLISH,UNITEDSTATES-HAWAIIAN,UNITEDSTATES-LAKOTA,UNITEDSTATES-SPANISH,UNITEDSTATESMINOROUTLYINGISLANDS-ENGLISH,
  * UNITEDSTATESVIRGINISLANDS-ENGLISH,URUGUAY-SPANISH,UZBEKISTAN-UZBEK,VANUATU-ENGLISH,VANUATU-FRENCH,VENEZUELA-SPANISH,VIETNAM-VIETNAMESE,WALLISANDFUTUNAISLANDS-FRENCH,
  * ZAMBIA-BEMBA,ZAMBIA-ENGLISH,ZIMBABWE-ENGLISH,ZIMBABWE-NORTH NDEBELE,ZIMBABWE-SHONA */







