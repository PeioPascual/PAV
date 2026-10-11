#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "pav_analysis.h"
#include "fic_wave.h"

int main(int argc, char *argv[]) {
    float durTrm = 0.010;
    float fm;
    int   N;
    int   trm;
    float *x;
    short *buffer;
    FILE  *fpWave;

    FILE *output = stdout, *tmp = NULL;
    short retcd = 0;
    unsigned short nchann, auform, bps;
    unsigned int samples;
    unsigned int Nham, Mham, len;

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Empleo: %s inputfile [outputfile]\n", argv[0]);
        return -1;
    }

    if ((fpWave = abre_wave(argv[1], &fm, &nchann, &auform, &bps, &samples)) == NULL) {
        fprintf(stderr, "Error al abrir el fichero WAVE de entrada %s (%s)\n", argv[1], strerror(errno));
        return -1;
    }

    if (nchann != 1 || auform != 1 || bps != 16) {
        fprintf(stderr, "Formato de audio no soportado.\n");
        return -1;
    }

    N = durTrm * fm;
    if ((buffer = malloc(N * sizeof(*buffer))) == 0 ||
        (x = malloc(N * sizeof(*x))) == 0) {
        fprintf(stderr, "Error al ubicar los vectores (%s)\n", strerror(errno));
        cierra_wave(fpWave);
        free(buffer);
        free(x);
        return -1;
    }

    trm = 0;
    if (argc == 3) {
        if ((tmp = fopen(argv[2], "w")) == NULL) {
            fprintf(stderr, "Error al escribir en el fichero de salida %s (%s)\nSe escribirá por stdout\n\n", argv[2], strerror(errno));
            retcd = 1;
        } else {
            output = tmp;
        }
    }
    while (lee_wave(buffer, sizeof(*buffer), N, fpWave) == N) {
        for (int n = 0; n < N; n++) x[n] = buffer[n] / (float) (1 << 15);

        fprintf(output, "%d\t%f\t%f\t%f\n", trm, compute_power(x, N),
                                        compute_am(x, N),
                                        compute_zcr(x, N, fm));
        trm += 1;
    }

    Nham = fm * 0.02;
    Mham = fm * 0.01;
    len = ((samples - Nham) / Mham) + 1;
    float hamming_pow[len];
    float x_ham[samples];
    short buffer_ham[samples];
    fseek(fpWave, 44, SEEK_SET);
    lee_wave(buffer_ham, sizeof(short), samples, fpWave);
    for (int n = 0; n < samples; n++) x_ham[n] = buffer_ham[n] / (float) (1 << 15);
    compute_power_hamming(len, hamming_pow, x_ham, Nham, Mham);
    fprintf(output, "\n\nUsando la ventana de Hamming:\n");
    for (unsigned int i = 0; i < len; i++) {
        fprintf(output, "%u\t%f\n", i, hamming_pow[i]);
    }

    cierra_wave(fpWave);
    free(buffer);
    free(x);

    if (tmp != NULL) {
        fclose(output);
    }

    return retcd;
}
