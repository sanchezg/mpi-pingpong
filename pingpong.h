#ifndef _PINGPONG_H_
#define _PINGPONG_H_

/* Constantes locales */
#define MASTER	0
#define ESCLAVO	1

/* Tamaño de los datos a enviar */
#define SIZE1	1024
#define SIZE2	65536
#define SIZE3	131072
#define SIZE4	524288

/* Cantidad de envíos a hacer */
#define ENVIOS	50

/* Menu del programa */
#define MENU_DATOS	"## Ingrese la cantidad de datos:\n\
				## 1) 10 datos.\n\
				## 2) 25 datos.\n\
				## 3) 50 datos.\n"

#define MENU_ENVIOS	"## Ingrese la cantidad de envíos:\n\
					## 1)    100\n\
					## 2)  1.000\n\
					## 3) 10.000\n\"

#endif /* _PINGPONG_H_ */
