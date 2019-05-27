/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:10:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/21 18:10:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exceptions.hpp"

/*
 * Lexical Error
 * */

LexicalErr::LexicalErr() {
    std::cout << START_RED << "Lexical error ";
}

UnknownInstrErr::UnknownInstrErr(){}

UnknownInstrErr::UnknownInstrErr(char* instr) : instr_(instr) {
    instr_.insert(0, "Unknown instruction: ");
}

UnknownInstrErr::UnknownInstrErr(std::string & instr) : instr_(instr) {
    instr_.insert(0, "Unknown instruction: ");
}

UnknownInstrErr::~UnknownInstrErr() noexcept {};

UnknownInstrErr& UnknownInstrErr::operator=(const UnknownInstrErr &other) {
    if (this != &other)
        instr_ = other.instr_;
    return (*this);
}

UnknownInstrErr::UnknownInstrErr(const UnknownInstrErr &other) {
    *this = other;
}

const char* UnknownInstrErr::what() const noexcept{
    return (instr_.c_str());
}

/*
 * Syntax errors
 * */

SyntaxErr::SyntaxErr() {
    std::cout << START_RED << "Syntax error ";
}

const char* InstrErr::what() const noexcept {
    return "Bad value after instruction.";
}

const char* NoValueErr::what() const noexcept {
    return "No value after instruction.";
}

BadTypeValueErr::BadTypeValueErr(const char *instr) : instr_(instr)  {
    std::cout << "Unknown type value.";

}

BadTypeValueErr::BadTypeValueErr(std::string const & instr) : instr_(instr)  {
    std::cout << "Unknown type value.";
}

BadTypeValueErr::~BadTypeValueErr() noexcept {}

BadTypeValueErr& BadTypeValueErr::operator=(const BadTypeValueErr &other) {
    if (this != &other)
        instr_ = other.instr_;
    return (*this);
}

BadTypeValueErr::BadTypeValueErr(const BadTypeValueErr &other) noexcept {
    *this = other;
}

const char* BadTypeValueErr::what() const noexcept {
    return (instr_.c_str());
}

const char* TypeValueErr::what() const noexcept{
    return "Wrong type of value.";
}

/*
 * Logical errors
 * */

LogicalErr::LogicalErr()
{
    std::cout << "Logical error ";
}

EmptyStackErr::EmptyStackErr(const char *a) : std::logic_error(a){
    std::string tmp(a);
    instr_name_ = "Instruction " + tmp + " on an empty stack";
}

EmptyStackErr::EmptyStackErr(const std::string &a) : std::logic_error(a){
    instr_name_ = "Instruction " + a + " on an empty stack";
}

const char* EmptyStackErr::what() const noexcept {
    return instr_name_.c_str();
}

NonPrintableInt::NonPrintableInt(const char *a) : std::logic_error(a) {}

NonPrintableInt::NonPrintableInt(const std::string &a) : std::logic_error(a) {}

const char* NonPrintableInt::what() const noexcept{
    return "Cannot print this value";
}

TooSmallStackErr::TooSmallStackErr(const char *a) : std::logic_error(a) {
    std::string tmp(a);
        instr_name_ = "The stack is composed of strictly less that two values when an arithmetic instruction " + tmp + " is executed";
}

TooSmallStackErr::TooSmallStackErr(const std::string &a) : std::logic_error(a) {
    instr_name_ = "The stack is composed of strictly less that two values when an arithmetic instruction " + a + " is executed";
}

const char* TooSmallStackErr::what() const noexcept {
    return instr_name_.c_str();
}

NoExitErr::NoExitErr(const char *a) : std::logic_error(a) {}

NoExitErr::NoExitErr(const std::string &a) : std::logic_error(a) {}

const char* NoExitErr::what() const noexcept {
    return "The instruction \"exit\" is missing at the end of the file";
}

UnderflowErr::UnderflowErr(const char *a) : std::underflow_error(a), instr_name_(a) {}

UnderflowErr::UnderflowErr(const std::string &a) : std::underflow_error(a), instr_name_(a) {}

const char* UnderflowErr::what() const noexcept {
    return (instr_name_.empty() ? "Underflow of value" : instr_name_.c_str());
}

OverflowErr::OverflowErr(const char *a) : std::overflow_error(a) {}

OverflowErr::OverflowErr(const std::string &a) : std::overflow_error(a) {}

const char* OverflowErr::what() const noexcept {
    return "Overflow of value";
}

ZeroDivException::ZeroDivException(const char *a) : std::logic_error(a), instr_name_(a){
}

ZeroDivException::ZeroDivException(const std::string &a) : std::logic_error(a), instr_name_(a) {}

const char* ZeroDivException::what() const noexcept {
    return instr_name_.c_str();
}

FloatPointErr::FloatPointErr(const char *a) : std::logic_error(a), instr_name_(a) {}

FloatPointErr::FloatPointErr(const std::string &a) : std::logic_error(a), instr_name_(a) {}

const char* FloatPointErr::what() const noexcept {
    return instr_name_.c_str();
}

NegativeValErr::NegativeValErr(const char *a) : std::logic_error(a) {}

NegativeValErr::NegativeValErr(const std::string &a) : std::logic_error(a) {}

const char* NegativeValErr::what() const noexcept {
    return "Cannot find my_sqrt from negative value";
}

AssertErr::AssertErr(const char *a) : std::logic_error(a) {}

AssertErr::AssertErr(const std::string &a) : std::logic_error(a) {}

const char* AssertErr::what() const noexcept {
    return "Assert parameter value is not equal to the value at the top of the stack";
}