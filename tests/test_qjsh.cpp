#include <QJsonDocument>

#include <gtest/gtest.h>

#include "test_data/Widget.h"
#include "test_data/Numbers.h"

#include <qjsh_util.h>


static QJsonObject getObject(const char* c) {
    auto jsonDocument = QJsonDocument::fromJson(c);
    return jsonDocument.object();
}

TEST(Json, Widget)
{
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
    auto obj = getObject(data);

    Widget w(obj["widget"].toObject());
    EXPECT_EQ(w.authors.size(), 1);
    EXPECT_EQ(w.authors[0], "Dmitry");
    EXPECT_EQ(w.properties.size(), 2);
    EXPECT_EQ(w.properties[0].name, "readonly");
    EXPECT_EQ(w.properties[0].value, "true");
    EXPECT_EQ(w.properties[1].name, "reaction");
    EXPECT_EQ(w.extraProperties.has_value(), true);
    EXPECT_EQ(w.extraProperties->size(), 1);
    EXPECT_EQ(w.extraProperties->at(0).name, "hello");
    EXPECT_EQ(w.extraProperties->at(0).value, "world");
    EXPECT_EQ(w.window.has_value(), true);
    EXPECT_EQ(w.window->name, "test");
    EXPECT_EQ(w.window->width, 500);
    EXPECT_EQ(w.window->height, 500);
    EXPECT_EQ(w.window->scale, 1.25);
}

TEST(Json, Numbers)
{
    Numbers numbers;
    numbers.i = 1;
    numbers.oi = 2;
    numbers.vi = {3,4};
    numbers.ovi = {5,6};
    numbers.qi = 10000000001;
    numbers.oqi = 10000000002;
    numbers.vqi = {10000000003, 10000000004};
    numbers.ovqi = {10000000005, 10000000006};
    numbers.d = 1.1;
    numbers.od = 2.1;
    numbers.vd = {3.1, 4.1};
    numbers.ovd = {5.1, 6.1};
    numbers.b = true;
    numbers.ob = true;
    numbers.vb = {true, false};
    numbers.ovb = {true, false};

    auto json = numbers.toJson();
    Numbers numbersFromJson(json);

    EXPECT_EQ(numbers.i, numbersFromJson.i);
    EXPECT_EQ(numbers.oi, numbersFromJson.oi);
    EXPECT_EQ(numbers.vi, numbersFromJson.vi);
    EXPECT_EQ(numbers.ovi, numbersFromJson.ovi);

    EXPECT_EQ(numbers.qi, numbersFromJson.qi);
    EXPECT_EQ(numbers.oqi, numbersFromJson.oqi);
    EXPECT_EQ(numbers.vqi, numbersFromJson.vqi);
    EXPECT_EQ(numbers.ovqi, numbersFromJson.ovqi);

    EXPECT_EQ(numbers.d, numbersFromJson.d);
    EXPECT_EQ(numbers.od, numbersFromJson.od);
    EXPECT_EQ(numbers.vd, numbersFromJson.vd);
    EXPECT_EQ(numbers.ovd, numbersFromJson.ovd);

    EXPECT_EQ(numbers.b, numbersFromJson.b);
    EXPECT_EQ(numbers.ob, numbersFromJson.ob);
    EXPECT_EQ(numbers.vb, numbersFromJson.vb);
    EXPECT_EQ(numbers.ovb, numbersFromJson.ovb);
}

TEST(Json, NumbersEmptyOpt)
{
    Numbers numbers;
    numbers.i = 1;
    numbers.vi = {3,4};
    numbers.qi = 10000000001;
    numbers.vqi = {10000000003, 10000000004};
    numbers.d = 1.1;
    numbers.vd = {3.1, 4.1};
    numbers.b = true;
    numbers.vb = {true, false};

    auto json = numbers.toJson();
    auto numbersFromJson = qjsh::parse<Numbers>(json);
    EXPECT_EQ(numbersFromJson.has_value(), true);

    EXPECT_EQ(numbers.i, numbersFromJson->i);
    EXPECT_EQ(numbers.oi, numbersFromJson->oi);
    EXPECT_EQ(numbers.vi, numbersFromJson->vi);
    EXPECT_EQ(numbers.ovi, numbersFromJson->ovi);

    EXPECT_EQ(numbers.qi, numbersFromJson->qi);
    EXPECT_EQ(numbers.oqi, numbersFromJson->oqi);
    EXPECT_EQ(numbers.vqi, numbersFromJson->vqi);
    EXPECT_EQ(numbers.ovqi, numbersFromJson->ovqi);

    EXPECT_EQ(numbers.d, numbersFromJson->d);
    EXPECT_EQ(numbers.od, numbersFromJson->od);
    EXPECT_EQ(numbers.vd, numbersFromJson->vd);
    EXPECT_EQ(numbers.ovd, numbersFromJson->ovd);

    EXPECT_EQ(numbers.b, numbersFromJson->b);
    EXPECT_EQ(numbers.ob, numbersFromJson->ob);
    EXPECT_EQ(numbers.vb, numbersFromJson->vb);
    EXPECT_EQ(numbers.ovb, numbersFromJson->ovb);
}

TEST(Json, NumbersNotANumber)
{

constexpr auto i_data = R"(
{
    "i": "string!",
}

)";
    auto value = getObject(i_data);
    auto obj = value["widget"].toObject();
    auto numbers = qjsh::parse<Numbers>(obj);
    EXPECT_EQ(numbers.has_value(), false);
}

