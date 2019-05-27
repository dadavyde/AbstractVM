/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:06:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/11/03 15:06:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_H
# define OPERAND_H

#include <algorithm>
#include <typeinfo>
#include <typeindex>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <cerrno>
#include "OperandFactory.hpp"

template <typename T>
class Operand : public IOperand
{
public:
    Operand(T digit_value, std::string const &num, eOperandType type);
    ~Operand();
    Operand &operator=(const Operand &other);
    Operand(const Operand &other);

    int getPrecision(void) const;
    eOperandType getType(void) const;
    std::string const & toString( void ) const;

    IOperand const * operator + ( IOperand const & rhs ) const;
    IOperand const * operator - ( IOperand const & rhs ) const;
    IOperand const * operator * ( IOperand const & rhs ) const;
    IOperand const * operator / ( IOperand const & rhs ) const;
    IOperand const * operator % ( IOperand const & rhs ) const;
    IOperand const * operator ^ (IOperand const & rhs ) const;
    IOperand const * my_sqrt () const;
    bool operator==( IOperand const & rhs ) const;
    bool operator!=( IOperand const & rhs ) const;

private:
    T               digit_value_;
    std::string     str_value_;
    eOperandType    type_;
    int             precision_;//Int8 < Int16 < Int32 < Float < Double
    OperandFactory  factory_;
};

template <typename T>
Operand<T>::Operand(T digit_value, std::string const &num, eOperandType type) : digit_value_(digit_value), str_value_(num), type_(type), factory_()
{
    precision_ = static_cast<int>(type);
}

template <typename T>
Operand<T>::~Operand(){}

template <typename T>
Operand<T>& Operand<T>::operator=(const Operand<T> &other)
{
    if (this != &other)
    {
        digit_value_ = other.digit_value_;
        str_value_ = other.str_value_;
        type_ = other.type_;
        precision_ = other.precision_;
        factory_ = other.factory_;
    }
    return (*this);
}

template <typename T>
Operand<T>::Operand(const Operand<T> &other)
{
    *this = other;
}

template <typename T>
int Operand<T>::getPrecision( void ) const
{
    return (precision_);
}

template <typename T>
eOperandType Operand<T>::getType( void ) const
{
    return (type_);
}

template <typename T>
std::string const& Operand<T>::toString() const
{
    return (str_value_);
}

