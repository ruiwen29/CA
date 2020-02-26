#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


long size; 
int plateau;
FILE * fp;
int registre[8] = {0,0,0,0,0,0,0,0};
unsigned int** tab_plateaux;
int taille_collection = 1; //La taille de la collection de plateaux est initialisée à 1 
int reader(){   //read a byte form data source
    int ch;
    int res;
    for(int i =0 ;i<4;i++){
        ch = fgetc(fp);
        res += ch << 8*(3-i);
        if(ch == EOF) return EOF;
    }
    return res;
}

void init(char *filename){
    int j= 0;
    fp = fopen(filename,"rb+");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    tab_plateaux = calloc(taille_collection, sizeof(*tab_plateaux));
    tab_plateaux[0] = calloc(size/4, sizeof(*(tab_plateaux[0])));
    fseek(fp,0,SEEK_SET); //Remettre le pointeur au début du fichier afin d'en charger le contenu par la suite

    while(!feof(fp)){
        
        int ch;
        int res;
 		res = reader();
        //printf("%x\n",res);

 		tab_plateaux[0][j] = (unsigned int) res ;     
        //printf("%x ",fgetc(fp));
        // printf("%x ",tab_plateaux[0][j]);
		j++;
        
	}
      fclose(fp);

}
int runtime(){
    int j = 0;
    int i = -1; // i  l'index d'exécution
    while(1) {
    j++;
    i++; 
    unsigned int A, B, C; 
    long int operateur; 

    // l'index du registre A en appliquant un mask sur les 3 bits concernés
    A = (tab_plateaux[0][i] & (7 << 6));
    A >>= 6;
    //l'index du registre B
    B = (tab_plateaux[0][i] & (7 << 3));
    B >>= 3;
    // l'index du registre C
    C = (tab_plateaux[0][i] & 7);

    //Récupération de l'opérateur
    operateur = (long int) (tab_plateaux[0][i]) & (15<<28);
    operateur >>= 28;


    printf("Boucle %d | Operator : %ld | A : %u B : %u C : %u\n",i,operateur,registre[A],registre[B],registre[C]);
    int valeur; //
    switch(operateur) {
    case 0 : /** Conditional Move **/
        if(registre[C] != 0) {
            registre[A] = registre[B];
        }
      break;

    case 1 : /** Array Index **/
      registre[A] = tab_plateaux[registre[B]][registre[C]];
      break;

    case 2 : /** Array Amendment **/
      tab_plateaux[registre[A]][registre[B]] = registre[C];
      break;

    case 3 : /** Addition **/
      registre[A] = (registre[B]+registre[C]);
      break;

    case 4 : /** Muliplication **/
      registre[A] = (registre[B]*registre[C]); 
      break;

    case 5 : /** Division **/
      if(registre[C]) //vérifier c!= 0
        registre[A] = registre[B]/registre[C];
      break;

    case 6 : /** Not-And **/
      registre[A] = ~(registre[B] & registre[C]);
      break;

    case 7 : /** Halt **/
      //Stoppe la Machine Universelle
      exit(0);
      break;

    case 8 : /** Allocation **/
      ++taille_collection;
      tab_plateaux = realloc(tab_plateaux, taille_collection * sizeof(*tab_plateaux));
      tab_plateaux[taille_collection-1] = calloc(registre[C], sizeof(*(tab_plateaux[taille_collection-1])));
      registre[B] = taille_collection-1;
      break;

    case 9 : /** Abandonment **/
      //free(tab_plateaux[registre[C]]);
      break;

    case 10: /** Output **/
      if(registre[C] >= 0 && registre[C] <= 255) {
        printf("\nValeur du registre C : %u\n",registre[C]);
        //console = registre[C];
      }
      break;

    case 11: /** Input **/
      printf("\nVeuillez entrer un nombre, ce dernier sera stocké dans le registre C : ");
      scanf("%d",&registre[C]);
      break;

    case 12: /** Load Program **/
   
      //free(tab_plateaux[0]);
      if(registre[B] != 0) {
        memcpy(tab_plateaux[0],tab_plateaux[registre[B]],sizeof(*tab_plateaux[registre[B]]));
        //tab_plateaux[0] = (unsigned int*)tab_plateaux[registre[B]];
      }
      //if(registre[C] < 256)
      i = registre[C]- 1; 
      break;

    case 13 : /** Orthography **/
      valeur = (int) (tab_plateaux[0][i] & 33554431);
      A = (int) (tab_plateaux[0][i] & (7<<25));
      A >>= 25;
      registre[A] = valeur;
      B = C = 0;
      break;

    default: return EXIT_FAILURE; break;

    }
  }




  printf("\nFIN");
  printf("\n\n");
  return EXIT_SUCCESS;

}
int main(int argc, char ** argv){
    init(argv[1]);
    runtime();

    // ***test reader***
    // char filename[50] = "./sandmark.umz";
    // fp = fopen(filename,"rb+");

    // for(int i = 0 ; i<3 ;i++){
    //     int res = reader();
    //     printf("%x\n ",res);
    // }  
    

    

  
}


