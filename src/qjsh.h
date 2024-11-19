#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

namespace qjsh {

struct Extract {
    QJsonValueConstRef v;
    Extract(QJsonValueConstRef v) : v(v) {}
    Extract(const QJsonObject& o, const QString& s) : v(const_cast<QJsonObject&>(o)[s]) {
        if (v.isNull() || v.isUndefined()) {
            std::string error("QJsonObject have no value " + s.toStdString());
            throw std::runtime_error(error);
        }
    }

    operator std::optional<bool>() = delete;
    inline operator bool() {
        if (!v.isBool()) {
            throw std::runtime_error("value is not bool");
        }
        return v.toBool();
    }

    operator std::optional<int>() = delete;
    inline operator int() {
        if (!v.isDouble()) {
            throw std::runtime_error("value is not number");
        }
        return v.toInt();
    }

    operator std::optional<qint64>() = delete;
    inline operator qint64() {
        if (!v.isDouble()) {
            throw std::runtime_error("value is not number");
        }
        return v.toInteger();
    }

    operator std::optional<double>() = delete;
    inline operator double() {
        if (!v.isDouble()) {
            throw std::runtime_error("value is not number");
        }
        return v.toDouble();
    }

    operator std::optional<QString>() = delete;
    inline operator QString() {
        if (!v.isString()) {
            throw std::runtime_error("value is not string");
        }
        return v.toString();
    }

    template <typename T>
    T toObject() {
        if (!v.isObject()) {
            throw std::runtime_error("value is not object");
        }
        return T(v.toObject());
    }

    template <typename T>
    QVector<T> toVector() {
        if (!v.isArray()) {
            throw std::runtime_error("value is not array");
        }
        auto arr = v.toArray();
        QVector<T> answer;
        answer.reserve(arr.size());
        for (const auto& value : arr) {
            answer.push_back(Extract(value));
        }
        return answer;
    }

    template <typename T>
    QVector<T> toObjectsVector() {
        if (!v.isArray()) {
            throw std::runtime_error("value is not array");
        }
        auto arr = v.toArray();
        QVector<T> answer;
        answer.reserve(arr.size());
        for (const auto& value : arr) {
            answer.push_back(Extract(value).toObject<T>());
        }
        return answer;
    }

    operator std::optional<QVector<QString>>() = delete;
    inline operator QVector<QString>() {
        return toVector<QString>();
    }

    operator std::optional<QVector<int>>() = delete;
    inline operator QVector<int>() {
        return toVector<int>();
    }

    operator std::optional<QVector<qint64>>() = delete;
    inline operator QVector<qint64>() {
        return toVector<qint64>();
    }

    operator std::optional<QVector<double>>() = delete;
    inline operator QVector<double>() {
        return toVector<double>();
    }

    operator std::optional<QVector<bool>>() = delete;
    inline operator QVector<bool>() {
        return toVector<bool>();
    }
};

struct ExtractOpt {
    QJsonValueConstRef v;
    ExtractOpt(QJsonValueConstRef v) : v(v) {}
    ExtractOpt(const QJsonObject& o, const QString& s) : v(const_cast<QJsonObject&>(o)[s]) {}

    operator bool() = delete;
    inline operator std::optional<bool>() const {
        if (v.isNull() || v.isUndefined()) {
            return std::nullopt;
        }
        if (!v.isBool()) {
            throw std::runtime_error("value is not bool");
        }
        return v.toBool();
    }

    operator int() = delete;
    inline operator std::optional<int>() const {
        if (v.isNull() || v.isUndefined()) {
            return std::nullopt;
        }
        if (!v.isDouble()) {
            throw std::runtime_error("value is not number");
        }
        return v.toInt();
    }

    operator qint64() = delete;
    inline operator std::optional<qint64>() const {
        if (v.isNull() || v.isUndefined()) {
            return std::nullopt;
        }
        if (!v.isDouble()) {
            throw std::runtime_error("value is not number");
        }
        return v.toInteger();
    }

    operator double() = delete;
    inline operator std::optional<double>() const {
        if (v.isNull() || v.isUndefined()) {
            return std::nullopt;
        }
        if (!v.isDouble()) {
            throw std::runtime_error("value is not number");
        }
        return v.toDouble();
    }

    operator QString() = delete;
    inline operator std::optional<QString>() const {
        if (v.isNull() || v.isUndefined()) {
            return std::nullopt;
        }
        if (!v.isString()) {
            throw std::runtime_error("value is not string");
        }
        return v.toString();
    }

    template <typename T>
    std::optional<T> toObject() {
        if (v.isNull() || v.isUndefined()) {
            return std::nullopt;
        }
        if (!v.isObject()) {
            throw std::runtime_error("value is not object");
        }
        return T(v.toObject());
    }

    template <typename T>
    std::optional<QVector<T>> toVector() {
        if (v.isNull() || v.isUndefined()) {
            return std::nullopt;
        }
        return Extract(v).toVector<T>();
    }

    template <typename T>
    std::optional<QVector<T>> toObjectsVector() {
        if (v.isNull() || v.isUndefined()) {
            return std::nullopt;
        }
        return Extract(v).toObjectsVector<T>();
    }

    inline operator std::optional<QVector<QString>>() {
        return toVector<QString>();
    }

    inline operator std::optional<QVector<int>>() {
        return toVector<int>();
    }

    inline operator std::optional<QVector<qint64>>() {
        return toVector<qint64>();
    }

    inline operator std::optional<QVector<double>>() {
        return toVector<double>();
    }

    inline operator std::optional<QVector<bool>>() {
        return toVector<bool>();
    }
};

static const auto arrayToValue = [](auto&& data) -> QJsonValue {
    QJsonArray arr;
    for (const auto& jv : data) {
        arr.push_back(jv);
    }
    return arr;
};

static const auto optArrayToValue = [](auto&& data) -> QJsonValue {
    if (!data) {
        return {};
    }
    return arrayToValue(data.value());
};

static const auto objArrayToValue = [](auto&& data) -> QJsonValue {
    QJsonArray arr;
    for (const auto& jv : data) {
        arr.push_back(jv.toJson());
    }
    return arr;
};

static const auto optObjArrayToValue = [](auto&& data) -> QJsonValue {
    QJsonArray arr;
    for (const auto& jv : data.value()) {
        arr.push_back(jv.toJson());
    }
    return arr;
};

static const auto optToValue = [](auto&& data) -> QJsonValue { return data ? data.value() : QJsonValue(); };
static const auto optObjToValue = [](auto&& data) -> QJsonValue { return data ? data.value().toJson() : QJsonValue(); };

}  // namespace qjsh
