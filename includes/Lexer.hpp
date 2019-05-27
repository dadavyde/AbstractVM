/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:25:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/13 17:25:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ABSTRACT_VM_CLION_LEXER_HPP
#define ABSTRACT_VM_CLION_LEXER_HPP

#include <regex>
#include <iostream>
#include "structs.hpp"

class Lexer
{
public:
	Lexer();
	~Lexer();
	Lexer &operator=(const Lexer &other);
	Lexer(const Lexer &other);

	void  split_tokens(std::string line);
	bool  find_eof(std::string const & line);

private:
	std::vector<std::regex>  regular_exp_;
	std::smatch  match;
};

#endif
