#include <stdio.h>
#include <stdlib.h>


#define CHUNK_X 8
#define CHUNK_Y 8
#define CHUNK_Z 8


int main(){

	FILE *f = fopen("chunk.txt", "w");
	
	int i;
	int j;
	int k;
	int height;
	
	for ( i=0 ; i<CHUNK_X ; i++ ){
		for ( j=0 ; j<CHUNK_Z ; j++ ){
			srand(i*CHUNK_X*CHUNK_Y + j*CHUNK_Y);
			height = rand() % 8;
			for ( k=0 ; k<CHUNK_Y ; k++){
				srand(i*CHUNK_X*CHUNK_Y + j*CHUNK_Y + k);
				fprintf(f, "%i", k < height ? (rand() % 7) + 1 : 0);
			}
		}
	}
	
	fclose(f);
	
	return 0;
	
}
