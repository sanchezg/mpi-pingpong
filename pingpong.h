#ifndef _PINGPONG_H_
#define _PINGPONG_H_

/* Constantes locales */
#define MASTER	0
#define ESCLAVO	1

/* Tamaño de los datos a enviar */
#define SIZE0	1024		/* 2^10 */
#define SIZE1	16384		/* 2^14 */
#define SIZE2	262144		/* 2^18 */
#define SIZE3	1048576		/* 2^20 */
#define SIZE4	1048576		/* 2^20 */

#define SIZE5	524288		/* 2^19 */
#define SIZE6	1048576		/* 2^20 */
#define SIZE7	2097152		/* 2^21 */
#define SIZE8	4194304		/* 2^22 */
#define SIZE9	8388608		/* 2^22 */

/* Cantidad de envíos a hacer */
#define ENVIOS	50

/* Menu del programa */
#define MENU_ENVIOS	"## Ingrese la cantidad de envíos:\
			\n## 1)    100\
			\n## 2)  1.000\
			\n## 3) 10.000\n"

#endif /* _PINGPONG_H_ */
