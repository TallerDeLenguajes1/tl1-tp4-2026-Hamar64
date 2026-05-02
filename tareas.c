#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Tarea{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
} Tarea;
typedef struct Nodo{
Tarea T;
struct Nodo *Siguiente;
} Nodo;

void cargarTarea(Nodo ** L, int * c);
void insertarTarea(Nodo ** L, Nodo * N);
void completarTareas(Nodo ** L, Nodo ** L2);
void listarTareas(Nodo * L, Nodo * L2);
//void buscarTareas(Nodo ** L, Nodo ** L2);
void eliminarLista(Nodo ** L);
int listaVacia(Nodo ** L);

int main(void){
    
    srand(time(NULL));
    Tarea T;
    int c = 1000;
    int * pc = &c;

    Nodo * LP, * LR;
    LP = NULL;
    LR = NULL;
    int op;
    do{
        printf("Indice la operacion a realizar:\n 1. Cargar tareas pendientes\n 2. Marcar tareas como realizadas\n 3. Listar todas las tareas\n 4. Buscar tareas\n 5. Cerrar interfaz\n");
        scanf("%d", &op);
        switch(op){
            case 1: cargarTarea(&LP, pc);
            break;
            case 2: completarTareas(&LP, &LR);
            break;
            case 3: listarTareas(LP, LR);
            break;
            //case 4: buscarTareas(&LP, &LR);
            //break;
            case 5: printf("Menú cerrado.\n");
            break;
            default: printf("\n\nIngrese un numero valido.\n\n");
            break;
        }
    } while (op!=5);



    eliminarLista(&LP);
    eliminarLista(&LR);

    return 0;
}

void cargarTarea(Nodo ** L, int * p){
    int tama, iter;                       /*Comienzo a agregar nodo*/
    Tarea T;
    char Buff[50];
    Nodo * aux;
    do{
        printf("Ingrese la descripcion de la tarea:\n");
        scanf("%s", Buff);
        tama = strlen(Buff);
        T.Descripcion = (char *) malloc(tama * sizeof(char)+1);
        strcpy(T.Descripcion, Buff);
        T.TareaID = *p;
        *p = *p + 1;
        T.Duracion = 10 + rand()%91;
        aux = (Nodo *) malloc(sizeof(Nodo));
        aux->T = T;
        aux->Siguiente = *L;
        *L = aux;                       /*Termino de agregar nodo*/
        printf("Escriba 1 si desea ingresar otro nodo (cualquier otro numero cerrara la interfaz)\n");
        scanf("%d", &iter);
    } while (iter == 1);
}

void listarTareas(Nodo * L, Nodo * L2){
    Nodo * aux;
    aux = L;
    printf("\n\nTareas Pendientes:\n\n");
    while(aux != NULL){
        printf("\nTarea %d: \n", aux->T.TareaID);
        printf("\tDescripcion: %s\n", aux->T.Descripcion);
        printf("\tDuracion: %d\n", aux->T.Duracion);
        aux = aux->Siguiente;
    }
    
    aux = L2;
    printf("\n\nTareas Realizadas:\n\n");
    while(aux != NULL){
        printf("\nTarea %d: \n", aux->T.TareaID);
        printf("\tDescripcion: %s\n", aux->T.Descripcion);
        printf("\tDuracion: %d\n", aux->T.Duracion);
        aux = aux->Siguiente;
    }
}

void completarTareas(Nodo ** L, Nodo ** L2){
    
}

void eliminarLista(Nodo ** L){
    Nodo * aux;
    while(listaVacia(L) == 0){
        aux = *L;
        *L = (*L)->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}

int listaVacia(Nodo ** L){
    if(*L == NULL){
        return 1;
    } else {
        return 0;
    }
}