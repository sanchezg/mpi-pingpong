#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include "pingpong.h"

int main(int argc, char **argv)
{
	int proc_id, n_procs, i, envios;
	int buffer0[SIZE0], buffer1[SIZE1], buffer2[SIZE2], buffer3[SIZE3], buffer4[SIZE4];
//	double buffer5[SIZE5], buffer6[SIZE6], buffer7[SIZE7], buffer8[SIZE8], buffer9[SIZE9];
	double t_inicio, t_transcurrido;
	MPI_Status estado;

	/* Inicio del entorno MPI */
	MPI_Init (&argc, &argv);

	/* Obtener rango y tamaño del comm_world */
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	if (n_procs != 2)
	{
		printf("## Este programa utiliza 2 procesos\n");
		exit(EXIT_FAILURE);
	}

	/* Sincronizar a todos los procesos */
	MPI_Barrier(MPI_COMM_WORLD);

	/* Unicamente el maestro imprime en pantalla los datos iniciales */ 
	if (proc_id == MASTER)
	{
		system("clear");
		printf("## Cálculo de RTT / Envío Maestro-Esclavo\n\n");
		printf("## Total de procesadores: %d\n", n_procs);

		/* Leer de stdin la cantidad de envíos a hacer */
		do
		{
			printf("%s", MENU_ENVIOS);
			printf("## ");
			scanf("%d", &envios);
		} while ((envios != 1) && (envios != 2) && (envios != 3));

		switch (envios)
		{
			case 1:
				envios = 100;
				break;
			case 2:
				envios = 1000;
				break;
			case 3:
				envios = 10000;
				break;
			default:
				break;
		}

		/* Enviar dato a los procesos */
		MPI_Send(&envios, sizeof(envios), MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);

		printf("## Comienzo del envío con: %d envios;\n", envios);
		printf("## Tamaño de datos:\n");
		printf("## \tSIZE0 = %d\n", SIZE0);
		printf("## \tSIZE1 = %d\n", SIZE1);
		printf("## \tSIZE2 = %d\n", SIZE2);
		printf("## \tSIZE3 = %d\n", SIZE3);
		printf("## \tSIZE4 = %d\n", SIZE4);
/*		printf("## \tSIZE5 = %d\n", SIZE5);
		printf("## \tSIZE6 = %d\n", SIZE6);
		printf("## \tSIZE7 = %d\n", SIZE7);
		printf("## \tSIZE8 = %d\n", SIZE8);
		printf("## \tSIZE9 = %d\n", SIZE9);
*/		printf("\n");
	}

	MPI_Barrier(MPI_COMM_WORLD);
	if (proc_id == MASTER)
	{
		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer0[0] = i;
			MPI_Send(buffer0, SIZE0, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer0, SIZE0, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 0: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer1[0] = i;
			MPI_Send(buffer1, SIZE1, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer1, SIZE1, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 1: %g\n", t_transcurrido);
	
		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer2[0] = i;
			MPI_Send(buffer2, SIZE2, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer2, SIZE2, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 2: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer3[0] = i;
			MPI_Send(buffer3, SIZE3, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer3, SIZE3, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}

		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 3: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer4[0] = i;
			MPI_Send(buffer4, SIZE4, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer4, SIZE4, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 4: %g\n", t_transcurrido);
/*
		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer5[0] = i;
			MPI_Send(buffer5, SIZE5, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer5, SIZE5, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 5: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer6[0] = i;
			MPI_Send(buffer6, SIZE6, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer6, SIZE6, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 6: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer7[0] = i;
			MPI_Send(buffer7, SIZE7, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer7, SIZE7, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 7: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer8[0] = i;
			MPI_Send(buffer8, SIZE8, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer8, SIZE8, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 8: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < envios; ++i)
		{
			buffer9[0] = i;
			MPI_Send(buffer9, SIZE9, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer9, SIZE9, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 9: %g\n", t_transcurrido);
*/
	}
	else
	{
		/* Primero, recibir del maestro el dato de envios */
		MPI_Recv(&envios, sizeof(envios), MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);

		/* Ahora realizar el recibo y envío con esa cantidad */
		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer0, SIZE0, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer0[0] += 1;
			MPI_Send(buffer0, SIZE0, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer1, SIZE1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer1[0] += 1;
			MPI_Send(buffer1, SIZE1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer2, SIZE2, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer2[0] += 1;
			MPI_Send(buffer2, SIZE2, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer3, SIZE3, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer3[0] += 1;
			MPI_Send(buffer3, SIZE3, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer4, SIZE4, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer4[0] += 1;
			MPI_Send(buffer4, SIZE4, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}
/*		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer5, SIZE5, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer5[0] += 1;
			MPI_Send(buffer5, SIZE5, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer6, SIZE6, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer6[0] += 1;
			MPI_Send(buffer6, SIZE6, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer7, SIZE7, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer7[0] += 1;
			MPI_Send(buffer7, SIZE7, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer8, SIZE8, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer8[0] += 1;
			MPI_Send(buffer8, SIZE8, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < envios; ++i)
		{
			MPI_Recv(buffer9, SIZE9, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer9[0] += 1;
			MPI_Send(buffer9, SIZE9, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}
*/	}

	/* Terminate MPI */
	MPI_Finalize ();
	exit(EXIT_SUCCESS);
}

