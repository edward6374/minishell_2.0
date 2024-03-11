/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_detector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehernan <mehernan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:10 by mehernan          #+#    #+#             */
/*   Updated: 2024/03/11 17:37:27 by mehernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//He creado una estructura que se puede usar como nueva lista. Puede parece
//incomodo al principio pero para luego pasarlo a los comandosa sera mas
//facil. Lo que hay que hacer ahora es:
//1. Que es una palabra? --> caracteres que estan determinados por espacios
//si los espacios estan antes que las comillas, lo de dentroo de las comillas
//es una palabra.
//		1.
//		ejemplo: _hola""que'ta  l'_abc
//		todo esto seria una palabra
//		abc es otra palabra
//		2.
//		ejemplo: hola""que'ta  l'abc
//		esto es todo una palabra
//
//2. Se de ben quitar las comillas.
//		ejemplo: "hola que tal"
//		         "kkk''lk"
//		resultado: hola que tal
//		           kkklk
//
