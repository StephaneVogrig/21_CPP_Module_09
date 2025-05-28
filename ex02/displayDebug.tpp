/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayDebug.tpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:24:51 by svogrig           #+#    #+#             */
/*   Updated: 2025/05/28 22:36:32 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <typename T>
void displayByPair(const std::string & intro, const T & data, size_t element_size)
{
	std::cout << intro;

	typename T::const_iterator it = data.begin();
	for (size_t i = 0; i < data.size(); ++i)
	{
		if (isFirstInElement(i, element_size))
			std::cout << getPairColor(i, element_size, data.size());

		if (isLastInElement(i, element_size))
			std::cout << ' ' << BOLD_ON << *it << BOLD_OFF;
		else
			std::cout << ' ' << *it;
		++it;
	}
	std::cout <<  RESET << std::endl;
}
