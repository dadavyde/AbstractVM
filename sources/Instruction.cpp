/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 18:24:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/05/16 18:24:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Instruction.hpp"

Instruction::Instruction()
{}

IOperand const* Instruction::add(IOperand const* &op1, IOperand const* &op2)
{
    return (*op2 + *op1);
}

IOperand const* Instruction::sub(IOperand const* &op1, IOperand const* &op2)
{
    return (*op2 - *op1);
}

IOperand const* Instruction::mul(IOperand const* &op1, IOperand const* &op2)
{
    return (*op2 * *op1);
}

IOperand const* Instruction::div(IOperand const* &op1, IOperand const* &op2)
{
    return (*op2 / *op1);
}

IOperand const* Instruction::mod(IOperand const* &op1, IOperand const* &op2)
{
    return (*op2 % *op1);
}

IOperand const* Instruction::my_pow(IOperand const *&op1, IOperand const *&op2)
{
    return (*op2 ^ *op1);
}

void Instruction::my_sqrt(std::vector<IOperand const *> &operands)
{
    IOperand const *op = operands.back();

    operands.pop_back();
    try{
        operands.push_back(op->my_sqrt());
    }
    catch (std::logic_error &e) {
        delete op;
        throw std::logic_error(e);
    }
    delete op;
}

void Instruction::pop(std::vector<IOperand const *> &operands)
{
    delete operands.back();
    operands.pop_back();
}

void Instruction::dump(std::vector<IOperand const*> &operands)
{
    for (auto & operand : operands)
        std::cout << operand->toString() << std::endl;
}

void Instruction::print(std::vector<IOperand const *> &operands)
{
    if (std::isprint(static_cast<char>(stoi(operands.back()->toString()))))
        std::cout << static_cast<char>(stoi(operands.back()->toString())) << std::endl;
    else
        std::cout << START_YELLOW << "Char is not printable" << END_YELLOW << std::endl;
}

void Instruction::exit(std::vector<IOperand const *> &)
{
    is_exit_ = true;
}
