#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sys/_types/_size_t.h>
#include <unordered_map>
#include <vector>

namespace sim::common {

    enum class SYMBOL : size_t {
        BTCUSDT,
        ETHUSDT,
        BNBUSDT,
        NEOUSDT,
        LTCUSDT,
        QTUMUSDT,
        ADAUSDT,
        XRPUSDT,
        EOSUSDT,
        IOTAUSDT,
        TUSDUSDT,
        XLMUSDT,
        ONTUSDT,
        TRXUSDT,
        ETCUSDT,
        ICXUSDT,
        NULSUSDT,
        VETUSDT,
        PAXUSDT,
        USDCUSDT,
        LINKUSDT,
        WAVESUSDT,
        BTTUSDT,
        ONGUSDT,
        HOTUSDT,
        ZILUSDT,
        ZRXUSDT,
        FETUSDT,
        BATUSDT,
        XMRUSDT,
        ZECUSDT,
        IOSTUSDT,
        CELRUSDT,
        DASHUSDT,
        OMGUSDT,
        NANOUSDT,
        THETAUSDT,
        ENJUSDT,
        MITHUSDT,
        MATICUSDT,
        ATOMUSDT,
        TFUELUSDT,
        ONEUSDT,
        FTMUSDT,
        ALGOUSDT,
        GTOUSDT,
        DOGEUSDT,
        DUSKUSDT,
        ANKRUSDT,
        WINUSDT,
        COSUSDT,
        NPXSUSDT,
        COCOSUSDT,
        MTLUSDT,
        TOMOUSDT,
        PERLUSDT,
        FUNUSDT,
        WANUSDT,
        CVCUSDT,
        DENTUSDT,
        DOCKUSDT,
        MFTUSDT,
        KEYUSDT,
        CHZUSDT,
        BANDUSDT,
        BUSDUSDT,
        BEAMUSDT,
        XTZUSDT,
        RENUSDT,
        RVNUSDT,
        HBARUSDT,
        NKNUSDT,
        KAVAUSDT,
        STXUSDT,
        ARPAUSDT,
        RLCUSDT,
        IOTXUSDT,
        CTXCUSDT,
        BCHUSDT,
        TROYUSDT,
        VITEUSDT,
        FTTUSDT,
        EURUSDT,
        OGNUSDT,
        DREPUSDT,
        TCTUSDT,
        WRXUSDT,
        BNTUSDT,
        LSKUSDT,
        BTSUSDT,
        LTOUSDT,
        AIONUSDT,
        MBLUSDT,
        COTIUSDT,
        STPTUSDT,
        WTCUSDT,
        DATAUSDT,
        CTSIUSDT,
        HIVEUSDT,
        CHRUSDT,
        GXSUSDT,
        ARDRUSDT,
        MDTUSDT,
        STMXUSDT,
        LRCUSDT,
        REPUSDT,
        KNCUSDT,
        PNTUSDT,
        COMPUSDT,
        SCUSDT,
        ZENUSDT,
        SNXUSDT,
        VTHOUSDT,
        DGBUSDT,
        SXPUSDT,
        GBPUSDT,
        MKRUSDT,
        DCRUSDT,
        STORJUSDT,
        MANAUSDT,
        AUDUSDT,
        YFIUSDT,
        SRMUSDT,
        BALUSDT,
        JSTUSDT,
        BLZUSDT,
        KMDUSDT,
        IRISUSDT,
        SOLUSDT,
        ANTUSDT,
        SANDUSDT,
        CRVUSDT,
        DOTUSDT,
        NMRUSDT,
        OCEANUSDT,
        LUNAUSDT,
        RSRUSDT,
        PAXGUSDT,
        WNXMUSDT,
        TRBUSDT,
        BZRXUSDT,
        YFIIUSDT,
        SUSHIUSDT,
        EGLDUSDT,
        RUNEUSDT,
        FIOUSDT,
        KSMUSDT,
        DIAUSDT,
        UMAUSDT,
        BELUSDT,
        WINGUSDT,
        UNIUSDT,
        OXTUSDT,
        NBSUSDT,
        SUNUSDT,
        AVAXUSDT,
        HNTUSDT,
        FLMUSDT,
        ORNUSDT,
        UTKUSDT,
        XVSUSDT,
        ALPHAUSDT,
        NEARUSDT,
        FILUSDT,
        AAVEUSDT,
        INJUSDT,
        AUDIOUSDT,
        CTKUSDT,
        AKROUSDT,
        AXSUSDT,
        HARDUSDT,
        DNTUSDT,
        STRAXUSDT,
        ROSEUSDT,
        UNFIUSDT,
        XEMUSDT,
        AVAUSDT,
        SKLUSDT,
        SUSDUSDT,
        GRTUSDT,
        JUVUSDT,
        PSGUSDT,
        INCHUSDT, // change the name from 1INCHUSDT due to C++'s identifier naming
                  // rules.
        REEFUSDT,
        OGUSDT,
        ASRUSDT,
        ATMUSDT,
        CELOUSDT,
        RIFUSDT,
        BTCSTUSDT,
        TRUUSDT,
        CKBUSDT,
        TWTUSDT,
        FIROUSDT,
        LITUSDT,
        SFPUSDT,
        DODOUSDT,
        CAKEUSDT,
        ACMUSDT,
        BADGERUSDT,
        FISUSDT,
        OMUSDT,
        PONDUSDT,
        DEGOUSDT,
        ALICEUSDT,
        LINAUSDT,
        PERPUSDT,
        RAMPUSDT,
        SUPERUSDT,
        CFXUSDT,
        EPSUSDT,
        AUTOUSDT,
        TKOUSDT,
        PUNDIXUSDT,
        TLMUSDT,
        BTGUSDT,
        MIRUSDT,
        BARUSDT,
        FORTHUSDT,
        BURGERUSDT,
        BAKEUSDT,
        SLPUSDT,
        SHIBUSDT,
        ICPUSDT,
        ARUSDT,
        POLSUSDT,
        MDXUSDT,
        MASKUSDT,
        LPTUSDT,
        NUUSDT,
        XVGUSDT,
        ATAUSDT,
        GTCUSDT,
        TORNUSDT,
        KEEPUSDT,
        ERNUSDT,
        KLAYUSDT,
        PHAUSDT,
        BONDUSDT,
        MLNUSDT,
        DEXEUSDT,
        C98USDT,
        QNTUSDT,
        CLVUSDT,
        FLOWUSDT,
        TVKUSDT,
        MINAUSDT,
        RAYUSDT,
        FARMUSDT,
        ALPACAUSDT,
        QUICKUSDT,
        MBOXUSDT,
        REQUSDT,
        FORUSDT,
        GHSTUSDT,
        WAXPUSDT,
        TRIBEUSDT,
        GNOUSDT,
        XECUSDT,
        ELFUSDT,
        DYDXUSDT,
        VIDTUSDT,
        IDEXUSDT,
        POLYUSDT,
        USDPUSDT,
        GALAUSDT,
        ILVUSDT,
        SYSUSDT,
        DFUSDT,
        YGGUSDT,
        FIDAUSDT,
        CVPUSDT,
        FRONTUSDT,
        AGLDUSDT,
        RADUSDT,
        BETAUSDT,
        RAREUSDT,
        LAZIOUSDT,
        CHESSUSDT,
        AUCTIONUSDT,
        ADXUSDT,
        BNXUSDT,
        DARUSDT,
        MOVRUSDT,
        CITYUSDT,
        ENSUSDT,
        KP3RUSDT,
        QIUSDT,
        PORTOUSDT,
        POWRUSDT,
        VGXUSDT,
        JASMYUSDT,
        PLAUSDT,
        AMPUSDT,
        PYRUSDT,
        RNDRUSDT,
        ALCXUSDT,
        SANTOSUSDT,
        MCUSDT,
        BICOUSDT,
        FXSUSDT,
        FLUXUSDT,
        VOXELUSDT,
        HIGHUSDT,
        PEOPLEUSDT,
        CVXUSDT,
        OOKIUSDT,
        SPELLUSDT,
        JOEUSDT,
        ACHUSDT,
        IMXUSDT,
        GLMRUSDT,
        LOKAUSDT,
        API3USDT,
        SCRTUSDT,
        ANCUSDT,
        ACAUSDT,
        BTTCUSDT,
        XNOUSDT,
        WOOUSDT,
        ALPINEUSDT,
        TUSDT,
        ASTRUSDT,
        GMTUSDT,
        KDAUSDT,
        APEUSDT,
        BSWUSDT,
        BIFIUSDT,
        MULTIUSDT,
        STEEMUSDT,
        MOBUSDT,
        NEXOUSDT,
        INVALID
    };

