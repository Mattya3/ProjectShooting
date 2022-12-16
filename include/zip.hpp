#include <bits/stdc++.h>
template<typename T, typename U>
constexpr auto
zip_impl(T v1, U v2){
    auto vi1 = std::begin(v1);
    auto vi2 = std::begin(v2);

    using value_t = decltype(std::make_tuple(*vi1, *vi2));
    std::vector<value_t> result{};

    while(vi1 != std::end(v1) && vi2 != std::end(v2)){
        result.emplace_back(*vi1, *vi2);
        vi1++;
        vi2++;
    }
    return result;
}

template<typename T, typename U>
constexpr auto
zip(T v1, U v2){
    return zip_impl(v1, v2);
}