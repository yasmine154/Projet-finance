#include <stdio.h>
#include <stdlib.h>
struct date_operation{
    int jour;
    int mois;
    int annee;

};
struct date_valeur{
    int jour;
    int mois;
    int annee;
};

struct operation {
    struct date_operation date_op;
    struct date_valeur date_val; 
    float montant;
    int nb_jours;
    int nb_debiteur; 
    int solde;
};
void ajouter_operation(struct operation operations[], int *nombre_operations, int jbanque , int Mois_annee[]){
    printf("Entrer le jour de l'operation : ");
    int j ;
    scanf("%d",&j);
    operations[*nombre_operations].date_op.jour=j;
    printf("Entrer le mois de l'operation : ");
    int m;
    scanf("%d",&m);
    operations[*nombre_operations].date_op.mois=m;
    printf("Entrer l'annee de l'operation : ");
    int a;
    scanf("%d",&a);
    operations[*nombre_operations].date_op.annee=a;
    if (j+jbanque>Mois_annee[m-1]){
      operations[*nombre_operations].date_val.jour=jbanque-(Mois_annee[m-1]-j);
      operations[*nombre_operations].date_val.mois=m+1;
      if (m==31){
        operations[*nombre_operations].date_val.annee=a+1;
      }
    }
    else{
        operations[*nombre_operations].date_val.jour=j+jbanque;
        operations[*nombre_operations].date_val.mois=m;
        operations[*nombre_operations].date_val.annee=a;

    }
    printf("saisir le type de l'operation: \n 1.Depot\n 2.Retrait \n");
    int t;
    scanf("%d",&t);
    printf("saisir le montant : ");
    float mont;
    scanf("%f",&mont);
    if (t==1){
        operations[*nombre_operations].montant=mont;
    }
    if (t==2){
        operations[*nombre_operations].montant=-mont;
    }
    (*nombre_operations)++;

}







int main(){
    struct operation operations[100];
    int Mois_annee[]={31,29,31,30,31,30,31,31,30,31,30,31}; 
    printf("        ***COMPTE COURANT***\n");
    printf("Saisir le nombre d'operations a effectuer : ");
    int nb;
    scanf("%d",&nb);
    printf("saisir le nombre de jours de la banque : ");
    int jbanque; 
    scanf("%d",&jbanque); 
    printf("saisir le taux du decouvert en pourcentage : \n");
    float taux;
    scanf("%f",&taux);
    printf("saisir la commision sur le plus fort découvert en pourcentage : \n");
    float cpfd;
    scanf("%f",&cpfd);
    printf("saisir la commission des mouvements debit en pourcentage : \n");
    float md;
    scanf("%f",&md);
    int nombre_operations=0 ; 
    
    for (int i=0;i<nb;i++){
        ajouter_operation(operations,&nombre_operations,jbanque,Mois_annee);
    }
    for (int i=0; i<nb-1 ;i++){
        if (operations[i].date_val.mois==operations[i+1].date_val.mois){
            operations[i].nb_jours=operations[i+1].date_val.jour-operations[i].date_val.jour;
        }
        else{
            int diff;
            diff=operations[i+1].date_val.mois-operations[i].date_val.mois;
            if (diff==1){
                operations[i].nb_jours=(Mois_annee[operations[i].date_val.mois-1]-operations[i].date_val.jour)+operations[i+1].date_val.jour;
            }
            else if (diff>1){
                 operations[i].nb_jours=(Mois_annee[operations[i].date_val.mois-1]-operations[i].date_val.jour)+operations[i+1].date_val.jour;
                 for(int j=0;j<diff-1;j++){
                    operations[i].nb_jours+=Mois_annee[operations[i].date_val.mois+j];
                    }
                 operations[i].nb_jours+=operations[i+1].date_val.jour;   
        }
    }
}
operations[nb-1].nb_jours=Mois_annee[operations[nb-1].date_val.mois-1]-operations[nb-1].date_val.jour;
operations[0].solde=operations[0].montant;
for(int i=1; i<nb ;i++){
    operations[i].solde=operations[i-1].solde+operations[i].montant;
}
float soldetot=operations[0].solde;
for (int i=0;i<nb-1;i++){
    soldetot+=operations[i+1].montant;
}
printf("Votre solde le %d / %d / %d  est :  %f  dinars \n",Mois_annee[operations[nb-1].date_val.mois-1],operations[nb-1].date_val.mois,operations[nb-1].date_val.annee,soldetot);
float s=0;
for (int i=0;i<nb;i++){
    if (operations[i].solde<0){
        s+=(operations[i].solde*operations[i].nb_jours);
    }
}
float interet;
interet=(abs(s)*taux)/36000; 
printf("L'interet : %f \n",interet);

float c=0;
for (int i=0;i<nb;i++){
    if (operations[i].solde<0){
        c+=abs(operations[i].solde);
    }
}
float compf;
compf=(c*cpfd)/100;
printf("Commission plus fort decouvert : %f \n",compf);

float a=0;
for(int i=0;i<nb;i++){
    if(operations[i].montant<0){
        a+=abs(operations[i].montant);
    }
}
float comd;
comd= (a*md)/100;
printf("Commission de debit : %f \n",comd);

float agios;
agios=interet+compf+comd;
printf("Agios : %f \n", agios); 



int x; scanf("%d",x);
return 0;
}
