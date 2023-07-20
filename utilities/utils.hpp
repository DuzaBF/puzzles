#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    if (v.empty()) {
        out << "[]";
        return out;
    }

    out << "[";
    for (const auto& val : v) {
        out << val << ", ";
    }
    out << "\b\b]";
    return out;
}

namespace utils {

template <typename T>
struct CheckAnswer {
   public:
    const T& answer;
    const T& expected;
    CheckAnswer(const T& answer, const T& expected)
        : answer(answer), expected(expected){};

   private:
    CheckAnswer(){};
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const CheckAnswer<T>& v) {
    out << "Answer: " << v.answer << " Expected: " << v.expected <<
        ((v.answer == v.expected) ? " \033[32mPASS\033[m" : " \033[31mFAIL\033[0m");
    return out;
}

}  // namespace utils