#include <vector>
#include <iostream>

namespace lazy {
    class Vect;
    template <class L, class Op, class R> class Exp;

    struct Plus {
        static double apply(const double l, const double r) {
            return l + r;
        }
    };

    template <class T> class Wrapper;

    template <class T> class Wrapper<T&> {
        T& ref_;
    public:
        Wrapper(T& ref) :ref_(ref) {}
        T& get() { return ref_; }
        const T& get() const { return ref_; }
    };

    template <class T> class Wrapper<T&&> {
        T rval_;
    public:
        Wrapper(T&& val) :rval_(std::move(val)) {}
        T& get() { return rval_; }
        const T& get() const { return rval_; }
    };

    class Vect {
        using Iterator = typename std::vector<double>::iterator;
        std::vector<double> vec_;
    public:
        Vect() {}
        Vect(std::size_t n) : vec_(n) {}
        Vect(std::size_t n, double init) : vec_(n, init) {}
        Vect(std::initializer_list<double> list) : vec_(list) {}
        Vect(Vect const& rhs) : vec_(rhs.vec_) {}
        Vect(Vect&& rhs) : vec_(std::move(rhs.vec_)) {}

        double& operator[](std::size_t i) { return vec_[i]; }
        double operator[](std::size_t i) const { return vec_[i]; }

        template <class RE>
        Exp<Vect&, Plus, RE&&> operator+(RE&& rhs) {
            return Exp<Vect&, Plus, decltype(std::forward<RE>(rhs))>(*this, std::forward<RE>(rhs));
        }
        template <class R>
        Vect& operator=(const R& rhs) {
            std::size_t n = vec_.size();
            for (int i = 0; i < n; ++i) {
                (*this)[i] = rhs[i];
            }
            return *this;
        }
        Iterator begin() { return vec_.begin(); }
        Iterator end() { return vec_.end(); }
        const std::size_t size() const { return vec_.size(); }
    };

    template <class L, class Op, class R>
    class Exp {
        Wrapper<L> l_;
        Wrapper<R> r_;
    public:
        Exp(L l, R r) : l_(std::forward<L>(l)), r_(std::forward<R>(r)) {};

        double operator[](std::size_t i) const { return Op::apply(l_.get()[i], r_.get()[i]); }
        const std::size_t size() const { return r_.get().size(); }
        operator Vect() {
            std::size_t n = this->size();
            Vect result(n);
            for (std::size_t i = 0; i < n; ++i) {
                result[i] = (*this)[i];
            }
            return result;
        }
    };

    template <class L, class R>
    Exp<L&&, Plus, R&&> operator+(L&& l, R&& r) {
        return Exp<L&&, Plus, R&&>(std::forward<L>(l), std::forward<R>(r));
    }
}