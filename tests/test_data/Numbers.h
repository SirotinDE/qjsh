#pragma once

#include <optional>

#include <QString>
#include <QJsonObject>

struct Numbers {
    int i{};
    std::optional<int> oi;
    QVector<int> vi;
    std::optional<QVector<int>> ovi;

    qint64 qi{};
    std::optional<qint64> oqi;
    QVector<qint64> vqi;
    std::optional<QVector<qint64>> ovqi;

    double d{};
    std::optional<double> od;
    QVector<double> vd;
    std::optional<QVector<double>> ovd;

    bool b{};
    std::optional<bool> ob;
    QVector<bool> vb;
    std::optional<QVector<bool>> ovb;

    Numbers(const QJsonObject& j);
    Numbers() = default;
    QJsonObject toJson() const;
};
