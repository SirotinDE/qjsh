#include <optional>

class QJsonObject;

namespace qjsh {
template <typename T>
std::optional<T> parse(const QJsonObject& j) {
    try {
        return T(j);
    } catch (...) {
    }
    return std::nullopt;
}
}  // namespace qjsh
