/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:06:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/27 23:29:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <list>
# include <sstream>
# include <algorithm>
# include <iostream>
# include <exception>

typedef std::vector<int> t_vector;
typedef std::list<int> t_list;
typedef std::list<t_list> t_list_of_list;

template <typename T>
typename T::iterator listMoveIterator(typename T::iterator it, int nbr)
{
	if (nbr > 0)
		while (nbr--)
			it++;
	else
		while (nbr++)
			it--;
	return it;
}

class PmergeMe
{
	private:

		PmergeMe();
		PmergeMe(const PmergeMe & to_copy);
		~PmergeMe();
		PmergeMe & operator = (const PmergeMe & to_assign);

		static void sort(t_vector &data, size_t element_size);
		static void sort(t_list &data, int element_size);
		
	public:

		static void mergeInsertSort(t_vector & data);
		static void mergeInsertSort(std::list<int> & data);

};


#endif