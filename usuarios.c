#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

typedef struct nodo{
	char cadena[10];
	char c;
	int n1;
	int n2;
	int etiqueta;
	struct nodo* siguiente;
}nodo;
typedef struct proceso{
	
	int id;
	int idUsuario;
	int grupo;
	int tiempo;
	char c[10];
	int num;
	struct region* regiones;
	struct proceso* siguiente;
}proceso;
typedef struct region{
	int id;
	int n1;
	int n2;
	int duracion;
	struct region* siguiente;
}region;
typedef struct grupo{
	int id;
	char nombre[10];
	struct grupo* siguiente;
}grupo;
typedef struct usuario{
	int id;
	char nombre[10];
	int grupo;
	struct usuario* siguiente;
}usuario;
 
//void liberar(struct nodo *actual);
struct nodo* buscarUltimo(struct nodo *primero);
void menu();
void GenerarLin(int lg);
void delay(int ms);
struct nodo* leer(struct nodo *primero,struct nodo *ultimo, int etiqueta);
struct nodo* insertarNodo(struct nodo *primero,struct nodo *ultimo,char *cad, char s, int numero1, int numero2, int etiqueta);
void desplegarLista(struct nodo *primero);
struct nodo* eliminarnodo( struct nodo *primero, int etiq);
struct nodo* Rr (struct nodo *primero);
struct nodo* plusUltra(struct nodo*primero);
int existFile(char* filename);

struct grupo* crear_Grupo(struct grupo *primero,struct grupo *ultimo);
struct grupo* insertarNodoGrupos(struct grupo *primero,struct grupo *ultimo,int id,char nombre[10]);
struct grupo* buscarUltimoG(struct grupo *primero);
void desplegarListaG(struct grupo *primero);
struct grupo* eliminarNodoG(struct grupo *primero, int etiq);

struct usuario* crear_Usuario(struct usuario *primero,struct usuario *ultimo, struct grupo *primeroG);
struct usuario* insertarNodoUsuarios(struct usuario *primero,struct usuario *ultimo,int id,char nombre[10],int grupo);
struct usuario* buscarUltimoU(struct usuario *primero);
void desplegarListaU(struct usuario *primero);
struct usuario* eliminarNodoU(struct usuario *primero, int etiq);

struct proceso* crear_Proceso(struct proceso *primero,struct proceso *ultimo,struct region *primeroR, struct region *ultimoR,struct usuario *primeroU);
struct proceso* insertarNodoP(struct proceso *primero,struct proceso *ultimo,int id,int idUsuario,int grupo,int tiempo,char c[10],int num,
struct region *primeroR);
struct proceso* buscarUltimoP(struct proceso *primero);
void desplegarListaP(struct proceso *primero);
struct proceso* eliminarNodoP(struct proceso *primero, int etiq);

struct region* regionCritica(struct region *primero,struct region *ultimo,int id,int num,int tiempo);
struct region* insertarNodoRegion(struct region *primero,struct region *ultimo,int n1,int n2,int duracion);
struct region* buscarUltimoR(struct region *primero);
void desplegarListaR(struct region *primero);
struct region* eliminarNodoR(struct region *primero, int etiq);

int estaNodoG(struct grupo *primero, int etiq);
int estaNodoU(struct usuario *primero, int etiq);
int estaNodoP(struct proceso *primero, int etiq);

