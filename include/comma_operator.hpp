#ifndef _EVSPACE_COMMA_OPERATOR_H_
#define _EVSPACE_COMMA_OPERATOR_H_

#include <cstddef>
#include <stdexcept>
#include <iostream>

namespace evspace {

    template<typename T>
    class CommaInitializer {
    private:
        std::size_t index;

    protected:
        T& ref;

        // Gets a reference to the component from the current
        // value of the internal index value. If this value is
        // out of valid ranges this should throw std::out_of_range.
        virtual double& get_component(const std::size_t index) = 0;

        void initialize(double first) {
            this->get_component(0) = first;
        }
        
    public:
        // Constructs the CommaInitializer. In order to correctly handle
        // the first argument of a comma separated initialization any
        // derived class must handle setting the first value of the
        // object being initialized. For example:
        // this->get_component(0) = first.
        CommaInitializer(T& ref, [[maybe_unused]] double first) : index(1), ref(ref) {
            // this->index is initialized to 1 as the derived class's
            // constructor handles setting the first value.
        }

        CommaInitializer& operator,(double value) {
            this->get_component(this->index++) = value;
            return *this;
        }
    };

}   // namespace evspace

#endif // _EVSPACE_COMMA_OPERATOR_H_