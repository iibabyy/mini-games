/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 20:17:12 by ibaby             #+#    #+#             */
/*   Updated: 2024/09/16 17:07:00 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst) {
  int i;
  t_list *count;

  i = 1;
  if (!lst)
    return (0);
  count = lst->next;
  while (count) {
    count = count->next;
    i++;
  }
  return (i);
}
