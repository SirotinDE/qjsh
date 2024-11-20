#include "Widget.h"

#include <qjsh.h>

using namespace qjsh;

Window::Window(const QJsonObject &j)
    : width(Extract(j,"width"))
    , height(Extract(j,"height"))
    , scale(ExtractOpt(j,"scale"))
    , name(ExtractOpt(j,"name"))
{}

QJsonObject Window::toJson() const {
    return {
        {"width", width},
        {"height", height},
        {"scale", qjsh::optToValue(scale)},
        {"name", qjsh::optToValue(name)}
    };
}

Property::Property(const QJsonObject &j)
    : name(Extract(j,"name"))
    , value(ExtractOpt(j,"value"))
{}

QJsonObject Property::toJson() const {
    return {
        {"name", name},
        {"value", qjsh::optToValue(value)},
    };
}

Widget::Widget(const QJsonObject &j)
    : authors(Extract(j,"authors"))
    , properties(Extract(j,"properties").toObjectsVector<Property>())
    , idleAt(ExtractOpt(j,"idleAt"))
    , extraProperties(ExtractOpt(j,"extraProperties").toObjectsVector<Property>())
    , window(ExtractOpt(j,"window").toObject<Window>())
{}

QJsonObject Widget::toJson() const {
    return {
        {"authors", qjsh::arrayToValue(authors)},
        {"properties", qjsh::objArrayToValue(properties)},
        {"idleAt", qjsh::optDtToValue(idleAt)},
        {"extraProperties", qjsh::optObjArrayToValue(extraProperties)},
        {"window", qjsh::optObjToValue(window)}
    };
}

