#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include "pingpong.h"

int main(int argc, char **argv)
{
	int proc_id, n_procs, i, envios;
	int buffer0[SIZE0], buffer1[SIZE1], buffer2[SIZE2], buffer3[SIZE3], buffer4[SIZE4];
	int buffer5[SIZE5], buffer6[SIZE6], buffer7[SIZE7], buffer8[SIZE8], buffer9[SIZE9];
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

		obtener_info_sist();
		/* Leer de stdin la cantidad de envíos a hacer */
		do
		{
			printf("%s", MENU_ENVIOS);
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
		printf("## \tSIZE5 = %d\n", SIZE5);
		printf("## \tSIZE6 = %d\n", SIZE6);
		printf("## \tSIZE7 = %d\n", SIZE7);
		printf("## \tSIZE8 = %d\n", SIZE8);
		printf("## \tSIZE9 = %d\n", SIZE9);
		printf("\n");
	}

	MPI_Barrier(MPI_COMM_WORLD);
	if (proc_id == MASTER)
	{
		printf("## | tam (b) | envios | t_total (seg) | t/envio (s)  |     kB/s   |\n");
		printf("## |---------|--------|---------------|--------------|------------|\n");
		master_func(SIZE0, envios, estado);
		master_func(SIZE1, envios, estado);
		master_func(SIZE2, envios, estado);
		master_func(SIZE3, envios, estado);
		master_func(SIZE4, envios, estado);
		master_func(SIZE5, envios, estado);
		master_func(SIZE6, envios, estado);
		master_func(SIZE7, envios, estado);
		master_func(SIZE8, envios, estado);
		master_func(SIZE9, envios, estado);
		printf("## |_________|________|_______________|______________|____________|\n");
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
		for(i = 0; i < envios; ++i)
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
	}

	/* Terminar entorno */
	MPI_Finalize ();
	exit(EXIT_SUCCESS);
}

/* Utiliza la llamada uname y un struct predefinido para obtener info del sistema */
void obtener_info_sist()
{
	int dont_care, mpi_subversion, mpi_version;
	struct utsname info;

	uname(&info);
	dont_care = MPI_Get_version(&mpi_version,&mpi_subversion);

	printf("## Arquitectura: \t%s\n",info.machine);
	printf("## Sistema: \t%s\n", info.sysname);
	printf("## Release : \t%s\n",info.release);
	printf("## Version : \t%s\n",info.version);
	printf("## MPI Version : \t%-d.%-d\n",mpi_version,mpi_subversion);
	printf("\n");
	return;
}

/* Función del maestro que utiliza para mandar los datos, y recibir los que envía el esclavo */
/* También calcula los tiempos de demora, y tasa de envío, e imprime los resultados en pantalla */
void master_func(int size, int envios, MPI_Status estado)
{
	int i, buffer[size];
	double t_transcurrido;
	int tamanio;
	double tasa;
	double t_inicio = MPI_Wtime();

	for (i = 0; i < envios; ++i)
	{
		buffer[0] = i;
		MPI_Send(buffer, size, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD);
		MPI_Recv(buffer, size, MPI_INT, ESCLAVO, 0, MPI_COMM_WORLD, &estado);
	}
	t_transcurrido = MPI_Wtime() - t_inicio;

	tamanio = size*32; 					/* Tamaño del dato en bit */
	
	tasa = ((tamanio/(t_transcurrido/envios))/8)/1024;

	printf("## |%9d| %6d | %13g | %12g |%12g|\n", tamanio, envios, t_transcurrido, t_transcurrido/envios, tasa);
	return;
}
