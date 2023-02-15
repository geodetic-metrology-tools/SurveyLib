/*
© Copyright CERN 2022. All rigths reserved. This software is released under a CERN proprietary software licence.
Any permission to use it shall be granted in writing. Request shall be adressed to CERN through mail-KT@cern.ch
*/

#ifndef _CUSTOM_TYPE_TRAITS
#define _CUSTOM_TYPE_TRAITS

#include <memory>
#include <string>

// clang-format off

/* ######### HELPERS ######### */

// Consumes type, and makes it `void` if  well-formed
template<class...>
struct make_void { using type = void; };
template<typename... T>
using void_t = typename make_void<T...>::type;

// Regardless of type treat it as a pointer
template<typename T>
T* to_ptr(T& obj) { return &obj; } // ref to point
template<typename T>
T* to_ptr(T* obj) { return obj; } // pointer to pointer

/* ######### CUSTOM TYPE TRAITS ######### */

// is pair
template<class T>
struct is_pair : std::false_type {};
template<class T, class U>
struct is_pair<std::pair<T, U>> : std::true_type {};

// is map
template<class T, class = void>
struct has_mapped_type : std::false_type {};
template<class T>
struct has_mapped_type<T, void_t<typename T::mapped_type>> : std::true_type {};

// is iterable
template<class T, class = void>
struct is_iterable_container : std::false_type {};
template<typename T>
struct is_iterable_container<T, void_t<
	decltype(std::begin(std::declval<T>())),
	decltype(std::end(std::declval<T>()))
>> : std::true_type {};

// is sparse
template<class T, class = void>
struct is_sparse : std::false_type {};
template<typename T>
struct is_sparse<T, void_t<
	decltype(std::declval<T>().toDense())
>> : std::true_type {};

// is string (and char variants)
template<class T, class = void>
struct is_string : std::false_type{};
template<typename T>
struct is_string<T, typename std::enable_if_t<
	std::is_same_v<T, std::string> || 
	std::is_same_v<char const *, typename std::decay<T>::type> || 
	std::is_same_v<char *, typename std::decay<T>::type>
>> : std::true_type {};

//// Pointers
template <typename T>
struct is_unique_ptr : std::false_type{};
template <typename T>
struct is_unique_ptr<std::unique_ptr<T>> : std::true_type{};
template <typename T>
struct is_shared_ptr : std::false_type{};
template <typename T>
struct is_shared_ptr<std::shared_ptr<T>> : std::true_type{};
template <typename T>
struct is_weak_ptr : std::false_type{};
template <typename T>
struct is_weak_ptr<std::weak_ptr<T>> : std::true_type{};

template<typename T, class = void>
struct is_any_pointer: std::false_type {};
template<typename T>
struct is_any_pointer<T, typename std::enable_if_t<
	std::is_pointer<T>::value
	|| is_weak_ptr<T>::value
	|| is_shared_ptr<T>::value
	|| is_unique_ptr<T>::value
>> : std::true_type {};

// is Serializable class
class Serializable;
template<class T, class = void>
struct is_Serializable : std::false_type {};
template<typename T>
struct is_Serializable<T, typename std::enable_if_t<
	std::is_base_of<Serializable, T>::value
>> : std::true_type {};

// clang-format on
#endif
