#include <stdio.h>
#include <stdlib.h>

//Programa que converte um arquivo musica.wav para um resultado.c, que contem o código fonte com as amostras música wav. No fim imprime quantos elementos o vetor possui
int main(int argc, char** argv) {
	FILE* f = fopen("score.wav", "rb");
	FILE* r = fopen("score.c","wb+");

    fprintf(r,"int audio_score[] = {\n");
	int t;
	fseek(f,24,0);
	fread(&t, 4, 1, f);
	printf("\nsample rate: %d",t);
	fseek(f,34,0);
	printf("\nbits/sample: %d",t);
	fseek(f,44,0);

	fseek(f,44,0);
    unsigned long n = 0;
    int cont=0;
    while(!feof(f)) {
        unsigned int c;
        if(fread(&c, 3, 1, f) == 0) break;
        cont++;
        fprintf(r,"%#08X00,", (int)c);
        ++n;
        if(n % 10 == 0) printf("\n");
    }
    fclose(f);
    fprintf(r,"};\n");
	fclose(r);
	printf("\ntam vetor: %d",cont);
	//getch();
}