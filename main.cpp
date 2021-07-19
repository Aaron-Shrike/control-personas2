#include "basicas.cpp"
#define MAXDNI 9
#define MAXSEXO 2
#define MAXREGION 3

//ESTRUCTURAS
struct Persona{
	char dni[MAXDNI];
	char nombre[LIM];
	int edad;
	int sexo; //campo categorizado
	int region; //campo categorizado
	int nacimiento;
	int vencimiento;
	char padre[LIM];
	char madre[LIM];
   Fecha fA;
};

struct NodoPersona{
	Persona P;
	NodoPersona *Sgte;
};

struct ListaPersonas{
	NodoPersona *Cab;
	int N;
};

//TABLAS
char TSexo[MAXSEXO][LIM]={"Masculino","Femenino"};
char TRegion[MAXREGION][LIM]={"Norte","Centro","Sur"};

//OPERACIONES BASICAS DE PERSONA
void iniciaPersona(Persona &P){
	P.dni[0]=NULL;
	P.nombre[0]=NULL;
	P.edad=0;
	P.sexo=0;
	P.region=0;
	P.nacimiento=0;
	P.vencimiento=0;
	P.padre[0]=NULL;
	P.madre[0]=NULL;
   iniciaFecha(P.fA);
}

//OPERACIONES BASICAS DE LISTAPERSONAS
void inicia(ListaPersonas &LP){
	LP.Cab=NULL;
	LP.N=0;
}

void leePersona(Persona &P,ListaPersonas &LP){
	int flag;
   NodoPersona *Aux;
	do{
		do{
			printf("\n Ingrese DNI(8 digitos): ");
			fflush(stdin);
			gets(P.dni);
		}while(!(strlen(P.dni)==MAXDNI-1));
		flag=0;
		Aux=LP.Cab;
		while(Aux!=NULL){
			if(stricmp(P.dni,Aux->P.dni)==0)
				flag=1;
			Aux=Aux->Sgte;
		}
		if(flag==1)
			printf("\n El DNI de repite...");
	}while(!(flag==0));
	printf(" Ingrese nombre completo: ");
	fflush(stdin);
	gets(P.nombre);
	P.edad=leeEntero(" Ingrese edad[0-100]: ",0,100);
	P.sexo=validaTabla("\n Ingrese sexo: ",TSexo,MAXSEXO);
	P.region=validaTabla("\n Ingrese region: ",TRegion,MAXREGION);
	P.nacimiento=leeEntero(" Ingrese anio de nacimiento[1918-2018]: ",1918,2018);
	P.vencimiento=leeEntero(" Ingrese anio de vencimiento del DNI[2018-2026]: ",2018,2026);
	printf(" Ingrese nombre del Padre: ");
	fflush(stdin);
	gets(P.padre);
	printf(" Ingrese nombre de la Madre: ");
	fflush(stdin);
	gets(P.madre);
   leeFecha("\nIngrese fecha de atencion: ",P.fA);
}

void mostrarPersona(Persona &P){
	printf("\n\n DNI: %s",P.dni);
	printf("\n Nombre: %s",P.nombre);
	printf("\n Edad: %d",P.edad);
	printf("\n Sexo: %s",TSexo[P.sexo-1]);
	printf("\n Region: %s",TRegion[P.region-1]);
	printf("\n Nacimiento: %d",P.nacimiento);
	printf("\n Vencimiento: %d",P.vencimiento);
	printf("\n Padre: %s",P.padre);
	printf("\n Madre: %s",P.madre);
   mostrarFecha("\n Fecha de atencion: ",P.fA);
}

void inserta(ListaPersonas &LP,Persona &P,NodoPersona *&Aux){
	NodoPersona *A;
	A=new NodoPersona;
	A->P=P;
	
	if(Aux==NULL){
		A->Sgte=LP.Cab;
		LP.Cab=A;
	}
	else{
		A->Sgte=Aux->Sgte;
		Aux->Sgte=A;
	}

	LP.N++;
	Aux=A;
}

void lee(ListaPersonas &LP)
{
	Persona P;
	NodoPersona *Aux;
	Aux=LP.Cab;
	do
	{
		iniciaPersona(P);
		leePersona(P,LP);
		inserta(LP,P,Aux);
	}while(continuar("\nDesea Continuar(S/N): ")=='S');
}

void mostrar(ListaPersonas &LP)
{
	NodoPersona *Aux=LP.Cab;
	if(LP.N>0)
	{
		while(Aux!=NULL)
		{
			mostrarPersona(Aux->P);
			Aux=Aux->Sgte;
		}
	}
	else
		printf("\nNo Hay Datos...");
	getch();
}

void liberar(ListaPersonas &LP)
{
	NodoPersona *Aux=LP.Cab;
	while(Aux!=NULL)
	{
		LP.Cab=Aux->Sgte;
		delete Aux;
		Aux=LP.Cab;
	}
}

