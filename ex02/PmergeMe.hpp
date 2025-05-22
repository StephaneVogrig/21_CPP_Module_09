/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:06:17 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/22 17:21:50 by svogrig          ###   ########.fr       */
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

class PmergeMe
{
	private:

		PmergeMe();
		PmergeMe(const PmergeMe & toCopy);
		~PmergeMe();
		PmergeMe & operator = (const PmergeMe & toAssign);

		static void sort(t_vector &vector, size_t elementSize);
		
	public:

		static void mergeInsertSort(t_vector & vector);
		static void mergeInsertSort(std::list<int> & list);

		static void displayVector(t_vector & vector);




};


#endif