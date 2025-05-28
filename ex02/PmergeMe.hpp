/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:06:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 04:56:34 by svogrig          ###   ########.fr       */
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

		static void sort(t_vector &data, size_t element_size);
		static void sort(t_list &data, int element_size);
		
	public:

		template <typename T>
		static void mergeInsertSort(T & data)
		{
			sort(data, 1);
		}

};

#endif
