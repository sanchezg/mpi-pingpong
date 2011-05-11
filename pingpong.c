#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include "pingpong.h"

int main(int argc, char **argv)
{
	int proc_id, n_procs, i, buffer1[SIZE1], buffer2[SIZE2], buffer3[SIZE3], buffer4[SIZE4];
	double t_inicio, t_transcurrido;
	MPI_Status estado;

	/* Inicio del entorno MPI */
	MPI_Init (&argc, &argv);

	/* Obtener rango y tamaño del comm_world */
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	if (n_procs > 2)
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

		printf("## Comienzo del envío\n\n");
	}

	MPI_Barrier(MPI_COMM_WORLD);
	if (proc_id == MASTER)
	{
		t_inicio = MPI_Wtime();
		for (i = 0; i < ENVIOS; ++i)
		{
			buffer1[0] = i;
			MPI_Send(buffer1, SIZE1, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer1, SIZE1, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 1: %g\n", t_transcurrido);
		
		t_inicio = MPI_Wtime();
		for (i = 0; i < ENVIOS; ++i)
		{
			buffer2[0] = i;
			MPI_Send(buffer2, SIZE2, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer2, SIZE2, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 2: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < ENVIOS; ++i)
		{
			buffer3[0] = i;
			MPI_Send(buffer3, SIZE3, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer3, SIZE3, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 3: %g\n", t_transcurrido);

		t_inicio = MPI_Wtime();
		for (i = 0; i < ENVIOS; ++i)
		{
			buffer4[0] = i;
			MPI_Send(buffer4, SIZE4, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer4, SIZE4, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío 4: %g\n", t_transcurrido);
	}
	else
	{
		for(i = 0; i < ENVIOS; ++i)
		{
			MPI_Recv(buffer1, SIZE1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer1[0] += 1;
			MPI_Send(buffer1, SIZE1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < ENVIOS; ++i)
		{
			MPI_Recv(buffer2, SIZE2, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer2[0] += 1;
			MPI_Send(buffer2, SIZE2, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < ENVIOS; ++i)
		{
			MPI_Recv(buffer3, SIZE3, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer3[0] += 1;
			MPI_Send(buffer3, SIZE3, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}

		for(i = 0; i < ENVIOS; ++i)
		{
			MPI_Recv(buffer4, SIZE4, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer4[0] += 1;
			MPI_Send(buffer4, SIZE4, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}
	}

	/* Terminate MPI */
	MPI_Finalize ();
	exit(EXIT_SUCCESS);
}

