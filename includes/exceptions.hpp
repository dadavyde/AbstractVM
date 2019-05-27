/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 18:10:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/21 18:10:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_CLION_EXCEPTIONS_HPP
#define ABSTRACT_VM_CLION_EXCEPTIONS_HPP

#include <exception>
#include <iostream>
#include "structs.hpp"

//Lexical Error

class LexicalErr : public std::exception
{
public:
    LexicalErr();
};

class UnknownInstrErr : public LexicalErr
{
public:
    explicit UnknownInstrErr();
    explicit UnknownInstrErr(char* instr);
    explicit UnknownInstrErr(std::string & instr);
    ~UnknownInstrErr() noexcept;
    UnknownInstrErr(const UnknownInstrErr &other);
    UnknownInstrErr &operator=(const UnknownInstrErr &other);
    const char* what() const noexcept;

private:
    std::string  instr_;
};


//Syntax Error

class SyntaxErr : public std::exception
{
public:
    SyntaxErr();
};

class InstrErr : public SyntaxErr
{
    const char* what() const noexcept;
};

class NoValueErr : public SyntaxErr
{
    const char* what() const noexcept;
};

class BadTypeValueErr : public SyntaxErr{
public:
    explicit BadTypeValueErr(const char* instr);
    explicit BadTypeValueErr(std::string const & instr);
    virtual ~BadTypeValueErr() noexcept;
    BadTypeValueErr(const BadTypeValueErr &other) noexcept;
    BadTypeValueErr &operator=(const BadTypeValueErr &other);
    const char* what() const noexcept;

private:
    std::string instr_;
};

class TypeValueErr : public SyntaxErr
{
public:
    const char* what() const noexcept;
};

//Logical

class LogicalErr : public std::exception
{
public:
    LogicalErr();
};

class EmptyStackErr : public std::logic_error
{
public:
    explicit EmptyStackErr(const std::string& a);
    explicit EmptyStackErr(const char* a);
    const char* what() const noexcept;

private:
    std::string  instr_name_;
};

class NonPrintableInt : public std::logic_error
{
public:
    explicit NonPrintableInt(const std::string& a);
    explicit NonPrintableInt(const char* a);
    const char* what() const noexcept;
};

class TooSmallStackErr : public std::logic_error
{
public:
    explicit TooSmallStackErr(const std::string& a);
    explicit TooSmallStackErr(const char* a);
    const char* what() const noexcept;

private:
    std::string  instr_name_;
};

class NoExitErr : public std::logic_error
{
public:
    explicit NoExitErr(const std::string& a);
    explicit NoExitErr(const char* a);
    const char* what() const noexcept;
};

class UnderflowErr : public std::underflow_error
{
public:
    explicit UnderflowErr(const std::string& a);
    explicit UnderflowErr(const char* a);
    const char* what() const noexcept;

private:
    std::string  instr_name_;
};

class OverflowErr : public std::overflow_error
{
public:
    explicit OverflowErr(const std::string& a);
    explicit OverflowErr(const char* a);
    const char* what() const noexcept;
};

class ZeroDivException : public std::logic_error
{
public:
    explicit ZeroDivException(const std::string& a);
    explicit ZeroDivException(const char* a);
    const char* what() const noexcept;

private:
    std::string  instr_name_;
};

class FloatPointErr : public std::logic_error
{
public:
    explicit FloatPointErr(const std::string& a);
    explicit FloatPointErr(const char* a);
    const char* what() const noexcept;

private:
    std::string  instr_name_;
};

class NegativeValErr : public std::logic_error
{
public:
    explicit NegativeValErr(const std::string& a);
    explicit NegativeValErr(const char* a);
    const char* what() const noexcept;
};

class AssertErr : public std::logic_error
{
public:
    explicit AssertErr(const std::string& a);
    explicit AssertErr(const char* a);
    const char* what() const noexcept;
};


#endif