int main(){
	nodo *primero = NULL,*ultimo = NULL;
	grupo *primeroG=NULL,*ultimoG=NULL;
	usuario *primeroU=NULL,*ultimoU=NULL;
	proceso *primeroP=NULL,*ultimoP=NULL;
	proceso *primeroP1=NULL,*ultimoP1=NULL;
	region  *primeroR=NULL, *ultimoR=NULL;
	int op, end=0, lg;
	int etiqueta=0;
	int etiq;
	do{
	
	menu();
	scanf("%d",&op);
	switch(op){
	case 1:
		printf("Introduzca cantidad de lineas a generar\n");
		scanf("%d",&lg);
		GenerarLin(lg);
		break;
	case 2:
		//primero=insertarNodo(primero,ultimo,cad, s, numero1, numero2, etiqueta);
		//ultimo=buscarUltimo(primero);
		
		primero=leer(primero,ultimo,etiqueta);
		printf("Lista leida\n");
		ultimo=buscarUltimo(primero);
		etiqueta=ultimo->etiqueta;
		break;
	case 3:
		
		printf("Nodo a eliminar : \n");
	    	scanf("%d",&etiq);
	   	primero = eliminarnodo(primero, etiq);
		break;
	case 4:
		desplegarLista(primero);
		break;
	case 5:
		primero = Rr(primero);
		break;
	case 6:
	
		primero = plusUltra(primero);
	
		break;
	case 7:
		primeroG=crear_Grupo(primeroG,ultimoG);
		ultimoG=buscarUltimoG(primeroG);
		break;
	case 8:
		desplegarListaG(primeroG);
		break;
	case 9:
		printf("Nodo a eliminar : \n");
	    	scanf("%d",&etiq);
		primeroG=eliminarNodoG(primeroG, etiq);
		break;
	case 10:
		primeroU=crear_Usuario(primeroU,ultimoU,primeroG);
		if(ultimoU!=NULL){
			ultimoU=buscarUltimoU(primeroU);
		}
		
		
		break;
	case 11:
		desplegarListaU(primeroU);
		break;
	case 12:
		printf("Nodo a eliminar : \n");
	    	scanf("%d",&etiq);
		primeroU=eliminarNodoU(primeroU, etiq);
		break;
	case 13:
		primeroP=crear_Proceso(primeroP,ultimoP,primeroR,ultimoR,primeroU);
		if(primeroP!=NULL){
		ultimoP=buscarUltimoP(primeroP);
		}
		break;
	case 14:
		desplegarListaP(primeroP);
		break;
	case 15:
		printf("Nodo a eliminar : \n");
	    	scanf("%d",&etiq);
		primeroP=eliminarNodoP(primeroP, etiq);
		break;
		
	case 20:
		end=1;
		break;
		
		
	default:
		printf("Caracter Invalido\n");
		printf("-----------------------------------------------\n");
		break;
	}
    }while(end!=1);

}//main
//region de proceso
struct proceso* crear_Proceso(struct proceso *primero,struct proceso *ultimo,struct region *primeroR, struct region *ultimoR, struct usuario *primeroU){
	int id,a,ret;
	
	int grupo;
	int t=0;
	char c[10],c2[10]="y";
	int num;
	int idUsuario;
	int ini,flecha=0;
	
	printf("ingresa el id de proceso");
	scanf("%d",&id);
	if(primero!=NULL){
		if(a=estaNodoP(primero, id)==1){
			perror("está repetido");
			return primero;
		}
		
	}
	//if(no usuario) marca error
	//se asigna solo printf("ingresa el grupo");
	if(primeroU!=NULL){
		while(flecha==0){
		desplegarListaU(primeroU);
		printf("igresa el id de usuario");
		scanf("%d",&idUsuario);
		if(a=estaNodoU(primeroU, idUsuario)==1){
			printf("esta");
			//primero=insertarNodoUsuarios(primero,ultimo,id,nombre,grupo);
			do{
			printf("ingresa el tiempo de ejecucion");
			scanf("%d",&t);
			printf("tiempo %d",t);
			}while(t<0);
			printf("tiene regiones criticas? y/n");
			scanf(" %s",&c);
			if(ret = strncmp(c, c2, 1)==0){
			printf("cuantas?");
			scanf("%d",&num);
			printf("tiempo %d",t);
			primeroR=regionCritica(primeroR,ultimoR,id,num,t);
			}
	primero=insertarNodoP(primero,ultimo,id,idUsuario,grupo,t,c,num,primeroR);
			
			return primero;
		}else{
			printf("elija un usuario existente\n");
		}
	}
	}
	if(primeroU==NULL){
		perror("no se ha creado el usuario ");
	}	
	
	//fflush(stdin);
}

