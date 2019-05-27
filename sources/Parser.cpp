/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:22:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/02 20:22:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser()
{}

Parser::~Parser()
{}

Parser& Parser::operator=(const Parser &other)
{
    if (this != &other)
    {
        this->calcMap_ = other.calcMap_;
        this->instrMap_ = other.instrMap_;
    }
    return (*this);
}

Parser::Parser(const Parser &other)
{
    *this = other;
}

void Parser::check_syntax_errors()
{
    if (tokens.empty())
        return;
    if ((tokens[0].type == Instr_no_val || tokens[0].type == Instr_calc) && tokens.size() > 1)
        throw InstrErr();//синтаксическая ошибка
    if (tokens[0].type == Unknown_instr)
        throw UnknownInstrErr(tokens[0].name);//лексическая ошибка
    for(unsigned long i = 1; i < 4; i++)
        if (tokens.size() > i && tokens[i].type == Unknown_instr)
            throw UnknownInstrErr(tokens[i].name);//лексическая ошибка
    if (tokens[0].type == Instr_val)
    {
        if (tokens.size() == 1 || tokens[1].name == "")
            throw NoValueErr();
        else if (tokens.size() > 1 && tokens[1].type != Type_N && tokens[1].type != Type_Z)
            throw BadTypeValueErr(tokens[1].name);//синтаксическая ошибка
    }
    if (tokens.size() == 3  && ((tokens[1].type == Type_N && tokens[2].type != Value_N) || (tokens[1].type == Type_Z && tokens[2].type != Value_Z)))
        throw TypeValueErr();//синтаксическая ошибка
}

void Parser::check_logic_errors(std::vector<IOperand const*> &operands) {
    if ((tokens[0].name == "pop" || tokens[0].name == "dump" || tokens[0].name == "assert" ||
         tokens[0].name == "print" || tokens[0].name == "sqrt") && operands.empty())
        throw EmptyStackErr(tokens[0].name);//логическая ошибка
    else if (tokens[0].type == Instr_calc && operands.size() < 2)
        throw TooSmallStackErr(tokens[0].name); //логическая ошибка
    if (tokens[0].name == "print" && operands.back()->getType() != Int8)
        throw NonPrintableInt("");//логическая ошибка
}

void Parser::check_exit() {
    if (is_exit_ == false)
        throw NoExitErr("");
}

void Parser::init_calculate_map()
{
    calcMap_["add"] = &Instruction::add;
    calcMap_["sub"] = &Instruction::sub;
    calcMap_["mul"] = &Instruction::mul;
    calcMap_["div"] = &Instruction::div;
    calcMap_["mod"] = &Instruction::mod;
    calcMap_["pow"] = &Instruction::my_pow;
}

void Parser::init_instruction_map()//my_sqrt|pop|dump|print|exit
{
    instrMap_["sqrt"] = &Instruction::my_sqrt;
    instrMap_["pop"] = &Instruction::pop;
    instrMap_["dump"] = &Instruction::dump;
    instrMap_["print"] = &Instruction::print;
    instrMap_["exit"] = &Instruction::exit;
}

Parser::CalcMap &  Parser::getCalcMap()
{
    return (calcMap_);
}

Parser::InstrMap &  Parser::getInstrMap()
{
    return (instrMap_);
}
