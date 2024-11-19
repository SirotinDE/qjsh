#pragma once

#include <optional>

#include <QString>
#include <QJsonObject>

struct Window {
    int width;
    int height;
    std::optional<double> scale;
    std::optional<QString> name;

    Window(const QJsonObject& j);
    Window() = default;
    QJsonObject toJson() const;
};

struct Property {
    QString name;
    std::optional<QString> value;

    Property(const QJsonObject& j);
    Property() = default;
    QJsonObject toJson() const;;
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
