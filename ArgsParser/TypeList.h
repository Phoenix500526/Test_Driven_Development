#ifndef TYPELIST_H
#define TYPELIST_H

template <typename...> struct TypeList;

template <>
struct TypeList<> {};

template <typename Head, typename... Tails>
struct TypeList<Head, Tails...>{
    using head = Head;
    using tails = TypeList<Tails...>;
};

template <typename TList> struct Length;

template <typename... Types>
struct Length<TypeList<Types...>>{
    static constexpr std::size_t value = sizeof...(Types);
};

template <typename TList>
inline constexpr std::size_t Length_v = Length<TList>::value;

template <typename TList, std::size_t index> struct TypeAt;

template <typename Head, typename... Tails>
struct TypeAt<TypeList<Head, Tails...>, 0>{
    using type = Head;
};

template <typename Head, typename... Tails, std::size_t index>
struct TypeAt<TypeList<Head, Tails...>, index>{
    static_assert(index < sizeof...(Tails) + 1, "index out of range");
    using type = typename TypeAt<TypeList<Tails...>, index - 1>::type;
};

template <typename TList, std::size_t index>
using TypeAt_t = typename TypeAt<TList, index>::type;



#endif