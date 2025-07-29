/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:58:08 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/29 19:01:25 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_vector	add_vector(t_vector *v1, t_vector *v2)
{
	t_vector	new;

	new.x = v1->x + v2->x;
	new.y = v1->y + v2->y;
	return (new);
}

t_vector	mult_vector(t_vector *v, double n)
{
	t_vector new;

	new.x = v->x *n;
	new.y = v->y *n;
	return (new);
}