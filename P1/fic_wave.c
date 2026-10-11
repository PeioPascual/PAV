#include <stdio.h>
#include "fic_wave.h"

FILE    *abre_wave(const char *ficWave, float *fm, unsigned short *nchann, unsigned short *auform, unsigned short *bps, unsigned int *samples) {
    FILE    *fpWave;
    unsigned int freq;

    if ((fpWave = fopen(ficWave, "r")) == NULL) return NULL;

    if (fseek(fpWave, 22, SEEK_SET) < 0) return NULL;
    fread(nchann, 2, 1, fpWave);

    if (fseek(fpWave, 20, SEEK_SET) < 0) return NULL;
    fread(auform, 2, 1, fpWave);

    if (fseek(fpWave, 34, SEEK_SET) < 0) return NULL;
    fread(bps, 2, 1, fpWave);

    if (fseek(fpWave, 24, SEEK_SET) < 0) return NULL;
    if (fread(&freq, 4, 1, fpWave) == 1) {
        *fm = (float)freq;
    }

    if (fseek(fpWave, 40, SEEK_SET) < 0) return NULL;
    fread(samples, 4, 1, fpWave);
    *samples /= *bps / 8;

    if (fseek(fpWave, 44, SEEK_SET) < 0) return NULL;

    return fpWave;
}

size_t   lee_wave(void *x, size_t size, size_t nmemb, FILE *fpWave) {
    return fread(x, size, nmemb, fpWave);
}

void    cierra_wave(FILE *fpWave) {
    fclose(fpWave);
}
