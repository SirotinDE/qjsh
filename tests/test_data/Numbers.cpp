#include "Numbers.h"

#include <qjsh.h>

using namespace qjsh;

Numbers::Numbers(const QJsonObject &j)
    : i(Extract(j,"i"))
    , oi(ExtractOpt(j,"oi"))
    , vi(Extract(j,"vi"))
    , ovi(ExtractOpt(j,"ovi"))
    , qi(Extract(j,"qi"))
    , oqi(ExtractOpt(j,"oqi"))
    , vqi(Extract(j,"vqi"))
    , ovqi(ExtractOpt(j,"ovqi"))
    , d(Extract(j,"d"))
    , od(ExtractOpt(j,"od"))
    , vd(Extract(j,"vd"))
    , ovd(ExtractOpt(j,"ovd"))
    , b(Extract(j,"b"))
    , ob(ExtractOpt(j,"ob"))
    , vb(Extract(j,"vb"))
    , ovb(ExtractOpt(j,"ovb"))
{}

QJsonObject Numbers::toJson() const {
    return {
        {"i", i},
        {"oi", qjsh::optToValue(oi)},
        {"vi", qjsh::arrayToValue(vi)},
        {"ovi", qjsh::optArrayToValue(ovi)},
        {"qi", qi},
        {"oqi", qjsh::optToValue(oqi)},
        {"vqi", qjsh::arrayToValue(vqi)},
        {"ovqi", qjsh::optArrayToValue(ovqi)},
        {"d", d},
        {"od", qjsh::optToValue(od)},
        {"vd", qjsh::arrayToValue(vd)},
        {"ovd", qjsh::optArrayToValue(ovd)},
        {"b", b},
        {"ob", qjsh::optToValue(ob)},
        {"vb", qjsh::arrayToValue(vb)},
        {"ovb", qjsh::optArrayToValue(ovb)},
    };
}

