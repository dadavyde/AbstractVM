/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:28:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/13 17:28:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"

bool  is_exit_;

AbstractVm::AbstractVm() : factory(), instruction_(), lexer_(), parser_(),
                           operands_(), line_(), line_num_(0), logic_err_line_num_(0),
                           parser_error_num_(0), logical_err_()
{
    is_exit_ = false;
    parser_.init_calculate_map();
    parser_.init_instruction_map();
    valueType_.insert(std::pair <std::string const &, eOperandType>("int8", Int8));
    valueType_.insert(std::pair <std::string const &, eOperandType>("int16", Int16));
    valueType_.insert(std::pair <std::string const &, eOperandType>("int32", Int32));
    valueType_.insert(std::pair <std::string const &, eOperandType>("float", Float));
    valueType_.insert(std::pair <std::string const &, eOperandType>("double", Double));
}

AbstractVm::~AbstractVm()
{
    while(!operands_.empty())
    {
        delete (operands_.back());
        operands_.pop_back();
    }
}

AbstractVm& AbstractVm::operator=(const AbstractVm &other)
{
    while(!operands_.empty())
    {
        delete (operands_.back());
        operands_.pop_back();
    }
    if (this != &other)
    {
        this->factory = other.factory;
        this->valueType_ = other.valueType_;
        this->instruction_ = other.instruction_;
        this->lexer_ = other.lexer_;
        this->parser_ = other.parser_;
        this->operands_ = other.operands_;
        this->line_ = other.line_;
        this->line_num_ = other.line_num_;
        this->logic_err_line_num_ = other.logic_err_line_num_;
        this->parser_error_num_ = other.parser_error_num_;
        this->logical_err_ = other.logical_err_;
    }
    return *this;
}

AbstractVm::AbstractVm(const AbstractVm &other)
{
    if (this != &other)
    {
        this->factory = other.factory;
        this->valueType_ = other.valueType_;
        this->instruction_ = other.instruction_;
        this->lexer_ = other.lexer_;
        this->parser_ = other.parser_;
        this->operands_ = other.operands_;
        this->line_ = other.line_;
        this->line_num_ = other.line_num_;
        this->logic_err_line_num_ = other.logic_err_line_num_;
        this->parser_error_num_ = other.parser_error_num_;
        this->logical_err_ = other.logical_err_;
    }
}

void AbstractVm::read_input()
{
    std::string  fileName = "new_file.txt";
    std::ofstream  outfile(fileName);

    while(getline(std::cin, line_))
    {
        outfile << line_ << '\n';
        if (lexer_.find_eof(line_))
            break;
    }
    outfile.close();
    try_read_from_file(fileName);
}

void  AbstractVm::try_read_from_file(std::string& filename)
{
    std::ifstream  file;

    file.open(filename.c_str());
    if (file.is_open())
    {
        read_file(file);
        file.close();
        if (logical_err_.empty() && parser_error_num_ == 0)
        {
            try {
                parser_.check_exit();
            }
            catch (std::exception &e){
                std::cout << START_RED << e.what() << END_RED << std::endl;
            }
        }
        else if (!logical_err_.empty()){
            std::cout << START_RED << "Logical error at line " << logic_err_line_num_ << ": "  << END_RED << logical_err_ << std::endl;
        }
    }
    else
        std::cout << "File " << filename << " cannot be opened!" << std::endl;
}

void  AbstractVm::read_file(std::ifstream & file)
{
    while (getline(file, line_) && !is_exit_) {
        tokens.clear();
        line_num_++;
        lexer_.split_tokens(line_);
        if (tokens.empty())
            continue;
        try {
            parser_.check_syntax_errors();
        }
        catch (std::exception &e) {
            parser_error_num_++;
            std::cout << "at line " << line_num_ << ": "  << END_RED << e.what() << std::endl;
            continue;
        }
        if (parser_error_num_ == 0 && logic_err_line_num_ == 0)
        {
            try {
                parser_.check_logic_errors(operands_);
            }
            catch (std::exception &e) {
                logical_err_ = e.what();
                logic_err_line_num_ = line_num_;
                continue;
            }
            try {
                run_avm();
            }
            catch (std::exception &e) {
                logical_err_ = e.what();
                logic_err_line_num_ = line_num_;
                continue;
            }
        }
    }
}

void  AbstractVm::run_avm()
{
    try {
        if (tokens[0].type == Instr_val)
            run_value_instr();
        else if (tokens[0].type == Instr_calc)
            run_calculate_instr();
        else //my_sqrt|pop|dump|print|exit
            run_other_instr();
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}

void AbstractVm::run_value_instr()
{
    IOperand const*  tmp;
    try {
        tmp = factory.createOperand(valueType_.at(tokens[1].name), tokens[2].name);
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
    if (tokens[0].name == "push")
        operands_.push_back(tmp);
    else if (*(operands_.back()) != *tmp)
    {
        delete tmp;
        throw AssertErr("Assert parameter value is not equal to the value at the top of the stack");
    }
    else
        delete tmp;
}

void  AbstractVm::run_calculate_instr()
{
    IOperand const* (Instruction::*reference)(IOperand const* &op1, IOperand const* &op2);
    reference = parser_.getCalcMap().at(tokens[0].name);
    IOperand const *op1 = operands_.back();
    operands_.pop_back();
    IOperand const *op2 = operands_.back();
    operands_.pop_back();
    IOperand const *res;
    try {
        res = ((instruction_.*reference)(op1, op2));
    }
    catch (std::logic_error &e)
    {
        delete op1;
        delete op2;
        throw std::logic_error(e);
    }
    delete op1;
    delete op2;
    operands_.push_back(res);
}

void AbstractVm::run_other_instr()
{
    void (Instruction::*reference)(std::vector<IOperand const *> &operands_);
    reference = parser_.getInstrMap().at(tokens[0].name);
    try {
        return ((instruction_.*reference)(operands_));
    }
    catch (std::logic_error &e) {
        throw std::logic_error(e);
    }
}
