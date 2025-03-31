#include <mpi.h>
#include <iostream>
#include <omp.h>
#include <cmath>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

double start_time, end_time;


    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


int n=4; // Количество нитей
    if (rank == 0) {
        std::cout << "Input number of threads (n): ";
       // std::cin >> n;

    }
    start_time = MPI_Wtime();
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    const int N = 10000; // Общее количество интервалов
    double local_sum = 0.0;

    #pragma omp parallel num_threads(n)
    {
        int local_N = N / n;

        int thread_id = omp_get_thread_num();

        int start = thread_id * local_N;
        int end = (thread_id == n - 1) ? N : start + local_N;
        double thread_sum = 0.0;

        for (int i = start; i < end; ++i) {
            double x = (i + 0.5) / N;
        thread_sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp atomic
        local_sum += thread_sum;
    }


        double global_sum;
        MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        if (rank == 0) {
        double pi = global_sum / (N*size);
        std::cout << "Approximation of pi: " << pi << std::endl;
        }

    end_time = MPI_Wtime();
    std::cout << "Time taken: " << end_time - start_time << std::endl;
    MPI_Finalize();
    return 0;
}
