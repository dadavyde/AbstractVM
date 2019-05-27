/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:19:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/11/06 19:19:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"
#include "Operand.hpp"

OperandFactory::OperandFactory()
{
    func_ptr_map_[Int8] = &OperandFactory::createInt8;
    func_ptr_map_[Int16] = &OperandFactory::createInt16;
    func_ptr_map_[Int32] = &OperandFactory::createInt32;
    func_ptr_map_[Float] = &OperandFactory::createFloat;
    func_ptr_map_[Double] = &OperandFactory::createDouble;
}

OperandFactory& OperandFactory::operator=(const OperandFactory &other)
{
    if (this != &other)
    {
        func_ptr_map_ = other.func_ptr_map_;
    }
    return *this;
}

OperandFactory::OperandFactory(const OperandFactory &other)
{
    *this = other;
}

OperandFactory::~OperandFactory()
{}

IOperand const* OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
    IOperand const* (OperandFactory::*reference)(std::string const & value) const;
    reference = func_ptr_map_.at(type);
    try
    {
        return ((*this.*reference)(value));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

IOperand const* OperandFactory::createInt8(std::string const &value) const
{
    int  result;
    int8_t  digit_value;

    try {
        result = std::stoi(value, nullptr, 10);
    }
    catch  (std::out_of_range &e) {
        if(value[0] == '-')
            throw UnderflowErr("");
        else
            throw OverflowErr("");
    }
    if (result < SCHAR_MIN)
        throw UnderflowErr("");
    else if (result > SCHAR_MAX)
        throw OverflowErr("");
    else
        digit_value = static_cast<int8_t>(result);
    return (new Operand<int8_t>(digit_value, value, Int8));
}

IOperand const* OperandFactory::createInt16(std::string const &value) const
{
    int  result;
    int16_t  digit_value;

    try {
        result = std::stoi(value, nullptr, 10);
    }
    catch  (std::out_of_range &e) {
        if(value[0] == '-')
            throw UnderflowErr("");
        else
            throw OverflowErr("");
    }
    if (result < SHRT_MIN)
        throw UnderflowErr("");
    else if (result > SHRT_MAX)
        throw OverflowErr("");
    else
        digit_value = static_cast<int16_t>(result);
    return (new Operand<int16_t>(digit_value, value, Int16));
}


IOperand const* OperandFactory::createInt32(std::string const &value) const
{
    int32_t  digit_value;

    try {
        digit_value = std::stoi(value, nullptr, 10);
    }
    catch  (std::out_of_range &e)
    {
        if(value[0] == '-')
            throw UnderflowErr("");
        else
            throw OverflowErr("");
    }
    return (new Operand<int32_t>(digit_value, value, Int32));
}

IOperand const* OperandFactory::createFloat(std::string const &value) const
{
    float  digit_value;

    try {
        digit_value = std::stof(value, nullptr);
    }
    catch (std::out_of_range &e)
    {
        long double test_result;

        try{
            test_result = std::stold(value, nullptr);
        }
        catch (std::out_of_range &e){
            throw std::logic_error(e);
        }
        if (test_result < -FLT_MAX)
            throw UnderflowErr("");
        else if (test_result > 0 && test_result <= FLT_MIN)
            throw UnderflowErr("Underflow of representable positive float value");
        else if (test_result < 0 && test_result >= -FLT_MIN)
            throw UnderflowErr("Overflow of representable negative float value");
        else
            throw OverflowErr("");
    }
    return (new Operand<float>(digit_value, value, Float));
}

IOperand const* OperandFactory::createDouble(std::string const &value) const
{
    float  digit_value;

    try {
        digit_value = std::stod(value, nullptr);
    }
    catch (std::out_of_range &e)
    {
        long double test_result;

        try{
            test_result = std::stold(value, nullptr);
        }
        catch (std::out_of_range &e){
            throw std::logic_error(e);
        }
        if (test_result < -DBL_MAX)
            throw UnderflowErr("");
        else if (test_result > 0 && test_result <= DBL_MIN)
            throw UnderflowErr("Underflow of representable positive double value");
        else if (test_result < 0 && test_result >= -FLT_MIN)
            throw UnderflowErr("Overflow of representable negative double value");
        else
            throw OverflowErr("");
    }
    return (new Operand<double>(digit_value, value, Double));
}
