/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:19:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/11/06 19:19:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include <climits>
#include "IOperand.hpp"
#include "exceptions.hpp"
#include <map>
#include <cfloat>

class OperandFactory
{
public:
    typedef IOperand const * (OperandFactory::*GET_FUN_PTR)(std::string const & value) const;
    typedef std::map<eOperandType, GET_FUN_PTR> TFunList;
    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

    OperandFactory();
    ~OperandFactory();
    OperandFactory &operator=(const OperandFactory &other);
    OperandFactory(const OperandFactory &other);

    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

private:
    TFunList     func_ptr_map_;
};

#endif
