/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:22:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/02 20:22:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_CLION_PARSER_HPP
#define ABSTRACT_VM_CLION_PARSER_HPP

#include "structs.hpp"
#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "Instruction.hpp"
#include <cstdlib>
#include <stack>
#include <limits>

class Parser
{
public:
    using CALC_FUN = IOperand const* (Instruction::*)(IOperand const* &op1, IOperand const* &op2);
    using CalcMap = std::map<std::string, CALC_FUN>;
    using INSTR_FUN = void (Instruction::*)(std::vector<IOperand const *> &operands);
    using InstrMap = std::map<std::string, INSTR_FUN>;

    Parser();
    ~Parser();
    Parser &operator=(const Parser &other);
    Parser(const Parser &other);

    void  check_syntax_errors();
    void  check_logic_errors(std::vector<IOperand const*> &operands);
    void  check_exit();
    void  init_calculate_map();
    void  init_instruction_map();
    CalcMap  &getCalcMap();
    InstrMap  &getInstrMap();

private:
    CalcMap               calcMap_;
    InstrMap              instrMap_;
};


#endif //ABSTRACT_VM_CLION_PARSER_HPP
