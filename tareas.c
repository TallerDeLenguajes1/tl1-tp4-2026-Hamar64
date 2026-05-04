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
void buscarTareas(Nodo ** L, Nodo ** L2);
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
            case 4: buscarTareas(&LP, &LR);
            break;
            case 5: printf("Menu cerrado.\n");
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
    if(L == NULL){
        printf("\nNo hay ninguna tarea pendiente. Buen trabajo.\n");
    }
    
    aux = L2;
    printf("\n\nTareas Realizadas:\n\n");
    while(aux != NULL){
        printf("\nTarea %d: \n", aux->T.TareaID);
        printf("\tDescripcion: %s\n", aux->T.Descripcion);
        printf("\tDuracion: %d\n", aux->T.Duracion);
        aux = aux->Siguiente;
    }
    if(L2 == NULL){
        printf("\nNo hay ninguna tarea realizada. A trabajar!.\n");
    }
}

void completarTareas(Nodo ** L, Nodo ** L2){
    Nodo * aux, * aux2;
    int iter, id, b = 0;
    aux = *L;
    printf("\n\nTareas Pendientes:\n\n");
    while(aux != NULL){
        printf("\nTarea %d: \n", aux->T.TareaID);
        printf("\tDescripcion: %s\n", aux->T.Descripcion);
        printf("\tDuracion: %d\n", aux->T.Duracion);
        aux = aux->Siguiente;
    }

    do{
        printf("Ingrese la id de la tarea a marcar como realizada:\n");
        scanf("%d", &id);
        aux = *L;
        if(*L != NULL){
            do{
                b = 0;
                if((*L)->T.TareaID == id){
                    *L = (*L)->Siguiente;
                    aux2 = *L2;
                    *L2 = aux;
                    aux->Siguiente = aux2;
                    b = 1;
                } else if(aux->Siguiente != NULL && aux->Siguiente->T.TareaID == id){
                    aux2 = *L2;
                    *L2 = aux->Siguiente;
                    aux->Siguiente = aux->Siguiente->Siguiente;
                    (*L2)->Siguiente = aux2;
                    b = 1;
                } else if(aux->Siguiente != NULL){
                    aux = aux->Siguiente;
                }
            } while(aux->Siguiente != NULL  && aux->Siguiente->T.TareaID != id && b==0);
            if(b == 0){
                printf("La id no se encontraba en la lista.\n");
            }
        } else {
            printf("La lista de tareas pendientes está vacía.\n");
        }
        printf("Escriba 1 si desea ingresar otro nodo (cualquier otro numero cerrara la interfaz)\n");
        scanf("%d", &iter);
    } while(iter == 1);
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

void buscarTareas(Nodo ** L, Nodo ** L2){
    int op, id, b = 0;
    char Buff[30];
    Nodo * aux;
    
    do{
        printf("\n\nIndique si desea buscar la tarea:\n1. Por ID\n2. Por palabra clave\n3. Salir de la interfaz\n");
        scanf("%d", &op);
        b = 0;
        if(op == 1){
            do{
                printf("Ingrese la ID de la tarea a buscar:\n");
                scanf("%d", &id);
            }while(id<1000);
            aux = *L;
            while(aux != NULL){
                if(aux->T.TareaID == id){
                    printf("Tarea de id %d:\n", id);
                    printf("\tDescripcion: %s\n", aux->T.Descripcion);
                    printf("\tDuracion: %d\n", aux->T.Duracion);
                    printf("\tSe trata de una tarea pendiente\n");
                    b = 1;
                    aux = NULL;
                } else {
                    aux = aux->Siguiente;
                }
            }
            if(b == 0){
                aux = *L2;
                while(aux != NULL){
                    if(aux->T.TareaID == id){
                        printf("Tarea de id %d:\n", id);
                        printf("\tDescripcion: %s\n", aux->T.Descripcion);
                        printf("\tDuracion: %d\n", aux->T.Duracion);
                        printf("\tSe trata de una tarea realizada\n");
                        b = 1;
                        aux = NULL;
                    } else {
                        aux = aux->Siguiente;
                    }
                }
            }
            if(b == 0){
                printf("No se encontro la id de la tarea.\n");
            }
        } else if(op == 2){
            printf("Ingrese una palabra clave de la descripcion de la tarea a buscar:\n");
            scanf("%s", Buff);
            aux = *L;
            while(aux != NULL){
                if(strstr(aux->T.Descripcion, Buff) != NULL){
                    printf("Tarea de id %d:\n", id);
                    printf("\tDescripcion: %s\n", aux->T.Descripcion);
                    printf("\tDuracion: %d\n", aux->T.Duracion);
                    printf("\tSe trata de una tarea pendiente\n");
                    b = 1;
                    aux = NULL;
                } else {
                    aux = aux->Siguiente;
                }
            }
            if(b == 0){
                aux = *L2;
                while(aux != NULL){
                    if(strstr(aux->T.Descripcion, Buff) != NULL){
                        printf("Tarea de id %d:\n", id);
                        printf("\tDescripcion: %s\n", aux->T.Descripcion);
                        printf("\tDuracion: %d\n", aux->T.Duracion);
                        printf("\tSe trata de una tarea realizada\n");
                        b = 1;
                        aux = NULL;
                    } else {
                        aux = aux->Siguiente;
                    }
                }
            }
            if(b == 0){
                printf("No se encontro ninguna tarea con la palabra clave");
            }
        }
    } while(op != 3);
}