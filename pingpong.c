#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define MASTER	0
#define ESCLAVO	1

/* Tamaño de los datos a enviar */
#define SIZE1	1024

/* Cantidad de envíos a hacer */
#define ENVIOS	25			

int main(int argc, char **argv)
{
	int proc_id, n_procs, i, buffer[SIZE];
	double t_inicio, t_transcurrido;
	float x;
	MPI_Status estado;

	/* Inicio del entorno MPI */
	MPI_Init (&argc, &argv);

	/* Obtener rango y tamaño del comm_world */
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	/* Sincronizar a todos los procesos */
	MPI_Barrier(MPI_COMM_WORLD);

	/* Unicamente el maestro imprime en pantalla los datos iniciales */ 
	if (proc_id == MASTER)
	{
		system("clear");
		printf("## Cálculo de RTT / Envío Maestro-Esclavo\n\n");
		printf("## Total de procesadores: %d\n", n_procs);
 
		t_inicio = MPI_Wtime();
		printf("## Elaborando dato ... ");
		for (i = 0; i < SIZE; ++i)
			x += i*i;
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("\n");
		printf("## tiempo transcurrido para el calculo: %g\n", t_transcurrido);
		printf("## Comienzo del envío\n\n");
	}

	MPI_Barrier(MPI_COMM_WORLD);
	if (proc_id == MASTER)
	{
		t_inicio = MPI_Wtime();
		for (i = 0; i < ENVIOS; ++i)
		{
			buffer[0] = i;
			MPI_Send(buffer, SIZE, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
			MPI_Recv(buffer, SIZE, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
		}
		t_transcurrido = MPI_Wtime() - t_inicio;
		printf("## tiempo transcurrido para el envío: %g\n", t_transcurrido);
	}
	else
	{
		for(i = 0; i < ENVIOS; ++i)
		{
			MPI_Recv(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD, &estado);
			buffer[0] += 1;
			MPI_Send(buffer, SIZE, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
		}
	}

	/* Terminate MPI */
	MPI_Finalize ();
	exit(EXIT_SUCCESS);
}

