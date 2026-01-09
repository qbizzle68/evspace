#ifndef _EVSPACE_COMMA_OPERATOR_H_
#define _EVSPACE_COMMA_OPERATOR_H_

#include <cstddef>
#include <stdexcept>
#include <iostream>

namespace evspace {

    template<typename T, std::size_t N>
    class CommaInitializer {
    private:
        T& ref;
        std::size_t index;
    public:
        CommaInitializer(T& ref, double first) : ref(ref), index(0) {
            this->ref[this->index++] = first;
        }

        CommaInitializer& operator,(double value) {
            if (this->index >= N) {
                throw std::invalid_argument("Too many values provided "
                                            "in comma initialization");
            }
            this->ref[this->index++] = value;
            return *this;
        }
    };

}   // namespace evspace

#endif // _EVSPACE_COMMA_OPERATOR_H_