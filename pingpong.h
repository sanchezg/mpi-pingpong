#ifndef _PINGPONG_H_
#define _PINGPONG_H_

/* Constantes locales */
#define MASTER	0
#define ESCLAVO	1

/* Tamaño de los datos a enviar */

#define SIZE0	1024		/* 2^10 */
#define SIZE1	4096		/* 2^12 */
#define SIZE2	8192		/* 2^13 */
#define SIZE3	16384		/* 2^14 */
#define SIZE4	32768		/* 2^15 */

#define SIZE5	65536		/* 2^16 */
#define SIZE6	131072		/* 2^17 */
#define SIZE7	262144		/* 2^18 */
#define SIZE8	524288		/* 2^19 */
#define SIZE9	1048576		/* 2^20 */

/* Cantidad de envíos a hacer */
#define ENVIOS	50

/* Menu del programa */
#define MENU_ENVIOS	"## Ingrese la cantidad de envíos:\
			\n## 1)    100\
			\n## 2)  1.000\
			\n## 3) 10.000\n"

/* Funciones */
void obtener_info_sist();
void master_func(int size, int envios, MPI_Status estado);

#endif /* _PINGPONG_H_ */
