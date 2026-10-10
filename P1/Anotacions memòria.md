# PDF 1
## Tasca 2
- RIFF: bytes 0-3
- fmt : bytes 12-15
- data: bytes 36-39
- Nombre de canals: 1
- Freqüència de mostreig: 16000 (16 kHz)
- Nombre de mostres: 0x00045DA0 (286112 bytes), dos bytes per mostra ==> 143056 mostres

## Tasca 3
```
[0] peio:~/Documents/PAV/P1 $ sox PAV.wav -e mu-law -r 8000 PAV.au
[0] peio:~/Documents/PAV/P1 $ file PAV.wav
PAV.wav: RIFF (little-endian) data, WAVE audio, Microsoft PCM, 16 bit, mono 16000 Hz
[0] peio:~/Documents/PAV/P1 $ file PAV.au
PAV.au: Sun/NeXT audio data: 8-bit ISDN mu-law, mono, 8000 Hz
```

