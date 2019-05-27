/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:25:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/13 17:25:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

std::vector<Token>  tokens;

Lexer::Lexer()
{
    regular_exp_.push_back((std::regex)"^\\s*(;)");//Comment
    regular_exp_.push_back((std::regex)"^\"[^\"]+\"$");//Print_text
    regular_exp_.push_back((std::regex)"^\\s*$");//Blank
    regular_exp_.push_back((std::regex)"^\\s*(push|assert)(\\s*)");//Instr_val
    regular_exp_.push_back((std::regex)"^\\s*(add|sub|mul|div|mod|pow)\\s*(\\w*)");//Instr_calc
    regular_exp_.push_back((std::regex)"^\\s*(sqrt|pop|dump|print|exit)\\s*(\\w*)");//Instr_no_val
    regular_exp_.push_back((std::regex)"^\\s+(int8|int16|int32)\\s*(\\w*)");//Type_N
    regular_exp_.push_back((std::regex)"^\\s+(float|double)\\s*(\\w*)");//Type_Z
    regular_exp_.push_back((std::regex)"^\\(\\s*([-]?\\d+)\\s*\\)\\s*(\\w*)");//Value_N
    regular_exp_.push_back((std::regex)"^\\(\\s*([-]?\\d+\\.\\d+)\\s*\\)\\s*(\\w*)");//Value_Z
    regular_exp_.push_back((std::regex)"(;;)");//Eof
}

Lexer::~Lexer()
{}

Lexer& Lexer::operator=(const Lexer &other)
{
    if (this != &other)
    {
        this->match = other.match;
        this->regular_exp_ = other.regular_exp_;
    }
    return *this;
}

Lexer::Lexer(const Lexer &other)
{
    *this = other;
}

bool Lexer::find_eof(std::string const & line) {
    return (regex_search(line, match, regular_exp_[Eof]));
}

void Lexer::split_tokens(std::string line)
{
    if (regex_search(line, match, regular_exp_[Print_text]) == true)//bonus
    {
        line.erase (line.begin());
        line.erase (line.end()-1);
        std::cout << START_CYAN << line << END_CYAN << std::endl;
        return;
    }
    if (regex_search(line, match, regular_exp_[Comment]) == true || regex_search(line, match, regular_exp_[Blank]) == true)//comment or blank line
        return ;
    for (int i = Instr_val; i <= Value_Z; i++)
        if (regex_search(line, match, regular_exp_[i]) == true)
        {
            tokens.push_back((Token) {(match.str(1)), static_cast<eTokenType>(i)});
            line.erase(0, match.position(2));
        }
    if (!line.empty() && line[0] != ';')//error after instruction
        tokens.push_back((Token){line, Unknown_instr});
}
