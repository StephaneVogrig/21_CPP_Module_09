/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:06:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 20:27:29 by svogrig          ###   ########.fr       */
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

class PmergeMe
{
	private:

		PmergeMe();
		PmergeMe(const PmergeMe & to_copy);
		~PmergeMe();
		PmergeMe & operator = (const PmergeMe & to_assign);

		static void merge(t_vector & data, int element_size);
		static void merge(t_list & data, int element_size);
		static void insertion(t_vector & data, size_t element_size);
		static void insertion(t_list & data, size_t element_size);
		
		template <typename T>
		static void sort(T & data, int element_size)
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
		
	public:

		template <typename T>
		static void mergeInsertSort(T & data)
		{
			sort(data, 1);
		}
};

#endif
