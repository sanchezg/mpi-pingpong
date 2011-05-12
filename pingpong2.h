#ifndef _PINGPONG_H_
#define _PINGPONG_H_

/* Constantes locales */
#define MASTER	0
#define ESCLAVO	1

/* Tamaño de los datos a enviar */
#define SIZE	1048576		/* 2^20 */

/* Cantidad de envíos a hacer */
#define ENVIOS_1	50
#define ENVIOS_2	100
#define ENVIOS_3	250
#define ENVIOS_4	500

/* Menu del programa */
#define MENU_ENVIOS	"## Ingrese la cantidad de envíos:\
			\n## 1)    100\
			\n## 2)  1.000\
			\n## 3) 10.000\n"

/* Funciones */
void master_func(int envios, int buffer, MPI_Status estado);

#endif /* _PINGPONG_H_ */
