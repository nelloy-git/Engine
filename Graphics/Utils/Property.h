#pragma once

template<typename T, typename Owner>
class Property final {
public:
    using SetterType = void (Owner::*)(const T&);
    using GetterType = const T& (Owner::*)();

    Property(Owner *owner,
             GetterType getter,
             SetterType setter) :
        _owner(owner),
        _getter(getter), 
        _setter(setter){
    };

    ~Property(){};

    inline Property<T, Owner> &operator=(const T& other){
        (_owner->*_setter)(other);
        return *this;
    };

    inline operator const T&() {
        return (_owner->*_getter)();
    };

    inline operator const T&() const {
        return (_owner->*_getter)();
    };

    template<typename V>
    inline auto &operator[](const V &index){
        return (_owner->*_getter)()[index];
    };

    template<typename V>
    inline const auto &operator[](const V &index) const {
        return (_owner->*_getter)()[index];
    };

    template<typename V>
    inline auto operator+(const V &other){
        return (_owner->*_getter)() + other;
    };

    template<typename V>
    inline auto operator+(const V &other) const {
        return (_owner->*_getter)() + other;
    };

    template<typename V>
    inline friend auto operator+ (const V& other, const Property<T, Owner> &prop){
        return other + (prop._owner->*(prop._getter))();
    };

    template<typename V>
    inline Property<T, Owner> &operator+=(const V& other){
        (_owner->*_setter)((_owner->*_getter)() + other);
        return *this;
    };

    template<typename V>
    inline auto operator-(const V &other){
        return (_owner->*_getter)() - other;
    };

    template<typename V>
    inline auto operator-(const V &other) const {
        return (_owner->*_getter)() - other;
    };

    template<typename V>
    inline friend auto operator- (const V& other, const Property<T, Owner> &prop){
        return other - (prop._owner->*(prop._getter))();
    };

    template<typename V>
    inline Property<T, Owner> &operator-=(const V& other){
        (_owner->*_setter)((_owner->*_getter)() - other);
        return *this;
    };

    template<typename V>
    inline auto operator*(const V &other){
        return (_owner->*_getter)() * other;
    };

    template<typename V>
    inline auto operator*(const V &other) const {
        return (_owner->*_getter)() * other;
    };

    template<typename V>
    inline friend auto operator* (const V& other, const Property<T, Owner> &prop){
        return other * (prop._owner->*(prop._getter))();
    };

    template<typename V>
    inline Property<T, Owner> &operator*=(const V& other){
        (_owner->*_setter)((_owner->*_getter)() * other);
        return *this;
    };

    template<typename V>
    inline auto operator/(const V &other){
        return (_owner->*_getter)() / other;
    };

    template<typename V>
    inline auto operator/(const V &other) const {
        return (_owner->*_getter)() / other;
    };

    template<typename V>
    inline friend auto operator/ (const V& other, const Property<T, Owner> &prop){
        return other / (prop._owner->*(prop._getter))();
    };

    template<typename V>
    inline Property<T, Owner> &operator/=(const V& other){
        (_owner->*_setter)((_owner->*_getter)() / other);
        return *this;
    };

private:
    Owner *_owner;
    const SetterType _setter;
    const GetterType _getter;
};