template <typename T>
IOperand const * Operand<T>::operator+( IOperand const & rhs ) const
{
    int precision = std::max(precision_, rhs.getPrecision());
    std::string  valueStr;

    if (precision >= Float)
    {
        auto value = static_cast<long double>(digit_value_ + stod(rhs.toString()));
        valueStr = std::to_string(value);
        std::ostringstream ss;
        ss << value;
        valueStr = ss.str();
    }
    else
    {
        auto  value = static_cast<long int>(digit_value_ + stoi(rhs.toString()));
        valueStr = std::to_string(value);
    }
    try {
        return (factory_.createOperand(static_cast<eOperandType>(precision), valueStr));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

template <typename T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const
{
    int precision = std::max(precision_, rhs.getPrecision());
    std::string  valueStr;

    if (precision >= Float)
    {
        auto  value = static_cast<long double>(digit_value_ - stod(rhs.toString()));
        std::ostringstream ss;
        ss << value;
        valueStr = ss.str();
    }
    else
    {
        auto  value = static_cast<long int>(digit_value_ - stoi(rhs.toString()));
        valueStr = std::to_string(value);
    }
    try {
        return (factory_.createOperand(static_cast<eOperandType>(precision), valueStr));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

template <typename T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
    int precision = std::max(precision_, rhs.getPrecision());
    std::string  valueStr;

    if (precision >= Float)
    {
        auto  value = static_cast<long double>(digit_value_ * stod(rhs.toString()));
        std::ostringstream ss;
        ss << value;
        valueStr = ss.str();
    }
    else
    {
        auto  value = static_cast<long int>(digit_value_ * stoi(rhs.toString()));
        valueStr = std::to_string(value);
    }
    try {
        return (factory_.createOperand(static_cast<eOperandType>(precision), valueStr));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

template <typename T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
    if (stod(rhs.toString()) == 0)
    {
        if (this->digit_value_ == 0)
            throw ZeroDivException("Division 0 by 0 - undefined behavior");
        else
            throw ZeroDivException("Division by 0 is forbidden");
    }

    int precision = std::max(precision_, rhs.getPrecision());
    std::string  valueStr;

    if (precision >= Float)
    {
        auto  value = static_cast<long double>(digit_value_ / stod(rhs.toString()));
        std::ostringstream ss;
        ss << value;
        valueStr = ss.str();
    }
    else
    {
        auto  value = static_cast<long int>(digit_value_ / stoi(rhs.toString()) + 0.5);
        valueStr = std::to_string(value);
    }
    try {
        return (factory_.createOperand(static_cast<eOperandType>(precision), valueStr));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

template <>
inline IOperand const * Operand<float>::operator%( IOperand const & rhs ) const
{
    rhs.getType();
    throw FloatPointErr("Use float point numbers in calculates of the modulus forbidden");
}

template <>
inline IOperand const * Operand<double>::operator%( IOperand const & rhs ) const
{
    rhs.getType();
    throw FloatPointErr("Use float point numbers in calculates of the modulus forbidden");
}

template <typename T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
    if (stoi(rhs.toString()) == 0)
        throw ZeroDivException("Modulo by 0 is forbidden");

    int precision = std::max(precision_, rhs.getPrecision());
    std::string  valueStr;

    if (precision >= Float)
        throw FloatPointErr("Use float point numbers in calculates of the modulus forbidden");
    else
    {
        auto  value = static_cast<long int>(digit_value_ % stoi(rhs.toString()));
        valueStr = std::to_string(value);
    }
    try {
        return (factory_.createOperand(static_cast<eOperandType>(precision), valueStr));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

template <typename T>
IOperand const * Operand<T>::operator ^ (IOperand const & rhs) const
{
    int precision = std::max(precision_, rhs.getPrecision());
    std::string  valueStr;

    double  value = pow(static_cast<double>(digit_value_), stod(rhs.toString()));
    if (errno == ERANGE) {
        if (value == HUGE_VAL)
            throw UnderflowErr("");
        else
            throw UnderflowErr("");
    }
    else if (errno == EDOM || isfinite(value) == false)
    {
        throw NegativeValErr("Cannot find pow with such parameters");
    }
    if (precision <= Int32)
    {
        if (value < static_cast<double>(INT32_MIN))
            throw UnderflowErr("");
        else if (value > static_cast<double>(INT32_MAX))
            throw OverflowErr("");
        valueStr = std::to_string(static_cast<int32_t>(lround(value)));
    }
    else {
        std::ostringstream ss;
        ss << value;
        valueStr = ss.str();
    }
    try {
        return (factory_.createOperand(static_cast<eOperandType>(precision), valueStr));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

template <typename T>
IOperand const * Operand<T>::my_sqrt() const
{
    std::string  valueStr;

    if (digit_value_ < 0)
        throw NegativeValErr("Cannot find sqrt from negative value");
    auto value = sqrt(digit_value_);
    if (precision_ <= Int32)
    {
        valueStr = std::to_string(static_cast<int32_t>(lround(value)));
    }
    else {
        std::ostringstream ss;
        ss << value;
        valueStr = ss.str();
    }
    try {
        return (factory_.createOperand(type_, valueStr));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

template <typename T>
bool Operand<T>::operator == (IOperand const & rhs) const
{
    return (str_value_ == rhs.toString() && type_ == rhs.getType());
}

template <typename T>
bool Operand<T>::operator != (IOperand const & rhs) const
{
    return !(*this == rhs);
}

#endif
