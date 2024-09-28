#ifndef _EVSPACE_AXIS_H_
#define _EVSPACE_AXIS_H_

#include <evspace_common.hpp>

namespace evspace {

    enum class AxisDirection {
        X,
        Y,
        Z
    };

    template<AxisDirection _direction>
    struct Axis {
        static constexpr AxisDirection direction = _direction;
    };

    typedef Axis<AxisDirection::X> XAxis;
    typedef Axis<AxisDirection::Y> YAxis;
    typedef Axis<AxisDirection::Z> ZAxis;

}

#endif // _EVSPACE_AXIS_H_
