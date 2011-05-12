/* PingPong2 Lo que hace es enviar el mismo dato con diferentes envíos */

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include "pingpong2.h"

int main(int argc, char **argv)
{
	int proc_id, n_procs, i, envios;
	int buffer[SIZE];
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
		/*MPI_Send(&envios, sizeof(envios), MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);

		printf("## Comienzo del envío con: %d envios;\n", envios);
		printf("## Tamaño de datos:\n");
		printf("## \tSIZE = %d\n", SIZE);
		printf("\n");*/
	}

	MPI_Barrier(MPI_COMM_WORLD);
	if (proc_id == MASTER)
	{
		master_func(ENVIOS_1, buffer, estado);
		master_func(ENVIOS_2, buffer, estado);
		master_func(ENVIOS_3, buffer, estado);
		master_func(ENVIOS_4, buffer, estado);
	}
	else
	{
		/* Primero, recibir del maestro el dato de envios */
		//MPI_Recv(&envios, sizeof(envios), MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);

		/* Ahora realizar el recibo y envío con esa cantidad */
		for(i = 0; i < ENVIOS_1; ++i)
		{
			MPI_Recv(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer[0] += 1;
			MPI_Send(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < ENVIOS_2; ++i)
		{
			MPI_Recv(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer[0] += 1;
			MPI_Send(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < ENVIOS_3; ++i)
		{
			MPI_Recv(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer[0] += 1;
			MPI_Send(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < ENVIOS_4; ++i)
		{
			MPI_Recv(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer[0] += 1;
			MPI_Send(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}
	}

	/* Terminar entorno */
	MPI_Finalize ();
	exit(EXIT_SUCCESS);
}

void master_func(int envios, int buffer, MPI_Status estado)
{
	double t_transcurrido;
	double t_inicio = MPI_Wtime();
	for (int i = 0; i < envios; ++i)
	{
		buffer[0] = i;
		MPI_Send(buffer, SIZE, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
		MPI_Recv(buffer, SIZE, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
	}
	t_transcurrido = MPI_Wtime() - t_inicio;
	printf("## tiempo transcurrido para el envío 0: %g\n", t_transcurrido);
	printf("## tiempo promedio por envío: %g\n", t_transcurrido/envios);
	return;
}

