/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:25:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/13 17:25:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_CLION_INSTRUCTION_HPP
#define ABSTRACT_VM_CLION_INSTRUCTION_HPP

#include "IOperand.hpp"
#include "exceptions.hpp"
#include <map>
#include <stack>
#include <climits>
#include <cfloat>
#include "structs.hpp"

class Instruction
{
public:
	Instruction();

	IOperand const*  add(IOperand const* &op1, IOperand const* &op2);
	IOperand const*  sub(IOperand const* &op1, IOperand const* &op2);
	IOperand const*  mul(IOperand const* &op1, IOperand const* &op2);
	IOperand const*  div(IOperand const* &op1, IOperand const* &op2);
	IOperand const*  mod(IOperand const* &op1, IOperand const* &op2);
	IOperand const*  my_pow(IOperand const *&op1, IOperand const *&op2);

	void  my_sqrt(std::vector<IOperand const *> &operands);
	void  pop(std::vector<IOperand const*> &operands);
    void  dump(std::vector<IOperand const*> &operands);
	void  print(std::vector<IOperand const*> &operands);
	void  exit(std::vector<IOperand const*> &operands);
};

#endif
