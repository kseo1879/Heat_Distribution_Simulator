#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <pthread.h>
#include <string.h>

#define N (100)
#define PRINT (10) //IT WILL PRINT PRINT X PRINT 
#define ITERATION (5000) 
#define ROOM_TEMP (20.0)
#define FIRE_TEMP (100.0)
#define FIRE_PERCENTAGE (0.4)
#define THREAD_NUM (4)

void heat_point_init_2d(double *heat_points);
void heat_point_init_3d(double *heat_points);
void iterate_2d(double* heat_points, double* temp_heat_points); 
int iterate_3d(double* heat_points);
void print_heat_point_2d(double * heat_points);
void print_heat_point_3d(double * heat_points, int index);

int main(int argc, char **argv) {

    //Error Handling
    if(argc < 2) {
        perror("You need to specify whether it's 2d of 3d\n");
        return -1;
    }

    double *heat_points = NULL;
    double *temp_heat_points = NULL; 

    //2d array
    if(0 == strcmp("2d", argv[1])) {

        heat_points = malloc(sizeof(double) * N * N);
        temp_heat_points = malloc(sizeof(double) * N * N);

        heat_point_init_2d(heat_points);
        heat_point_init_2d(temp_heat_points);

        iterate_2d(heat_points, temp_heat_points);

        print_heat_point_2d(heat_points);

        free(temp_heat_points);
        free(heat_points);

    } else if(0 == strcmp("3d", argv[1])) {

        heat_points = malloc(sizeof(double) * N * N * 2);

        heat_point_init_3d(heat_points);

        int index = 0;

        index = iterate_3d(heat_points);

        print_heat_point_3d(heat_points, index);

        free(heat_points);
    } else {
        perror("Not a correct type of argument provided it should be 2d or 3d\n");
        return -1;
    }

    return 0;
}

void heat_point_init_2d(double *heat_points) {

    double beginning_offset = (1 - FIRE_PERCENTAGE) / 2;
    double ending_offset = 1 - beginning_offset;
    
    //Initializing heat points for i and j
    for(int i = 0; i < N; i ++) {
        for(int j = 0; j < N; j++) {
            //Intializing the firewall place
            if(i == 0 && 
                ((j >= beginning_offset * N) && (j < ending_offset * N))) {
                    heat_points[i * N + j] = (double) FIRE_TEMP;
            } else {
                heat_points[i * N + j] = (double) ROOM_TEMP;
            }
        }
    }
}

void heat_point_init_3d(double *heat_points) {

    double beginning_offset = (1 - FIRE_PERCENTAGE) / 2;
    double ending_offset = 1 - beginning_offset;
    
    //Initializing heat points for i and j
    for(int i = 0; i < N; i ++) {
        for(int j = 0; j < N; j++) {
            //Intializing the firewall place
            if(i == 0 && 
                ((j >= beginning_offset * N) && (j < ending_offset * N))) {
                    heat_points[i * 2 * N + (j * 2)] = (double) FIRE_TEMP;
                    heat_points[i * 2 * N + (j * 2 + 1)] = (double) FIRE_TEMP;
            } else {
                heat_points[i * 2 * N + (j * 2)] = (double) ROOM_TEMP;
                heat_points[i * 2 * N + (j * 2 + 1)] = (double) ROOM_TEMP;
            }
        }
    }
}

void iterate_2d(double* heat_points, double* temp_heat_points) {

    omp_set_num_threads(THREAD_NUM);

    double *h = heat_points;
    double *g = temp_heat_points;

    for (int iteration = 0; iteration < ITERATION; iteration++) {
                
        #pragma omp parallel for //schedule(static)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                    g[i * N + j] = 0.25 * (h[((i - 1) * N) + j] + h[((i + 1) * N) + j] 
                        + h[(i * N) + j - 1] + h[(i * N) + j + 1]);
            }       
        }

        #pragma omp parallel for //schedule(static)
        for (int i = 1; i < N - 1; i++) { 
            for (int j = 1; j < N - 1; j++) {
                h[i * N + j] = g[i * N + j];
            }       
        }
    }
}

int iterate_3d(double* heat_points) {

    omp_set_num_threads(THREAD_NUM);

    double *h = heat_points;
    int index = 1;
    int opp_index = 0;

    for (int iteration = 0; iteration < ITERATION; iteration++) {

        if(0 == index) {
            index = 1;
            opp_index = 0;
        } else {
            index = 0;
            opp_index = 1;
        }
                
        #pragma omp parallel for //schedule(static, 8)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                    h[i * 2 * N + (j * 2 + index)] = 0.25 * (h[((i - 1) * 2 * N) + (j * 2 + opp_index)] + h[((i + 1) * 2 * N) + (j * 2 + opp_index)] 
                        + h[(i * 2 * N) + (j - 1) * 2 + opp_index] + h[(i * 2 * N) + (j + 1) * 2 + opp_index]);
            }       
        }
    }

    return index;
}

void print_heat_point_2d(double * heat_points) {

    int leap = N/PRINT;
    double *h = heat_points;

    printf("Printing for 2d implementation\n=============================\n\n");

    for(int i = 0; i < N; i += leap) {
        printf("|");
        for(int j = 0; j < N; j += leap) {
            //Intializing the firewall place
            printf("%.4f|", h[i * N + j]);
        }
        printf("\n");
    }
}

void print_heat_point_3d(double * heat_points, int index) {

    int leap = N/PRINT;
    double *h = heat_points;
    int z = index;

    printf("Printing for 2d implementation\n=============================\n\n");
    // printf("Printing for 3d implementation Parallel\n=============================\n\n");

    for(int i = 0; i < N; i += leap) {
        printf("|");
        for(int j = 0; j < N; j += leap) {
            //Intializing the firewall place
            printf("%.4f|", h[i * 2 * N + (j * 2 + z)]);
        }
        printf("\n");
    }
}

