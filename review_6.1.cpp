#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Polynomial {
private:
    std::vector<T> coeffs;

    void cutZeros() {
        auto it = coeffs.rbegin();
        while (it != coeffs.rend() && *it == T(0)) {
            coeffs.pop_back();
            ++it;
        }
    }

public:
    Polynomial<T>(const std::vector<T> &c) : coeffs(c) {
        cutZeros();
    }

    template<typename It>
    Polynomial<T>(It begin, It end) : coeffs(begin, end) {
        cutZeros();
    }

    Polynomial<T>(const T &num = T()) {
        coeffs.push_back(num);
        cutZeros();
    }

    T operator[](size_t i) const {
        if (i >= coeffs.size()) {
            return T(0);
        } else {
            return coeffs[i];
        }
    }

    long long int Degree() const {
        if (coeffs.empty() || (coeffs.size() == 1 && coeffs[0] == T(0))) {
            return -1;
        } else {
            return static_cast<int>(coeffs.size() - 1);
        }
    }

    bool operator!=(const Polynomial<T> &other) const {
        if (coeffs.size() != other.coeffs.size()) {
            return true;
        }
        for (size_t i = 0; i != coeffs.size(); ++i) {
            if (coeffs[i] != other[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator==(const Polynomial<T> &other) const {
        return !(*this != other);
    }

    bool operator==(T num) const {
        return *this == Polynomial<T>(num);
    }

    bool operator!=(T num) const {
        return *this != Polynomial<T>(num);
    }

    Polynomial<T> &operator+=(const Polynomial<T> &other) {
        coeffs.resize(std::max(other.coeffs.size(), coeffs.size()), T(0));
        for (size_t i = 0; i != std::min(coeffs.size(), other.coeffs.size()); ++i) {
            coeffs[i] += other.coeffs[i];
        }
        cutZeros();
        return *this;
    }

    Polynomial<T> &operator-=(const Polynomial<T> &other) {
        coeffs.resize(std::max(other.coeffs.size(), coeffs.size()), T(0));
        for (size_t i = 0; i != std::min(coeffs.size(), other.coeffs.size()); ++i) {
            coeffs[i] -= other.coeffs[i];
        }
        cutZeros();
        return *this;
    }

    Polynomial<T> &operator*=(const Polynomial<T> &other) {
        *this = *this * other;
        return *this;
    }

    Polynomial<T> &operator*=(T num) {
        for (T &c : coeffs) {
            c *= num;
        }
        cutZeros();
        return *this;
    }

    Polynomial<T> operator*(const Polynomial<T> &other) const {
        std::vector<T> tmp(coeffs.size() + other.coeffs.size(), T(0));
        for (size_t i = 0; i != coeffs.size(); ++i) {
            for (size_t j = 0; j != other.coeffs.size(); ++j) {
                tmp[i + j] += coeffs[i] * other.coeffs[j];
            }
        }
        return Polynomial(tmp);
    }

    Polynomial<T> operator+(const Polynomial<T> &other) const {
        Polynomial<T> temp(coeffs.begin(), coeffs.end());
        temp += other;
        return temp;
    }

    Polynomial<T> operator-(const Polynomial<T> &other) const {
        Polynomial<T> temp(coeffs.begin(), coeffs.end());
        temp -= other;
        return temp;
    }

    Polynomial<T> operator*(T num) const {
        Polynomial temp(coeffs.begin(), coeffs.end());
        temp *= num;
        return temp;
    }

    Polynomial<T> &operator+=(T num) {
        *this += Polynomial<T>(num);
        cutZeros();
        return *this;
    }

    Polynomial<T> &operator-=(T num) {
        if (coeffs.empty()) {
            coeffs.push_back(-num);
            return *this;
        }
        this->coeffs[0] -= num;
        cutZeros();
        return *this;
    }

    T operator()(T num) const {
        T numPow = T(1);
        T summ = T(0);
        for (T coef : coeffs) {
            summ += numPow * coef;
            numPow *= num;
        }
        return summ;
    }

    auto begin() const {
        return coeffs.begin();
    }

    auto end() const {
        return coeffs.end();
    }

    Polynomial<T> operator & (const Polynomial<T>& other) const {
        if (this->coeffs.empty()) {
            return *this;
        }
        Polynomial<T> temp(other.begin(), other.end());
        Polynomial<T> res((*this)[0]);
        auto it = ++begin();
        while (it != end()) {
            res += temp * (*(it++));
            temp *= other;
        }
        return res;
    }

    friend std::ostream& operator << (std::ostream& out, const Polynomial<T> &g) {
        bool first = true;
        auto degree = g.Degree();
        if (g.coeffs.empty()) {
            out << 0;
            return out;
        }
        auto it = g.coeffs.rbegin();
        while (it != g.coeffs.rend()) {
            if (*it != T(0)) {
                if (*it > T(0) && !first) {
                    out << '+';
                }
                if (degree == 0) {
                    out << *it;
                } else if (*it == T(-1)) {
                    out << "-x";
                } else if (*it == T(1)) {
                    out << 'x';
                } else {
                    out << *it << "*x";
                }
                if (degree > 1) {
                    out << '^' << degree;
                }
            }
            --degree;
            ++it;
            first = false;
        }
        return out;
    }
};

template<typename T>
Polynomial<T> operator+(T num, const Polynomial<T> &other) {
    return other + num;
}

template<typename T>
Polynomial<T> operator*(T num, const Polynomial<T> &other) {
    return other * num;
}

template<typename T>
Polynomial<T> operator-(T num, const Polynomial<T> &other) {
    return Polynomial<T>(num) - other;
}

template<typename T>
bool operator==(T num, const Polynomial<T> &other) {
    return other == num;
}

template<typename T>
bool operator!=(T num, const Polynomial<T> &other) {
    return other != num;
}

