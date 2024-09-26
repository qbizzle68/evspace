#include <angles.hpp>
#include <cstddef>
#include <stdexcept>

evspace::EulerAngles::EulerAngles() : m_values{ 0.0, 0.0, 0.0 } { }

evspace::EulerAngles::EulerAngles(double alpha, double beta, double gamma)
    : m_values{ alpha, beta, gamma } { }

evspace::EulerAngles::EulerAngles(const EulerAngles& cpy)
    : m_values{ cpy.m_values[0], cpy.m_values[1], cpy.m_values[2] } { }

double& evspace::EulerAngles::operator[](std::size_t index) {
    if (index > 2) {
        throw std::out_of_range("Angle index out of range.");
    }

    return this->m_values[index];
}

const double& evspace::EulerAngles::operator[](std::size_t index) const {
    if (index > 2) {
        throw std::out_of_range("Angle index out of range.");
    }

    return this->m_values[index];
}
