/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:52:37 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 21:18:34 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shellColor.hpp"

template <typename T>
void PmergeMe::sort(T & data, int element_size)
{
	int nbrElement = data.size() / element_size;
	if (nbrElement < 2)
		return ;

	merge(data, element_size);
	sort(data, element_size * 2);
	if (nbrElement < 3)
		return ;
	insertion(data, element_size);
}

template <typename T>
void PmergeMe::mergeInsertSort(T & data)
{
	sort(data, 1);
}
