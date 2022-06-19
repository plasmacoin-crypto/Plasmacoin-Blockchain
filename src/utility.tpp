//
// FILENAME: utility.tpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Template definitions for the utility namespace
// CREATED: 2022-06-15 @ 6:37 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef UTILITY_TPP
#define UTILITY_TPP

#include <algorithm>

// Check if a future is ready to have its value read
template<typename T> bool utility::isReady(const std::future<T>& future) {
	return future.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

// Find the mean (average) of an arbitrary number of values
template<typename T, typename... Args>
typename std::enable_if<std::is_arithmetic<T>::value, float>::type mean(T first, Args... nums) {
    constexpr size_t size = sizeof...(nums) + 1;

    std::array<T, size> numArray = {first, nums...}; // Unpack the arguments into a std::array
    T sum = 0;

    for (T num: numArray) {
        sum += num;
    }

    return sum / static_cast<float>(size);
}

// Find the median of a list of values
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, float>::type median(std::vector<T>& data) {
    std::sort(data.begin(), data.end());
    const size_t size = data.size();

    if (size % 2 == 0) {
        T index1 = size / 2 - 1;
        T index2 = size / 2;

        return mean(data[index1], data[index2]);
    }
    else {
        T index = (size - 1) / 2;
        return data[index];
    }
}

#endif // UTILITY_TPP