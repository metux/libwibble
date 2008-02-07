// -*- C++ -*- Substitution Failure Is Not An Error

#ifndef WIBBLE_SFINAE_H
#define WIBBLE_SFINAE_H

namespace wibble {

struct Unit {};

struct TTrue {
    static const bool value = true;
};

struct TFalse {
    static const bool value = true;
};

// small SFINAE utilities, we probably prefer to avoid full weight of boost here
template< typename A, typename B >
struct TSame {
    static const bool value = false;
};

template< typename A >
struct TSame< A, A > {
    static const bool value = true;
};

template< bool, bool >
struct TAndC {
    static const bool value = false;
};

template<>
struct TAndC< true, true > {
    static const bool value = true;
};

template< typename A, typename B >
struct TAnd : TAndC< A::value, B::value > {};

template< bool, bool >
struct TOrC {
    static const bool value = true;
};

template<>
struct TOrC< false, false > {
    static const bool value = false;
};

template< typename A, typename B >
struct TOr : TOrC< A::value, B::value > {};

/* template< typename T >
struct IsT {
    static const bool value = true;
    }; */

template< bool a > struct TNotC {
    static const bool value = !a;
};

template< typename T > struct TNot : TNotC< T::value > {};

template< bool a, bool b >
struct TImplyC : TNot< TAndC< a, TNotC< b >::value > > {};

template< typename A, typename B >
struct TImply : TImplyC< A::value, B::value > {};

template< bool, typename T = Unit >
struct EnableIfC {};

template< typename Type >
struct EnableIfC< true, Type > { typedef Type T; };

template< typename X, typename T = Unit >
struct EnableIf : EnableIfC< X::value, T > {};

}

#endif