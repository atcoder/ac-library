#include "atcoder/internal_type_traits"

#include <type_traits>

#include <gtest/gtest.h>

using namespace atcoder;
using namespace std;
using ll = long long;
using ull = unsigned long long;

struct A {};

static_assert(internal::is_integral<bool>::value, "");
static_assert(internal::is_integral<int>::value, "");
static_assert(!internal::is_integral<A>::value, "");

static_assert(internal::is_signed_int<signed char>::value, "");
static_assert(internal::is_signed_int<short>::value, "");
static_assert(internal::is_signed_int<int>::value, "");
static_assert(internal::is_signed_int<long>::value, "");
static_assert(internal::is_signed_int<long long>::value, "");

static_assert(!internal::is_signed_int<bool>::value, "");
static_assert(!internal::is_signed_int<unsigned char>::value, "");
static_assert(!internal::is_signed_int<unsigned short>::value, "");
static_assert(!internal::is_signed_int<unsigned int>::value, "");
static_assert(!internal::is_signed_int<unsigned long>::value, "");
static_assert(!internal::is_signed_int<unsigned long long>::value, "");

static_assert(!internal::is_unsigned_int<signed char>::value, "");
static_assert(!internal::is_unsigned_int<short>::value, "");
static_assert(!internal::is_unsigned_int<int>::value, "");
static_assert(!internal::is_unsigned_int<long>::value, "");
static_assert(!internal::is_unsigned_int<long long>::value, "");

static_assert(internal::is_unsigned_int<bool>::value, "");
static_assert(internal::is_unsigned_int<unsigned char>::value, "");
static_assert(internal::is_unsigned_int<unsigned short>::value, "");
static_assert(internal::is_unsigned_int<unsigned int>::value, "");
static_assert(internal::is_unsigned_int<unsigned long>::value, "");
static_assert(internal::is_unsigned_int<unsigned long long>::value, "");

static_assert(!internal::is_signed_int<A>::value, "");
static_assert(!internal::is_unsigned_int<A>::value, "");

static_assert(is_same<unsigned char, internal::to_unsigned_t<char>>::value, "");
static_assert(
    is_same<unsigned char, internal::to_unsigned_t<signed char>>::value,
    "");
static_assert(
    is_same<unsigned char, internal::to_unsigned_t<unsigned char>>::value,
    "");

static_assert(is_same<unsigned short, internal::to_unsigned_t<short>>::value,
              "");
static_assert(
    is_same<unsigned short, internal::to_unsigned_t<unsigned short>>::value,
    "");

static_assert(is_same<unsigned int, internal::to_unsigned_t<int>>::value, "");
static_assert(
    is_same<unsigned int, internal::to_unsigned_t<unsigned int>>::value,
    "");

static_assert(is_same<unsigned long, internal::to_unsigned_t<long>>::value, "");
static_assert(
    is_same<unsigned long, internal::to_unsigned_t<unsigned long>>::value,
    "");

static_assert(
    is_same<unsigned long long, internal::to_unsigned_t<long long>>::value,
    "");
static_assert(is_same<unsigned long long,
                      internal::to_unsigned_t<unsigned long long>>::value,
              "");

static_assert(is_same<A, internal::to_unsigned_t<A>>::value, "");

#ifndef _MSC_VER

static_assert(internal::is_integral<__int128_t>::value, "");
static_assert(internal::is_integral<__uint128_t>::value, "");
static_assert(internal::is_integral<__int128>::value, "");
static_assert(internal::is_integral<unsigned __int128>::value, "");

static_assert(internal::is_signed_int<__int128_t>::value, "");
static_assert(!internal::is_signed_int<__uint128_t>::value, "");
static_assert(internal::is_signed_int<__int128>::value, "");
static_assert(!internal::is_signed_int<unsigned __int128>::value, "");

static_assert(!internal::is_unsigned_int<__int128_t>::value, "");
static_assert(internal::is_unsigned_int<__uint128_t>::value, "");
static_assert(!internal::is_unsigned_int<__int128>::value, "");
static_assert(internal::is_unsigned_int<unsigned __int128>::value, "");

static_assert(
    std::is_same<__uint128_t,
                 internal::make_unsigned_int128<__int128_t>::type>::value,
    "");
static_assert(
    std::is_same<unsigned __int128,
                 internal::make_unsigned_int128<__int128>::type>::value,
    "");

#endif
