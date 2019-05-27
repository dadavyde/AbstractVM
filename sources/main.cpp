/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 17:25:00 by dadavyde          #+#    #+#             */
/*   Updated: 2019/04/13 17:25:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.hpp"

int main(int argc, char *argv[])
{
    AbstractVm  abstract_vm;

    if (argc > 2)
    {
        std::cout << START_RED << "Invalid number of arguments" << END_RED << std::endl;
        return (0);
    }
    else if (argc == 1)
        abstract_vm.read_input();
    else
    {
        std::string file(argv[1]);
        abstract_vm.try_read_from_file(file);
    }
}
