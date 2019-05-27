/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 19:38:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/05/08 19:38:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#define START_RED ("\033[1;31m")
#define END_RED ("\033[0m")
#define START_YELLOW ("\033[33m")
#define END_YELLOW ("\033[0m")
#define START_CYAN ("\033[36m")
#define END_CYAN ("\033[0m")

#include <iostream>
#include <vector>

enum eOperandType {Int8, Int16, Int32, Float, Double};
enum eTokenType {Comment, Print_text, Blank, Instr_val, Instr_calc, Instr_no_val, Type_N, Type_Z, Value_N, Value_Z, Eof, Unknown_instr};

struct Token
{
    std::string  name;
    eTokenType   type;
};

extern std::vector<Token>  tokens;

extern bool  is_exit_;

#endif