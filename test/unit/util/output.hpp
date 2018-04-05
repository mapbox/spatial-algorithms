#include <mapbox/geometry/geometry.hpp>
#include <ostream>

namespace mapbox {
namespace geometry {

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const point<T>& pt) {
    out << "[" << pt.x << "," << pt.y << "]";
    return out;
}

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const multi_point<T>& mp) {
    bool first = true;
    out << "[";
    for (auto & pt : mp) {
        if (first) {
            out << pt;
            first = false;
        } else {
            out << "," << pt;
        }
    }
    out << "]";
    return out;
}

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const line_string<T>& ls) {
    bool first = true;
    out << "[";
    for (auto & pt : ls) {
        if (first) {
            out << pt;
            first = false;
        } else {
            out << "," << pt;
        }
    }
    out << "]";
    return out;
}

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const multi_line_string<T>& mls) {
    bool first = true;
    out << "[";
    for (auto & ls : mls) {
        if (first) {
            out << ls;
            first = false;
        } else {
            out << "," << ls;
        }
    }
    out << "]";
    return out;
}

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const linear_ring<T>& lr) {
    bool first = true;
    out << "[";
    for (auto & pt : lr) {
        if (first) {
            out << pt;
            first = false;
        } else {
            out << "," << pt;
        }
    }
    out << "]";
    return out;
}

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const polygon<T>& poly) {
    bool first = true;
    out << "[";
    for (auto & lr : poly) {
        if (first) {
            out << lr;
            first = false;
        } else {
            out << "," << lr;
        }
    }
    out << "]";
    return out;
}

template <class charT, class traits, typename T>
inline std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& out,
                                                     const multi_polygon<T>& mp) {
    bool first = true;
    out << "[";
    for (auto & poly : mp) {
        if (first) {
            out << poly;
            first = false;
        } else {
            out << "," << poly;
        }
    }
    out << "]";
    return out;
}

}
}