//REPORTES
void reporte01(ListaPersonas &LP){
	NodoPersona *Aux=LP.Cab;
	char nombp[LIM],nombm[LIM];
	int flag=0;
	nombp[0]=NULL;
	nombm[0]=NULL;
	if(LP.N>0){
		printf(" Ingrese nombre del padre: ");
		fflush(stdin);
		gets(nombp);
		printf(" Ingrese nombre de la madre: ");
		fflush(stdin);
		gets(nombm);
		while(Aux!=NULL){
			if(stricmp(nombp,Aux->P.padre)==0 && stricmp(nombm,Aux->P.madre)==0){
				mostrarPersona(Aux->P);
				flag=1;
			}
			Aux=Aux->Sgte;
		}
		if(flag==0)
			printf("\n No se encontraron hijos...");
	}
	else
		printf("\n No hay datos...");
	getch();
}

void reporte02(ListaPersonas &LP){
	NodoPersona *Aux=LP.Cab;
	int flag=0;
	if(LP.N>0){
		while(Aux!=NULL){
			if(Aux->P.vencimiento==2018){
				flag=1;
				mostrarPersona(Aux->P);
			}
			Aux=Aux->Sgte;
		}
		if(flag==0)
			printf("\n No hay personas con esta fecha de vencimiento");
	}
	else
		printf("\n No hay datos...");
	getch();
}

void reporte03(ListaPersonas &LP){
	NodoPersona *Aux=LP.Cab;
	int contsexo[MAXSEXO],suma[MAXSEXO];
	float prom[MAXSEXO];
	iniciaVE(contsexo,MAXSEXO);
	iniciaVE(suma,MAXSEXO);
	iniciaVR(prom,MAXSEXO);
	if(LP.N){
		while(Aux!=NULL){
			contsexo[Aux->P.sexo-1]++;
			suma[Aux->P.sexo-1]+=Aux->P.edad;
			Aux=Aux->Sgte;
		}
		for(int j=0;j<MAXSEXO;j++){
			printf("\n\n%s :",TSexo[j]);
			if(contsexo[j]>0){
				prom[j]=(float)suma[j]/contsexo[j];
				printf("\n Promedio de edad %s: %.2f",TSexo[j],prom[j]);
			}
			else
				printf("\n No hay personas por ese sexo");
		}
	}
	else
		printf("\n No hay datos...");
	getch();
}

void reporte04(ListaPersonas &LP){
	NodoPersona *Aux=LP.Cab;
	int contregion[MAXREGION];
	iniciaVE(contregion,MAXREGION);
	if(LP.N>0){
		while(Aux!=NULL){
			contregion[Aux->P.region-1]++;
			Aux=Aux->Sgte;
		}
		for(int j=0;j<MAXREGION;j++)
			printf("\n\n %s: %d",TRegion[j],contregion[j]);
	}
	else
		printf("\n No hay datos...");
	getch();
}

void reporte05(ListaPersonas &LP){
	NodoPersona *Aux1=LP.Cab;
	NodoPersona *Aux2;
	Persona P;
	int aux,flag=0;
	if(LP.N>0){
		aux=validaTabla("\n Ingrese region a buscar:",TRegion,MAXREGION);
		while(Aux1->Sgte!=NULL)	{
			Aux2=Aux1->Sgte;
			while(Aux2!=NULL){
				if(stricmp(Aux1->P.nombre,Aux2->P.nombre)>0){
					P=Aux1->P;
					Aux1->P=Aux2->P;
					Aux2->P=P;
				}
				Aux2=Aux2->Sgte;
			}
			Aux1=Aux1->Sgte;
		}
		printf("\n PERSONAS ORDENADAS POR LA REGION %s",TRegion[aux-1]);
		NodoPersona *Aux=LP.Cab;
		while(Aux!=NULL){
			if(Aux->P.region==aux){
				mostrarPersona(Aux->P);
				flag=1;
			}
			Aux=Aux->Sgte;
		}
		if(flag==0)
			printf("\n No hay personas registradas en esta region.");
	}
	else
		printf("\n No hay datos...");
	getch();
}

void menu(ListaPersonas &LP){
	int opc;
	do{
		system("cls");
		printf("\tMENU");
		printf("\n 1.- Registrar");
		printf("\n 2.- Mostrar");
		printf("\n 3.- Hijos registrados, por nombre de Padre y Madre");
		printf("\n 4.- Vencimiento 2018");
		printf("\n 5.- Promedio de edad por sexo");
		printf("\n 6.- Numero de personas por region");
		printf("\n 7.- Persona ordenada por nombre, de acuerdo a la region");
		printf("\n 8.- Salir");
		opc=leeEntero("\n Ingrese opcion: ",1,8);
		switch(opc){
			case 1: lee(LP);
					break;
			case 2: mostrar(LP);
					break;
			case 3: reporte01(LP);
					break;
			case 4: reporte02(LP);
					break;
			case 5: reporte03(LP);
					break;
			case 6: reporte04(LP);
					break;
			case 7: reporte05(LP);
					break;
			case 8: liberar(LP);
					break;
		}
	}while(!(opc==8));
}

main(){
	ListaPersonas LP;
	inicia(LP);
	menu(LP);
}

