# qjsh

QJsonHelper header only library

Helps parse and serialize QJsonObject

## Usage

Describe the structure with constructors and method toJson() like in code below

```cpp
struct Property {
    QString name;
    std::optional<QString> value;

    Property(const QJsonObject& j);
    Property() = default;
    QJsonObject toJson() const;
};
```

Use the library for compact parse and serialization

```cpp
#include <qjsh.h>
using namespace qjsh;

Property::Property(const QJsonObject &j)
    : name(Extract(j,"name"))
    , value(ExtractOpt(j,"value"))
{}

QJsonObject Property::toJson() const {
    return {
        {"name", name},
        {"value", optToValue(value)},
    };
}

```

More examples

```cpp
// header file
#include <optional>
#include <QString>
#include <QVector>
#include "property.h"

struct Window {
    int width;
    int height;
    std::optional<double> scale;
    std::optional<QString> name;

    Window(const QJsonObject& j);
    Window() = default;
    QJsonObject toJson() const;
};

struct Widget {
    QVector<QString> authors;
    QVector<Property> properties;
    std::optional<QVector<Property>> extraProperties;
    std::optional<Window> window;

    Widget(const QJsonObject& j);
    Widget() = default;
    QJsonObject toJson() const;
};

// cpp file

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
        {"scale", optToValue(scale)},
        {"name", optToValue(name)}
    };
}

Widget::Widget(const QJsonObject &j)
    : authors(Extract(j,"authors"))
    , properties(Extract(j,"properties").toObjectsVector<Property>())
    , extraProperties(ExtractOpt(j,"extraProperties").toObjectsVector<Property>())
    , window(ExtractOpt(j,"window").toObject<Window>())
{}

QJsonObject Widget::toJson() const {
    return {
        {"authors", arrayToValue(authors)},
        {"properties", objArrayToValue(properties)},
        {"extraProperties", optObjArrayToValue(extraProperties)},
        {"window", optObjToValue(window)}
    };
}

```

Usage example

```cpp

#include <QJsonDocument>
#include <qjsh_util.h>

static QJsonObject getJson(const char* c) {
    auto jsonDocument = QJsonDocument::fromJson(c);
    return jsonDocument.object();
}

constexpr auto data = R"(
{
    "widget": {
        "authors": [
            "Dmitry"
        ],
        "properties": [
            {
                "name": "readonly",
                "value": "true"
            },
            {
                "name": "reaction"
            }
        ],
        "extraProperties": [
            {
                "name": "hello",
                "value": "world"
            }
        ],
        "window": {
            "name": "test",
            "width": 500,
            "height": 500,
            "scale": 1.25
        }
    }
}
)";

auto obj = getJson(data);
auto widgetObj = obj["widget"].toObject();

// usage without exception
auto widgetOpt = qjsh::parse<Numbers>(widgetObj);
if (!widgetOpt) {
    return;
}

// with exception if wrong json
try {
    Widget widget(widgetObj);
// use widget
} catch (...) {
    
}



```
