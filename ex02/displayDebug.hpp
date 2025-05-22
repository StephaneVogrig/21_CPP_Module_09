/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayDebug.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:08:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/22 18:30:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAYDEBUG_HPP
# define DISPLAYDEBUG_HPP

#include "PmergeMe.hpp"
#include "utils.hpp"

void displayPendValue(const std::string & intro, const t_vector & data, const t_vector &pend);
void displayVectorByPair(const std::string & intro, const t_vector & vector, size_t elementSize);
void displayLevel(size_t elementSize);

#endif