    static std::string to_string(SYMBOL symbol) {
        switch (symbol) {
            case SYMBOL::BTCUSDT:
                return "BTCUSDT";
            case SYMBOL::ETHUSDT:
                return "ETHUSDT";
            case SYMBOL::BNBUSDT:
                return "BNBUSDT";
            case SYMBOL::NEOUSDT:
                return "NEOUSDT";
            case SYMBOL::LTCUSDT:
                return "LTCUSDT";
            case SYMBOL::QTUMUSDT:
                return "QTUMUSDT";
            case SYMBOL::ADAUSDT:
                return "ADAUSDT";
            case SYMBOL::XRPUSDT:
                return "XRPUSDT";
            case SYMBOL::EOSUSDT:
                return "EOSUSDT";
            case SYMBOL::IOTAUSDT:
                return "IOTAUSDT";
            case SYMBOL::TUSDUSDT:
                return "TUSDUSDT";
            case SYMBOL::XLMUSDT:
                return "XLMUSDT";
            case SYMBOL::ONTUSDT:
                return "ONTUSDT";
            case SYMBOL::TRXUSDT:
                return "TRXUSDT";
            case SYMBOL::ETCUSDT:
                return "ETCUSDT";
            case SYMBOL::ICXUSDT:
                return "ICXUSDT";
            case SYMBOL::NULSUSDT:
                return "NULSUSDT";
            case SYMBOL::VETUSDT:
                return "VETUSDT";
            case SYMBOL::PAXUSDT:
                return "PAXUSDT";
            case SYMBOL::USDCUSDT:
                return "USDCUSDT";
            case SYMBOL::LINKUSDT:
                return "LINKUSDT";
            case SYMBOL::WAVESUSDT:
                return "WAVESUSDT";
            case SYMBOL::BTTUSDT:
                return "BTTUSDT";
            case SYMBOL::ONGUSDT:
                return "ONGUSDT";
            case SYMBOL::HOTUSDT:
                return "HOTUSDT";
            case SYMBOL::ZILUSDT:
                return "ZILUSDT";
            case SYMBOL::ZRXUSDT:
                return "ZRXUSDT";
            case SYMBOL::FETUSDT:
                return "FETUSDT";
            case SYMBOL::BATUSDT:
                return "BATUSDT";
            case SYMBOL::XMRUSDT:
                return "XMRUSDT";
            case SYMBOL::ZECUSDT:
                return "ZECUSDT";
            case SYMBOL::IOSTUSDT:
                return "IOSTUSDT";
            case SYMBOL::CELRUSDT:
                return "CELRUSDT";
            case SYMBOL::DASHUSDT:
                return "DASHUSDT";
            case SYMBOL::OMGUSDT:
                return "OMGUSDT";
            case SYMBOL::NANOUSDT:
                return "NANOUSDT";
            case SYMBOL::THETAUSDT:
                return "THETAUSDT";
            case SYMBOL::ENJUSDT:
                return "ENJUSDT";
            case SYMBOL::MITHUSDT:
                return "MITHUSDT";
            case SYMBOL::MATICUSDT:
                return "MATICUSDT";
            case SYMBOL::ATOMUSDT:
                return "ATOMUSDT";
            case SYMBOL::TFUELUSDT:
                return "TFUELUSDT";
            case SYMBOL::ONEUSDT:
                return "ONEUSDT";
            case SYMBOL::FTMUSDT:
                return "FTMUSDT";
            case SYMBOL::ALGOUSDT:
                return "ALGOUSDT";
            case SYMBOL::GTOUSDT:
                return "GTOUSDT";
            case SYMBOL::DOGEUSDT:
                return "DOGEUSDT";
            case SYMBOL::DUSKUSDT:
                return "DUSKUSDT";
            case SYMBOL::ANKRUSDT:
                return "ANKRUSDT";
            case SYMBOL::WINUSDT:
                return "WINUSDT";
            case SYMBOL::COSUSDT:
                return "COSUSDT";
            case SYMBOL::NPXSUSDT:
                return "NPXSUSDT";
            case SYMBOL::COCOSUSDT:
                return "COCOSUSDT";
            case SYMBOL::MTLUSDT:
                return "MTLUSDT";
            case SYMBOL::TOMOUSDT:
                return "TOMOUSDT";
            case SYMBOL::PERLUSDT:
                return "PERLUSDT";
            case SYMBOL::FUNUSDT:
                return "FUNUSDT";
            case SYMBOL::WANUSDT:
                return "WANUSDT";
            case SYMBOL::CVCUSDT:
                return "CVCUSDT";
            case SYMBOL::DENTUSDT:
                return "DENTUSDT";
            case SYMBOL::DOCKUSDT:
                return "DOCKUSDT";
            case SYMBOL::MFTUSDT:
                return "MFTUSDT";
            case SYMBOL::KEYUSDT:
                return "KEYUSDT";
            case SYMBOL::CHZUSDT:
                return "CHZUSDT";
            case SYMBOL::BANDUSDT:
                return "BANDUSDT";
            case SYMBOL::BUSDUSDT:
                return "BUSDUSDT";
            case SYMBOL::BEAMUSDT:
                return "BEAMUSDT";
            case SYMBOL::XTZUSDT:
                return "XTZUSDT";
            case SYMBOL::RENUSDT:
                return "RENUSDT";
            case SYMBOL::RVNUSDT:
                return "RVNUSDT";
            case SYMBOL::HBARUSDT:
                return "HBARUSDT";
            case SYMBOL::NKNUSDT:
                return "NKNUSDT";
            case SYMBOL::KAVAUSDT:
                return "KAVAUSDT";
            case SYMBOL::STXUSDT:
                return "STXUSDT";
            case SYMBOL::ARPAUSDT:
                return "ARPAUSDT";
            case SYMBOL::RLCUSDT:
                return "RLCUSDT";
            case SYMBOL::IOTXUSDT:
                return "IOTXUSDT";
            case SYMBOL::CTXCUSDT:
                return "CTXCUSDT";
            case SYMBOL::BCHUSDT:
                return "BCHUSDT";
            case SYMBOL::TROYUSDT:
                return "TROYUSDT";
            case SYMBOL::VITEUSDT:
                return "VITEUSDT";
            case SYMBOL::FTTUSDT:
                return "FTTUSDT";
            case SYMBOL::EURUSDT:
                return "EURUSDT";
            case SYMBOL::OGNUSDT:
                return "OGNUSDT";
            case SYMBOL::DREPUSDT:
                return "DREPUSDT";
            case SYMBOL::TCTUSDT:
                return "TCTUSDT";
            case SYMBOL::WRXUSDT:
                return "WRXUSDT";
            case SYMBOL::BNTUSDT:
                return "BNTUSDT";
            case SYMBOL::LSKUSDT:
                return "LSKUSDT";
            case SYMBOL::BTSUSDT:
                return "BTSUSDT";
            case SYMBOL::LTOUSDT:
                return "LTOUSDT";
            case SYMBOL::AIONUSDT:
                return "AIONUSDT";
            case SYMBOL::MBLUSDT:
                return "MBLUSDT";
            case SYMBOL::COTIUSDT:
                return "COTIUSDT";
            case SYMBOL::STPTUSDT:
                return "STPTUSDT";
            case SYMBOL::WTCUSDT:
                return "WTCUSDT";
            case SYMBOL::DATAUSDT:
                return "DATAUSDT";
            case SYMBOL::CTSIUSDT:
                return "CTSIUSDT";
            case SYMBOL::HIVEUSDT:
                return "HIVEUSDT";
            case SYMBOL::CHRUSDT:
                return "CHRUSDT";
            case SYMBOL::GXSUSDT:
                return "GXSUSDT";
            case SYMBOL::ARDRUSDT:
                return "ARDRUSDT";
            case SYMBOL::MDTUSDT:
                return "MDTUSDT";
            case SYMBOL::STMXUSDT:
                return "STMXUSDT";
            case SYMBOL::LRCUSDT:
                return "LRCUSDT";
            case SYMBOL::REPUSDT:
                return "REPUSDT";
            case SYMBOL::KNCUSDT:
                return "KNCUSDT";
            case SYMBOL::PNTUSDT:
                return "PNTUSDT";
            case SYMBOL::COMPUSDT:
                return "COMPUSDT";
            case SYMBOL::SCUSDT:
                return "SCUSDT";
            case SYMBOL::ZENUSDT:
                return "ZENUSDT";
            case SYMBOL::SNXUSDT:
                return "SNXUSDT";
            case SYMBOL::VTHOUSDT:
                return "VTHOUSDT";
            case SYMBOL::DGBUSDT:
                return "DGBUSDT";
            case SYMBOL::SXPUSDT:
                return "SXPUSDT";
            case SYMBOL::GBPUSDT:
                return "GBPUSDT";
            case SYMBOL::MKRUSDT:
                return "MKRUSDT";
            case SYMBOL::DCRUSDT:
                return "DCRUSDT";
            case SYMBOL::STORJUSDT:
                return "STORJUSDT";
            case SYMBOL::MANAUSDT:
                return "MANAUSDT";
            case SYMBOL::AUDUSDT:
                return "AUDUSDT";
            case SYMBOL::YFIUSDT:
                return "YFIUSDT";
            case SYMBOL::SRMUSDT:
                return "SRMUSDT";
            case SYMBOL::BALUSDT:
                return "BALUSDT";
            case SYMBOL::JSTUSDT:
                return "JSTUSDT";
            case SYMBOL::BLZUSDT:
                return "BLZUSDT";
            case SYMBOL::KMDUSDT:
                return "KMDUSDT";
            case SYMBOL::IRISUSDT:
                return "IRISUSDT";
            case SYMBOL::SOLUSDT:
                return "SOLUSDT";
            case SYMBOL::ANTUSDT:
                return "ANTUSDT";
            case SYMBOL::SANDUSDT:
                return "SANDUSDT";
            case SYMBOL::CRVUSDT:
                return "CRVUSDT";
            case SYMBOL::DOTUSDT:
                return "DOTUSDT";
            case SYMBOL::NMRUSDT:
                return "NMRUSDT";
            case SYMBOL::OCEANUSDT:
                return "OCEANUSDT";
            case SYMBOL::LUNAUSDT:
                return "LUNAUSDT";
            case SYMBOL::RSRUSDT:
                return "RSRUSDT";
            case SYMBOL::PAXGUSDT:
                return "PAXGUSDT";
            case SYMBOL::WNXMUSDT:
                return "WNXMUSDT";
            case SYMBOL::TRBUSDT:
                return "TRBUSDT";
            case SYMBOL::BZRXUSDT:
                return "BZRXUSDT";
            case SYMBOL::YFIIUSDT:
                return "YFIIUSDT";
            case SYMBOL::SUSHIUSDT:
                return "SUSHIUSDT";
            case SYMBOL::EGLDUSDT:
                return "EGLDUSDT";
            case SYMBOL::RUNEUSDT:
                return "RUNEUSDT";
            case SYMBOL::FIOUSDT:
                return "FIOUSDT";
            case SYMBOL::KSMUSDT:
                return "KSMUSDT";
            case SYMBOL::DIAUSDT:
                return "DIAUSDT";
            case SYMBOL::UMAUSDT:
                return "UMAUSDT";
            case SYMBOL::BELUSDT:
                return "BELUSDT";
            case SYMBOL::WINGUSDT:
                return "WINGUSDT";
            case SYMBOL::UNIUSDT:
                return "UNIUSDT";
            case SYMBOL::OXTUSDT:
                return "OXTUSDT";
            case SYMBOL::NBSUSDT:
                return "NBSUSDT";
            case SYMBOL::SUNUSDT:
                return "SUNUSDT";
            case SYMBOL::AVAXUSDT:
                return "AVAXUSDT";
            case SYMBOL::HNTUSDT:
                return "HNTUSDT";
            case SYMBOL::FLMUSDT:
                return "FLMUSDT";
            case SYMBOL::ORNUSDT:
                return "ORNUSDT";
            case SYMBOL::UTKUSDT:
                return "UTKUSDT";
            case SYMBOL::XVSUSDT:
                return "XVSUSDT";
            case SYMBOL::ALPHAUSDT:
                return "ALPHAUSDT";
            case SYMBOL::NEARUSDT:
                return "NEARUSDT";
            case SYMBOL::FILUSDT:
                return "FILUSDT";
            case SYMBOL::AAVEUSDT:
                return "AAVEUSDT";
            case SYMBOL::INJUSDT:
                return "INJUSDT";
            case SYMBOL::AUDIOUSDT:
                return "AUDIOUSDT";
            case SYMBOL::CTKUSDT:
                return "CTKUSDT";
            case SYMBOL::AKROUSDT:
                return "AKROUSDT";
            case SYMBOL::AXSUSDT:
                return "AXSUSDT";
            case SYMBOL::HARDUSDT:
                return "HARDUSDT";
            case SYMBOL::DNTUSDT:
                return "DNTUSDT";
            case SYMBOL::STRAXUSDT:
                return "STRAXUSDT";
            case SYMBOL::ROSEUSDT:
                return "ROSEUSDT";
            case SYMBOL::UNFIUSDT:
                return "UNFIUSDT";
            case SYMBOL::XEMUSDT:
                return "XEMUSDT";
            case SYMBOL::AVAUSDT:
                return "AVAUSDT";
            case SYMBOL::SKLUSDT:
                return "SKLUSDT";
            case SYMBOL::SUSDUSDT:
                return "SUSDUSDT";
            case SYMBOL::GRTUSDT:
                return "GRTUSDT";
            case SYMBOL::JUVUSDT:
                return "JUVUSDT";
            case SYMBOL::PSGUSDT:
                return "PSGUSDT";
            case SYMBOL::INCHUSDT:
                return "INCHUSDT";
            case SYMBOL::REEFUSDT:
                return "REEFUSDT";
            case SYMBOL::OGUSDT:
                return "OGUSDT";
            case SYMBOL::ASRUSDT:
                return "ASRUSDT";
            case SYMBOL::ATMUSDT:
                return "ATMUSDT";
            case SYMBOL::CELOUSDT:
                return "CELOUSDT";
            case SYMBOL::RIFUSDT:
                return "RIFUSDT";
            case SYMBOL::BTCSTUSDT:
                return "BTCSTUSDT";
            case SYMBOL::TRUUSDT:
                return "TRUUSDT";
            case SYMBOL::CKBUSDT:
                return "CKBUSDT";
            case SYMBOL::TWTUSDT:
                return "TWTUSDT";
            case SYMBOL::FIROUSDT:
                return "FIROUSDT";
            case SYMBOL::LITUSDT:
                return "LITUSDT";
            case SYMBOL::SFPUSDT:
                return "SFPUSDT";
            case SYMBOL::DODOUSDT:
                return "DODOUSDT";
            case SYMBOL::CAKEUSDT:
                return "CAKEUSDT";
            case SYMBOL::ACMUSDT:
                return "ACMUSDT";
            case SYMBOL::BADGERUSDT:
                return "BADGERUSDT";
            case SYMBOL::FISUSDT:
                return "FISUSDT";
            case SYMBOL::OMUSDT:
                return "OMUSDT";
            case SYMBOL::PONDUSDT:
                return "PONDUSDT";
            case SYMBOL::DEGOUSDT:
                return "DEGOUSDT";
            case SYMBOL::ALICEUSDT:
                return "ALICEUSDT";
            case SYMBOL::LINAUSDT:
                return "LINAUSDT";
            case SYMBOL::PERPUSDT:
                return "PERPUSDT";
            case SYMBOL::RAMPUSDT:
                return "RAMPUSDT";
            case SYMBOL::SUPERUSDT:
                return "SUPERUSDT";
            case SYMBOL::CFXUSDT:
                return "CFXUSDT";
            case SYMBOL::EPSUSDT:
                return "EPSUSDT";
            case SYMBOL::AUTOUSDT:
                return "AUTOUSDT";
            case SYMBOL::TKOUSDT:
                return "TKOUSDT";
            case SYMBOL::PUNDIXUSDT:
                return "PUNDIXUSDT";
            case SYMBOL::TLMUSDT:
                return "TLMUSDT";
            case SYMBOL::BTGUSDT:
                return "BTGUSDT";
            case SYMBOL::MIRUSDT:
                return "MIRUSDT";
            case SYMBOL::BARUSDT:
                return "BARUSDT";
            case SYMBOL::FORTHUSDT:
                return "FORTHUSDT";
            case SYMBOL::BURGERUSDT:
                return "BURGERUSDT";
            case SYMBOL::BAKEUSDT:
                return "BAKEUSDT";
            case SYMBOL::SLPUSDT:
                return "SLPUSDT";
            case SYMBOL::SHIBUSDT:
                return "SHIBUSDT";
            case SYMBOL::ICPUSDT:
                return "ICPUSDT";
            case SYMBOL::ARUSDT:
                return "ARUSDT";
            case SYMBOL::POLSUSDT:
                return "POLSUSDT";
            case SYMBOL::MDXUSDT:
                return "MDXUSDT";
            case SYMBOL::MASKUSDT:
                return "MASKUSDT";
            case SYMBOL::LPTUSDT:
                return "LPTUSDT";
            case SYMBOL::NUUSDT:
                return "NUUSDT";
            case SYMBOL::XVGUSDT:
                return "XVGUSDT";
            case SYMBOL::ATAUSDT:
                return "ATAUSDT";
            case SYMBOL::GTCUSDT:
                return "GTCUSDT";
            case SYMBOL::TORNUSDT:
                return "TORNUSDT";
            case SYMBOL::KEEPUSDT:
                return "KEEPUSDT";
            case SYMBOL::ERNUSDT:
                return "ERNUSDT";
            case SYMBOL::KLAYUSDT:
                return "KLAYUSDT";
            case SYMBOL::PHAUSDT:
                return "PHAUSDT";
            case SYMBOL::BONDUSDT:
                return "BONDUSDT";
            case SYMBOL::MLNUSDT:
                return "MLNUSDT";
            case SYMBOL::DEXEUSDT:
                return "DEXEUSDT";
            case SYMBOL::C98USDT:
                return "C98USDT";
            case SYMBOL::QNTUSDT:
                return "QNTUSDT";
            case SYMBOL::CLVUSDT:
                return "CLVUSDT";
            case SYMBOL::FLOWUSDT:
                return "FLOWUSDT";
            case SYMBOL::TVKUSDT:
                return "TVKUSDT";
            case SYMBOL::MINAUSDT:
                return "MINAUSDT";
            case SYMBOL::RAYUSDT:
                return "RAYUSDT";
            case SYMBOL::FARMUSDT:
                return "FARMUSDT";
            case SYMBOL::ALPACAUSDT:
                return "ALPACAUSDT";
            case SYMBOL::QUICKUSDT:
                return "QUICKUSDT";
            case SYMBOL::MBOXUSDT:
                return "MBOXUSDT";
            case SYMBOL::REQUSDT:
                return "REQUSDT";
            case SYMBOL::FORUSDT:
                return "FORUSDT";
            case SYMBOL::GHSTUSDT:
                return "GHSTUSDT";
            case SYMBOL::WAXPUSDT:
                return "WAXPUSDT";
            case SYMBOL::TRIBEUSDT:
                return "TRIBEUSDT";
            case SYMBOL::GNOUSDT:
                return "GNOUSDT";
            case SYMBOL::XECUSDT:
                return "XECUSDT";
            case SYMBOL::ELFUSDT:
                return "ELFUSDT";
            case SYMBOL::DYDXUSDT:
                return "DYDXUSDT";
            case SYMBOL::VIDTUSDT:
                return "VIDTUSDT";
            case SYMBOL::IDEXUSDT:
                return "IDEXUSDT";
            case SYMBOL::POLYUSDT:
                return "POLYUSDT";
            case SYMBOL::USDPUSDT:
                return "USDPUSDT";
            case SYMBOL::GALAUSDT:
                return "GALAUSDT";
            case SYMBOL::ILVUSDT:
                return "ILVUSDT";
            case SYMBOL::SYSUSDT:
                return "SYSUSDT";
            case SYMBOL::DFUSDT:
                return "DFUSDT";
            case SYMBOL::YGGUSDT:
                return "YGGUSDT";
            case SYMBOL::FIDAUSDT:
                return "FIDAUSDT";
            case SYMBOL::CVPUSDT:
                return "CVPUSDT";
            case SYMBOL::FRONTUSDT:
                return "FRONTUSDT";
            case SYMBOL::AGLDUSDT:
                return "AGLDUSDT";
            case SYMBOL::RADUSDT:
                return "RADUSDT";
            case SYMBOL::BETAUSDT:
                return "BETAUSDT";
            case SYMBOL::RAREUSDT:
                return "RAREUSDT";
            case SYMBOL::LAZIOUSDT:
                return "LAZIOUSDT";
            case SYMBOL::CHESSUSDT:
                return "CHESSUSDT";
            case SYMBOL::AUCTIONUSDT:
                return "AUCTIONUSDT";
            case SYMBOL::ADXUSDT:
                return "ADXUSDT";
            case SYMBOL::BNXUSDT:
                return "BNXUSDT";
            case SYMBOL::DARUSDT:
                return "DARUSDT";
            case SYMBOL::MOVRUSDT:
                return "MOVRUSDT";
            case SYMBOL::CITYUSDT:
                return "CITYUSDT";
            case SYMBOL::ENSUSDT:
                return "ENSUSDT";
            case SYMBOL::KP3RUSDT:
                return "KP3RUSDT";
            case SYMBOL::QIUSDT:
                return "QIUSDT";
            case SYMBOL::PORTOUSDT:
                return "PORTOUSDT";
            case SYMBOL::POWRUSDT:
                return "POWRUSDT";
            case SYMBOL::VGXUSDT:
                return "VGXUSDT";
            case SYMBOL::JASMYUSDT:
                return "JASMYUSDT";
            case SYMBOL::PLAUSDT:
                return "PLAUSDT";
            case SYMBOL::AMPUSDT:
                return "AMPUSDT";
            case SYMBOL::PYRUSDT:
                return "PYRUSDT";
            case SYMBOL::RNDRUSDT:
                return "RNDRUSDT";
            case SYMBOL::ALCXUSDT:
                return "ALCXUSDT";
            case SYMBOL::SANTOSUSDT:
                return "SANTOSUSDT";
            case SYMBOL::MCUSDT:
                return "MCUSDT";
            case SYMBOL::BICOUSDT:
                return "BICOUSDT";
            case SYMBOL::FXSUSDT:
                return "FXSUSDT";
            case SYMBOL::FLUXUSDT:
                return "FLUXUSDT";
            case SYMBOL::VOXELUSDT:
                return "VOXELUSDT";
            case SYMBOL::HIGHUSDT:
                return "HIGHUSDT";
            case SYMBOL::PEOPLEUSDT:
                return "PEOPLEUSDT";
            case SYMBOL::CVXUSDT:
                return "CVXUSDT";
            case SYMBOL::OOKIUSDT:
                return "OOKIUSDT";
            case SYMBOL::SPELLUSDT:
                return "SPELLUSDT";
            case SYMBOL::JOEUSDT:
                return "JOEUSDT";
            case SYMBOL::ACHUSDT:
                return "ACHUSDT";
            case SYMBOL::IMXUSDT:
                return "IMXUSDT";
            case SYMBOL::GLMRUSDT:
                return "GLMRUSDT";
            case SYMBOL::LOKAUSDT:
                return "LOKAUSDT";
            case SYMBOL::API3USDT:
                return "API3USDT";
            case SYMBOL::SCRTUSDT:
                return "SCRTUSDT";
            case SYMBOL::ANCUSDT:
                return "ANCUSDT";
            case SYMBOL::ACAUSDT:
                return "ACAUSDT";
            case SYMBOL::BTTCUSDT:
                return "BTTCUSDT";
            case SYMBOL::XNOUSDT:
                return "XNOUSDT";
            case SYMBOL::WOOUSDT:
                return "WOOUSDT";
            case SYMBOL::ALPINEUSDT:
                return "ALPINEUSDT";
            case SYMBOL::TUSDT:
                return "TUSDT";
            case SYMBOL::ASTRUSDT:
                return "ASTRUSDT";
            case SYMBOL::GMTUSDT:
                return "GMTUSDT";
            case SYMBOL::KDAUSDT:
                return "KDAUSDT";
            case SYMBOL::APEUSDT:
                return "APEUSDT";
            case SYMBOL::BSWUSDT:
                return "BSWUSDT";
            case SYMBOL::BIFIUSDT:
                return "BIFIUSDT";
            case SYMBOL::MULTIUSDT:
                return "MULTIUSDT";
            case SYMBOL::STEEMUSDT:
                return "STEEMUSDT";
            case SYMBOL::MOBUSDT:
                return "MOBUSDT";
            case SYMBOL::NEXOUSDT:
                return "NEXOUSDT";
            case SYMBOL::INVALID:
                return "INVALID";
            default:
                return "INVALID";
        }
    }
} // namespace sim::common

#endif