struct proceso* insertarNodoP(struct proceso *primero,struct proceso *ultimo,int id,int idUsuario,int grupo,int tiempo,char c[10],int num,
struct region *primeroR){
	proceso* nuevo = (proceso*) malloc(sizeof(proceso));
	char cadena[10]="";
	int i=0;
	
	nuevo->id=id;
	nuevo->idUsuario=idUsuario;
	nuevo->grupo=grupo;
	nuevo->tiempo=tiempo;
	strcpy( cadena, c );
	strcpy( nuevo->c, cadena );
	nuevo->num=num;
	nuevo->regiones=primeroR;
	if(primero==NULL){
		primero = nuevo;
		primero->siguiente = primero;
		ultimo = primero;
	}else{
		ultimo->siguiente=nuevo;
		nuevo->siguiente=primero;
		ultimo=nuevo;
		
	}
	return primero;
}
int estaNodoP(struct proceso *primero, int etiq){
	proceso* actual = NULL;
	proceso* anterior = NULL;
	proceso* ultimo = NULL;
	//int f;
	ultimo=buscarUltimoP(primero);
	actual=primero;
	anterior=ultimo;
	//printf("Nodo a eliminar : \n");
	//scanf("%d",&f);
	
	if(actual != NULL){
		do{
			
			if(actual->id==etiq){
				return 1;	
			}
			anterior=actual;
			actual=actual->siguiente;
			
		}while(actual!= primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	
	}

	//desplegarLista(actual);
	return 0;
}
struct proceso* buscarUltimoP(struct proceso *primero){
	proceso* actual=primero->siguiente;
	proceso* anterior=primero;
		do{
			actual=actual->siguiente;
			anterior=anterior->siguiente;
		}while(actual!=primero);
		return anterior;
}
void desplegarListaP(struct proceso *primero){
	proceso* actual = NULL;
	actual = primero;
	if(primero != NULL){
		do{
			printf("id proceso %d usuario %d grupo %d regiones y/n:%c numero de regiones:%d ", 
			actual->id, actual->idUsuario,actual->grupo,actual->c,actual->num);
			desplegarListaR(actual->regiones);
			actual = actual->siguiente;
		}while(actual!=primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}
}
struct proceso* eliminarNodoP(struct proceso *primero, int etiq){
	proceso* actual = NULL;
	proceso* anterior = NULL;
	proceso* ultimo = NULL;
	//int f;
	ultimo=buscarUltimoP(primero);
	actual=primero;
	anterior=ultimo;
	//printf("Nodo a eliminar : \n");
	//scanf("%d",&f);
	
	if(actual != NULL){
		do{
			
			if(actual->id==etiq){
				if(actual==primero&&actual==ultimo){	
				printf("Nodo eliminado %d\n",actual->id);		
				free(actual);
				return NULL;
				}else if(actual==primero){
					printf("Nodo eliminado %d\n",actual->id);
					anterior=primero;
					primero = primero->siguiente;
					free(anterior);	
					ultimo->siguiente=primero;
				}else if(actual== ultimo){
					printf("Nodo eliminado %d\n",actual->id);
					free(actual);
					
					anterior->siguiente=ultimo->siguiente;
					ultimo=anterior;
				}else{	
					printf("Nodo eliminado %d\n",actual->id);
					anterior->siguiente = actual->siguiente;
					free(actual);
					
				}
			}
			anterior=actual;
			actual=actual->siguiente;
			
		}while(actual!= primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}

	//desplegarLista(actual);
	return primero;
}
// proceso

//inicia region de bloqueados

//termina region de bloqueados
//inicia region critica
struct region* regionCritica(struct region *primero,struct region *ultimo,int id,int num,int tiempo){
	int n1,n2 ,duracion;
	do{
		printf("tiempo %d",tiempo);
	printf("ingresa el tiempo en que inicia n region critica");
	scanf("%d",&n1);
	do{
	printf("duracion de la region critica");
	scanf("%d",&duracion);
	n2=n1+duracion;
	printf("%d %d",n2,tiempo);
	}while(n2>tiempo);
	
	primero=insertarNodoRegion(primero,ultimo,n1,n2,duracion);
	ultimo=buscarUltimoR(primero);
	num--;
	}while(num>0);
	return primero;
}
struct region* insertarNodoRegion(struct region *primero,struct region *ultimo,int n1,int n2,int duracion){
	region* nuevo = (region*) malloc(sizeof(region));
	
	int i=0;
	nuevo->n1=n1;
	nuevo->n2=n2;
	nuevo->duracion=duracion;
	if(primero==NULL){
		primero = nuevo;
		primero->siguiente = primero;
		ultimo = primero;
	}else{
		ultimo->siguiente=nuevo;
		nuevo->siguiente=primero;
		ultimo=nuevo;
		
	}
	return primero;
}
struct region* buscarUltimoR(struct region *primero){
	region* actual=primero->siguiente;
	region* anterior=primero;
		do{
			actual=actual->siguiente;
			anterior=anterior->siguiente;
		}while(actual!=primero);
		return anterior;
}
void desplegarListaR(struct region *primero){
	region* actual = NULL;
	actual = primero;
	if(primero != NULL){
		do{
			printf("inicia %d acaba %d duracion %d\n", actual->n1, actual->n2,actual-> duracion);
			actual = actual->siguiente;
		}while(actual!=primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}
}
struct region* eliminarNodoR(struct region *primero, int etiq){
	region* actual = NULL;
	region* anterior = NULL;
	region* ultimo = NULL;
	//int f;
	ultimo=buscarUltimoR(primero);
	actual=primero;
	anterior=ultimo;
	//printf("Nodo a eliminar : \n");
	//scanf("%d",&f);
	
	if(actual != NULL){
		do{
			
			if(actual->id==etiq){
				if(actual==primero&&actual==ultimo){	
				printf("Nodo eliminado %d\n",actual->id);		
				free(actual);
				return NULL;
				}else if(actual==primero){
					printf("Nodo eliminado %d\n",actual->id);
					anterior=primero;
					primero = primero->siguiente;
					free(anterior);	
					ultimo->siguiente=primero;
				}else if(actual== ultimo){
					printf("Nodo eliminado %d\n",actual->id);
					free(actual);
					
					anterior->siguiente=ultimo->siguiente;
					ultimo=anterior;
				}else{	
					printf("Nodo eliminado %d\n",actual->id);
					anterior->siguiente = actual->siguiente;
					free(actual);
					
				}
			}
			anterior=actual;
			actual=actual->siguiente;
			
		}while(actual!= primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}

	//desplegarLista(actual);
	return primero;
}
//termina region critica
//region de grupo
struct grupo* crear_Grupo(struct grupo *primero,struct grupo *ultimo){
	
	int id;
	char nombre[10]="";
	int a;
	printf("ingresa el id de grupo\n");
	scanf("%d",&id);
	if(primero!=NULL){
		if(a=estaNodoG(primero, id)==1){
			perror("está repetido");
			return primero;
		}
		
	}
		
	
	printf("ingresa el nombre\n");
	scanf("%s",&nombre);
	primero=insertarNodoGrupos(primero,ultimo,id,nombre);
	return primero;
}
int estaNodoG(struct grupo *primero, int etiq){
	grupo* actual = NULL;
	grupo* anterior = NULL;
	grupo* ultimo = NULL;
	//int f;
	ultimo=buscarUltimoG(primero);
	actual=primero;
	anterior=ultimo;
	//printf("Nodo a eliminar : \n");
	//scanf("%d",&f);
	
	if(actual != NULL){
		do{
			
			if(actual->id==etiq){
				return 1;	
			}
			anterior=actual;
			actual=actual->siguiente;
			
		}while(actual!= primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	
	}

	//desplegarLista(actual);
	return 0;
}
struct grupo* insertarNodoGrupos(struct grupo *primero,struct grupo *ultimo,int id,char nombre[10]){
	grupo* nuevo = (grupo*) malloc(sizeof(grupo));
	char cadena[10]="";
	int i=0;
	strcpy( cadena, nombre );
	strcpy( nuevo->nombre, cadena );
	nuevo->id=id;
	if(primero==NULL){
		primero = nuevo;
		primero->siguiente = primero;
		ultimo = primero;
	}else{
		ultimo->siguiente=nuevo;
		nuevo->siguiente=primero;
		ultimo=nuevo;
		
	}
	return primero;
}
struct grupo* buscarUltimoG(struct grupo *primero){
	grupo* actual=primero->siguiente;
	grupo* anterior=primero;
		do{
			actual=actual->siguiente;
			anterior=anterior->siguiente;
		}while(actual!=primero);
		return anterior;
}
void desplegarListaG(struct grupo *primero){
	grupo* actual = NULL;
	actual = primero;
	if(primero != NULL){
		do{
			printf("%d %s\n", actual->id, actual->nombre);
			actual = actual->siguiente;
		}while(actual!=primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}
}
struct grupo* eliminarNodoG(struct grupo *primero, int etiq){
	grupo* actual = NULL;
	grupo* anterior = NULL;
	grupo* ultimo = NULL;
	//int f;
	ultimo=buscarUltimoG(primero);
	actual=primero;
	anterior=ultimo;
	//printf("Nodo a eliminar : \n");
	//scanf("%d",&f);
	
	if(actual != NULL){
		do{
			
			if(actual->id==etiq){
				if(actual==primero&&actual==ultimo){	
				printf("Nodo eliminado %d\n",actual->id);		
				free(actual);
				return NULL;
				}else if(actual==primero){
					printf("Nodo eliminado %d\n",actual->id);
					anterior=primero;
					primero = primero->siguiente;
					free(anterior);	
					ultimo->siguiente=primero;
				}else if(actual== ultimo){
					printf("Nodo eliminado %d\n",actual->id);
					free(actual);
					
					anterior->siguiente=ultimo->siguiente;
					ultimo=anterior;
				}else{	
					printf("Nodo eliminado %d\n",actual->id);
					anterior->siguiente = actual->siguiente;
					free(actual);
					
				}
			}
			anterior=actual;
			actual=actual->siguiente;
			
		}while(actual!= primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}

	//desplegarLista(actual);
	return primero;
}
//termina region de grupo

//region usuario
struct usuario* crear_Usuario(struct usuario *primero,struct usuario *ultimo,struct grupo *primeroG){ //cesar id grupo 
	int id,grupo,a,flecha=0;
	char nombre[10];
	usuario* nuevo = (usuario*) malloc(sizeof(usuario));
	printf("ingresa el id");
	scanf("%d",&id);
	if(primero!=NULL){
		if(a=estaNodoU(primero, id)==1){
			perror("está repetido");
			return primero;
		}
		
	}
	
	printf("ingresa el nombre");
	scanf("%s",&nombre);
	
	
	
	if(primeroG!=NULL){
		while(flecha==0){
		desplegarListaG(primeroG);
		printf("ingresa el grupo");
		scanf("%d",&grupo);
		if(a=estaNodoG(primeroG, grupo)==1){
			printf("esta");
			primero=insertarNodoUsuarios(primero,ultimo,id,nombre,grupo);
			return primero;
		}else{
			printf("elija un grupo existente\n");
		}
	}
	}
	if(primeroG==NULL){
		perror("no se ha creado grupo ");
	}	
	//if(no grupo )marca error
	
}
int estaNodoU(struct usuario *primero, int etiq){
	usuario* actual = NULL;
	usuario* anterior = NULL;
	usuario* ultimo = NULL;
	//int f;
	ultimo=buscarUltimoU(primero);
	actual=primero;
	anterior=ultimo;
	//printf("Nodo a eliminar : \n");
	//scanf("%d",&f);
	
	if(actual != NULL){
		do{
			
			if(actual->id==etiq){
				return 1;	
			}
			anterior=actual;
			actual=actual->siguiente;
			
		}while(actual!= primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
		
	}

	//desplegarLista(actual);
	return 0;
}
struct usuario* insertarNodoUsuarios(struct usuario *primero,struct usuario *ultimo,int id,char nombre[10],int grupo){
	usuario* nuevo = (usuario*) malloc(sizeof(usuario));
	char cadena[10]="";
	int i=0;
	strcpy( cadena, nombre );
	strcpy( nuevo->nombre, cadena );
	nuevo->id=id;
	nuevo->grupo=grupo;
	if(primero==NULL){
		primero = nuevo;
		primero->siguiente = primero;
		ultimo = primero;
	}else{
		ultimo->siguiente=nuevo;
		nuevo->siguiente=primero;
		ultimo=nuevo;
		
	}
	return primero;
}
struct usuario* buscarUltimoU(struct usuario *primero){
	usuario* actual=primero->siguiente;
	usuario* anterior=primero;
		do{
			actual=actual->siguiente;
			anterior=anterior->siguiente;
		}while(actual!=primero);
		return anterior;
}
void desplegarListaU(struct usuario *primero){
	usuario* actual = NULL;
	actual = primero;
	if(primero != NULL){
		do{
			printf("%d %s %d\n", actual->id, actual->nombre,actual->grupo);
			actual = actual->siguiente;
		}while(actual!=primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}
}
struct usuario* eliminarNodoU(struct usuario *primero, int etiq){
	usuario* actual = NULL;
	usuario* anterior = NULL;
	usuario* ultimo = NULL;
	//int f;
	ultimo=buscarUltimoU(primero);
	actual=primero;
	anterior=ultimo;
	//printf("Nodo a eliminar : \n");
	//scanf("%d",&f);
	
	if(actual != NULL){
		do{
			
			if(actual->id==etiq){
				if(actual==primero&&actual==ultimo){	
				printf("Nodo eliminado %d\n",actual->id);		
				free(actual);
				return NULL;
				}else if(actual==primero){
					printf("Nodo eliminado %d\n",actual->id);
					anterior=primero;
					primero = primero->siguiente;
					free(anterior);	
					ultimo->siguiente=primero;
				}else if(actual== ultimo){
					printf("Nodo eliminado %d\n",actual->id);
					free(actual);
					
					anterior->siguiente=ultimo->siguiente;
					ultimo=anterior;
				}else{	
					printf("Nodo eliminado %d\n",actual->id);
					anterior->siguiente = actual->siguiente;
					free(actual);
					
				}
			}
			anterior=actual;
			actual=actual->siguiente;
			
		}while(actual!= primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}

	//desplegarLista(actual);
	return primero;
}
//termina la region usuario

void permisos(int a,int b,int c){//user group others
	
}

void eliminar_Usuario(){

}



//FUNCIONES

void menu(){
	printf("-Elija accion a realizar-\n");
	printf("1. Generar Lineas\n");
	printf("2. Generar lista\n");
	printf("3. Eliminar nodo\n");
	printf("4. Mostrar lista\n");
	printf("5. Round Robin\n");
	printf("6. Nuestro Querubin <3\n");
	printf("7. Crear grupo\n");
	printf("8. Mostrar grupo\n");
	printf("9. Eliminar grupo\n");
	printf("10. Crear usuario\n");
	printf("11. Mostrar usuarios\n");
	printf("12. Eliminar usuario\n");
	printf("13. Crear proceso\n");
	printf("14. Mostrar procesos\n");
	printf("15. Eliminar proceso\n");
	printf("20. Salir\n");
}

void GenerarLin(int lg){
	char Cadena[10]="cadena";
	char caracter;
	int entero1;
	int entero2;
	int i;
	
	srand(time(NULL));
	
	FILE * flujo = fopen("Archivo.txt", "w");
	
	for(i=0;i<lg;i++){
		
		caracter =(rand() % 127);
		entero1 = 1 + rand() % ((100+1)-1);
		entero2 = 1 + rand() % ((100+1)-1);
		
		fprintf(flujo,"%s %c %d %d", Cadena, caracter, entero1, entero2);
	}
	fclose(flujo);
}

void delay(int ms){
	clock_t timeDelay = ms + clock();
	while(timeDelay>clock());
}

nodo* leer(struct nodo *primero,struct nodo *ultimo, int etiqueta){
	time_t t;
	int x =  rand() %4;
	int y =  rand() %5;
	int numero1=0,numero2=0;
	char cadena[10], s, cad[10];
	int lg;
	
	if(existFile("Archivo.txt")==0){
		perror("Error en la apertura del archivo");
		printf("Introduzca cantidad de lineas a generar\n");
		scanf("%d",&lg);
		GenerarLin(lg);
	}
	FILE * flujo = fopen("Archivo.txt", "r");
	srand((unsigned) time(&t));
	while (feof(flujo) == 0){
		//printf("%d",y);
			delay(y*100);
			fscanf(flujo, "%s %c %d %d", cadena, &s, &numero1, &numero2);
			etiqueta++;
			printf("%s %c %d %d %d\n", cadena, s, numero1, numero2,etiqueta);
			primero=insertarNodo(primero,ultimo,cadena, s, numero1, numero2, etiqueta);
			ultimo=buscarUltimo(primero);
			//primero = insertarNodo(primero, cadena, s, numero1, numero2, z);
			fflush( stdin );
	}
	
	fclose(flujo);
	printf("\n\nSe ha leido el archivo correctamente ..");
	return primero;
}
int existFile(char* filename) {
    	FILE* f = NULL;
    	f = fopen(filename,"r");
    	if (f == NULL && errno == ENOENT) 
    		return 0;
    	else {
    		fclose(f);
    		return 1;
    	}
    }
struct nodo* insertarNodo(struct nodo *primero,struct nodo *ultimo,char *cad, char s, int numero1, int numero2, int etiqueta){
	nodo* nuevo = (nodo*) malloc(sizeof(nodo));
	char cadena[10]="";
	int i=0;
	nuevo->etiqueta=etiqueta;
	strcpy( cadena, cad );
	strcpy( nuevo->cadena, cadena );
	nuevo->c=s;
	nuevo->n1=numero1;
	nuevo->n2=numero2;
//	nuevo->etiqueta=primero->etiqueta;
//	printf("%s %c %d %d", nuevo->cadena, nuevo->c, nuevo->n1, nuevo->n2);
	if(primero==NULL){
		primero = nuevo;
		primero->siguiente = primero;
		ultimo = primero;
	}else{
		ultimo->siguiente=nuevo;
		nuevo->siguiente=primero;
		ultimo=nuevo;
		
	}
	return primero;
}
struct nodo* buscarUltimo(struct nodo *primero){
	nodo* actual=primero->siguiente;
	nodo* anterior=primero;
		do{
			actual=actual->siguiente;
			anterior=anterior->siguiente;
		}while(actual!=primero);
		return anterior;
}
void desplegarLista(struct nodo *primero){
	nodo* actual = NULL;
	actual = primero;
	if(primero != NULL){
		do{
			printf("%s %c %d %d %d\n", actual->cadena, actual->c, actual->n1, actual->n2, actual->etiqueta);
			actual = actual->siguiente;
		}while(actual!=primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}
}
nodo* eliminarnodo(struct nodo *primero, int etiq){
	nodo* actual = NULL;
	nodo* anterior = NULL;
	nodo* ultimo = NULL;
	//int f;
	ultimo=buscarUltimo(primero);
	actual=primero;
	anterior=ultimo;
	//printf("Nodo a eliminar : \n");
	//scanf("%d",&f);
	
	if(actual != NULL){
		do{
			
			if(actual->etiqueta==etiq){
				if(actual==primero&&actual==ultimo){	
				printf("Nodo eliminado %d\n",actual->etiqueta);		
				free(actual);
				return NULL;
				}else if(actual==primero){
					printf("Nodo eliminado %d\n",actual->etiqueta);
					anterior=primero;
					primero = primero->siguiente;
					free(anterior);	
					ultimo->siguiente=primero;
				}else if(actual== ultimo){
					printf("Nodo eliminado %d\n",actual->etiqueta);
					free(actual);
					
					anterior->siguiente=ultimo->siguiente;
					ultimo=anterior;
				}else{	
					printf("Nodo eliminado %d\n",actual->etiqueta);
					anterior->siguiente = actual->siguiente;
					free(actual);
					
				}
			}
			anterior=actual;
			actual=actual->siguiente;
			
		}while(actual!= primero);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}

	//desplegarLista(actual);
	return primero;
}

struct nodo* Rr (struct nodo *primero){
	nodo* actual = (nodo*)malloc(sizeof(nodo));
	nodo* ultimo = (nodo*)malloc(sizeof(nodo));
	actual = primero;
	int y =  5;//variable de tiempo
	
	if(actual != NULL){
		do{
			ultimo=buscarUltimo(primero);
			if(actual->n1 > 5){
			//delay(1000);//tiempo que se tarda
			sleep(1);
			printf("n1 %d etiqueta %d \n",actual->n1,actual->etiqueta);
			actual->n1 = actual->n1 - 5;
			}else{
			if(primero==ultimo){
				primero=eliminarnodo(primero, actual->etiqueta);
				return NULL;
			}else {
				primero=eliminarnodo(primero, actual->etiqueta);
				}
			
			}
		actual = actual->siguiente;
		
//		desplegarLista(primero);	
		}while(actual!=NULL);
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}
	printf("\n");
	return actual;
}

struct nodo* plusUltra (struct nodo *primero){
	nodo* actual = (nodo*)malloc(sizeof(nodo));
	nodo* ultimo = (nodo*)malloc(sizeof(nodo));
	nodo* anterior = (nodo*)malloc(sizeof(nodo));
	
	int y =  5; //variable de tiempo
	
	
	
	
	int temp;
	nodo* numerin = (nodo*)malloc(sizeof(nodo)); //Numerin es el numero(lmao jejep owo) que tiene la direccion de el tiempo mas pequeño okay?
	
	
	if(primero != NULL){
		do{
			temp=10000000;
			ultimo=buscarUltimo(primero);
			actual=primero;
			anterior=ultimo;
		
			do{
				if(actual->n1<temp) //Holis
				{
				temp=actual->n1;
				numerin=actual;
				printf("%d\n",numerin->n1);
				}
		
			
				anterior=actual;
				actual=actual->siguiente;
			
			}while(actual!= primero);
			//lo que prosigue: se va a reducir el numero de tiempo en el nodo del cual tenemos la direccion guardada en numerin.
			
			
			do{
				
				if(numerin->n1 > 5){
				delay(y*1000);//tiempo
				printf("n1 %d etiqueta %d \n",numerin->n1,numerin->etiqueta);
				numerin->n1 = numerin->n1 - 5;
				}else{
				if(primero==ultimo){
				
					primero=eliminarnodo(primero, numerin->etiqueta);
					actual=NULL;
					numerin=NULL;
				}else {
					printf("n1 %d etiqueta %d \n",numerin->n1,numerin->etiqueta);
					primero=eliminarnodo(primero, numerin->etiqueta);
					numerin=NULL;
					}		
				}
			
			//		desplegarLista(primero);	
			}while(numerin!=NULL);//se decrementa y elimina
		printf("salio\n");
		}while(actual!=NULL);//sale hasta que la lista está vacia
	}else{
		printf("\n La lista se encuentra vacia \n\n");
	}
	
	
	
	printf("\n");
	return primero;
}
//bloqueados
//practicas programas presentaciones proyecto investigación filosofos,lector escritor, productor consumidor .pptx y .c y .txt manual
//leer quantum
//(procesos)id de proceso id de usuario 
//tiempo total del proceso
//tiene regiones criticas?
//cuantas?
//tiempo inicial
//duracion
//que no se encimen que no se pase tiempo total del proceso
//turno 0 
//tiempo 0
//region critica puede iniciar en el tiempo 0
//no id ni usuaro ni grupos repetidos
//usuario id + nombre del usuario
//grupo id de grupo y nombre del grupo
//elimino usuario elimino procesos
//elimino grupo elimino usuario y procesos
//eliminar procesos en tabla de control y en listas
//ejecuta todo y por partes
//letrero ejecutando proceso
//intentando entrar a region critica
//entrando a region critica
//proceso bloqueado
//saliendo de region critica
//terminando proceso x
//   dando un proceso
//mostrar variable turno
//martes 14 entrega de proyectos y examen


