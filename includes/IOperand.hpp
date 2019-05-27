/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 14:42:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/11/03 14:42:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
#define IOPERAND_HPP

#include <iostream>
#include "structs.hpp"

class IOperand
{
public:
    virtual int getPrecision( void ) const = 0;
    virtual eOperandType getType( void ) const = 0;
    virtual IOperand const * operator + (IOperand const & rhs ) const = 0;
    virtual IOperand const * operator - (IOperand const & rhs ) const = 0;
    virtual IOperand const * operator * (IOperand const & rhs ) const = 0;
    virtual IOperand const * operator / (IOperand const & rhs ) const = 0;
    virtual IOperand const * operator % (IOperand const & rhs ) const = 0;
    virtual IOperand const * operator ^ (IOperand const & rhs ) const = 0;
    virtual IOperand const * my_sqrt () const = 0;
    virtual bool operator == (IOperand const & rhs) const = 0;
    virtual bool operator != (IOperand const & rhs) const = 0;
    virtual std::string const & toString(void) const = 0;
    virtual ~IOperand( void ) {};
};

#endif
