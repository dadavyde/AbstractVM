/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:28:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/13 17:28:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_CLION_ABSTRACTVM_HPP
#define ABSTRACT_VM_CLION_ABSTRACTVM_HPP

#include "Lexer.hpp"
#include "Parser.hpp"
#include <vector>
#include <fstream>

class AbstractVm
{
public:
	typedef std::map<std::string, eOperandType> ValueType;

    AbstractVm();
    ~AbstractVm();
    AbstractVm &operator=(const AbstractVm &other);
    AbstractVm(const AbstractVm &other);

    void  read_input();
    void  try_read_from_file(std::string& filename);
    void  read_file(std::ifstream & file);
	void  run_avm();
	void  run_value_instr();
	void  run_calculate_instr();
	void  run_other_instr();

private:
	OperandFactory                factory;
	ValueType                     valueType_;
	Instruction                   instruction_;
    Lexer                         lexer_;
    Parser                        parser_;
    std::vector<IOperand const*>  operands_;
    std::string                   line_;
    unsigned int                  line_num_;
    unsigned int                  logic_err_line_num_;
    unsigned int                  parser_error_num_;
    std::string                   logical_err_;
};


#endif //ABSTRACT_VM_CLION_ABSTRACTVM_HPP
