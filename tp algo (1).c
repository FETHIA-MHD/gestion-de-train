
// mahdi fethia g2 191932028150



#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#define TailleDeQuai 10
#define Max 50
#define MaxTrain 10
#define MaxParkingRails 4
#define MapSize 6


typedef char chaine[Max];



//passager
typedef struct passager *Passagers;
typedef struct passager
{
int IdPas;
chaine destination;
Passagers passagerSuivant;

}Passager;

//train
typedef struct train
{
    int IdTrain;
    int capaciteMax;
    int placesPrises;
    Passagers listeDePassager;
chaine destination;
int vitesse;
int kilometreRestant;

}Train;

//Quai
typedef struct parkingRail
{
chaine IdQuai;
int capacity;
    int premierTrainAPartir;
Train listeDeTrain[TailleDeQuai];

}ParkingRail;


//****************************************************************************************************************************************************//
//protoypes


//Pour les quais
ParkingRail CreerUnParkingRail(chaine Id,int capacity);
int PileRemplie(ParkingRail PK);
int Empiler(Train TrainCourant, ParkingRail * ParkingForTrain);
ParkingRail TrouverDesTrainDisponible(ParkingRail ParkingForTrain, Train * Trains, int numTrain);
int AjouterQuais(ParkingRail * Quais,int NumQuai,chaine IdentifiantQuai, int capacity, Train * Trains, int NumTrain);
void UpdateQuais( ParkingRail * Quais, int NumQuai, Train * Trains, int NumTrain );
Train Depiler (ParkingRail * ParkingForTrain);
void AfficherParkingRail(ParkingRail* ParkingRails, int NumParkingRail);
int PileVide(ParkingRail * ParkingForTrain);


//Pour les passager
Passagers CreerPassager(int IDPassagerCourant, chaine Destination);
int SiListeVide(Passagers ListePassager);
int TailleListe(Passagers ListePassager);
Passagers AvoirDernierElementList(Passagers ListePassager);
Passagers ReservationPlace(Passagers ListePassagers, Train * Trains, int NumTrain, chaine Destination);
int ExistIdDansListe(int IDRecherche,Passagers ListePassager);
Passagers AnnulerReservation(Passagers ListePassagers,int IDAnulation);
Passagers AjouterPassagerDansLaListe (Passager PassagerAAjouter, Passagers ListeDesPassagers);
void AfficherPassagers(Passagers ListePassagers);
Passager SupprimerPassagerListeAttenteEtLeRetourner(Passagers * ListePassagers,int iDPassager);


//Pour les trains
Train CreerTrain(int IDTrain, int PlacesSupportees, chaine Destination);
Train ViderTrain(Train T);
int AjouterTrain(Train * Trains, int Id, int Capacitee, chaine Destination);
void AfficherTrains(Train * Trains, int nbrTrains);
int SiTrainRemplis(Train TrainCourant);
void MiseAJourTableauDesTrain(Train TrainPourDepart,Train * Trains,int NumTrain);
Passagers Embarquement (ParkingRail * Quaies, int NumQuaie, Passagers PassagerPretPourEmbarquement, chaine Destinations[MapSize][2], int NumDestination, Train * Trains, int NumTrain);
void TrainEnMarche(ParkingRail * Quaies,int NumQuai,  Train * Trains, int NumTrain);

//Pour les destinations
int InitialiserLesDestinationsDisponibles(chaine Destinations[MapSize][2]);


//****************************************************************************************************************************************//


//LES FONCTIONS


//ParkingRail

ParkingRail CreerUnParkingRail(chaine Id,int capacity)
{
ParkingRail q;

strcpy(q.IdQuai,Id);
q.capacity=capacity;
q.premierTrainAPartir=-1;

return q;
}


int PileRemplie(ParkingRail q)
{
if(q.premierTrainAPartir < q.capacity)
    {
return 0;
}
return 1;
}


ParkingRail TrouverDesTrainDisponible(ParkingRail ParkingForTrain, Train * Trains, int numTrain)
{
int i;
for (i=0;i<numTrain;i++)
        {
            if((Trains[i].kilometreRestant==-1)&&(!PileRemplie(ParkingForTrain)))
            {
                Trains[i].kilometreRestant=0;
                Empiler(Trains[i],&ParkingForTrain);
                ParkingForTrain.capacity--;
            }
        }

return ParkingForTrain;
}


int Empiler(Train TrainCourant, ParkingRail * ParkingForTrain)
{
if(PileRemplie(*ParkingForTrain) == 0)
    {
ParkingForTrain->premierTrainAPartir++;
ParkingForTrain->listeDeTrain[ParkingForTrain->premierTrainAPartir] = TrainCourant;
return 1;
}
return 0;
}


int AjouterQuais(ParkingRail *Quais,int NumQuai,chaine IdentifiantQuai, int capacity, Train * Trains, int NumTrain)
{
Quais[NumQuai]=CreerUnParkingRail(IdentifiantQuai,capacity);
Quais[NumQuai]=TrouverDesTrainDisponible(Quais[NumQuai],Trains,NumTrain);
NumQuai++;

return NumQuai;
}


void UpdateQuais( ParkingRail * Quais, int NumQuai, Train * Trains, int NumTrain )
{
int j,i;
for(j=0;j<NumTrain;j++)
    {
for(i=0;i<NumQuai;i++)
{
        if((Trains[j].kilometreRestant==-1))
        {
            if(!PileRemplie(Quais[i]))
            {
                Trains[j].kilometreRestant=0;
                Empiler(Trains[j],&Quais[i]);
            }
        }
    }
}
}


Train Depiler(ParkingRail * ParkingForTrain)
{
Train x;
if(!PileVide(ParkingForTrain))
    {
        x = ParkingForTrain->listeDeTrain[ParkingForTrain->premierTrainAPartir];
ParkingForTrain-> premierTrainAPartir--;
return x;
}
}


void AfficherParkingRail(ParkingRail* ParkingRails, int NumParkingRail){
/********************************************************************************************/
int i,j;
printf("Le nombre de Quais dans la gare est de %d\n \n",NumParkingRail);


for(i=0;i<NumParkingRail;i++){

printf("Le nombre de train dans le quai %s est de %d \n",ParkingRails[i].IdQuai,ParkingRails[i].premierTrainAPartir+1);

for (j=ParkingRails[i].premierTrainAPartir;j>=0;j--){
    printf("le train ID=%d prendra le d�part en %d position\n",ParkingRails[i].listeDeTrain[j].IdTrain,ParkingRails[i].premierTrainAPartir-j+1);
}
}
}


int PileVide(ParkingRail * ParkingForTrain){
if(ParkingForTrain->premierTrainAPartir == -1){
return 1;
}
return 0;
}

//Passagers

Passagers CreerPassager(int IDPassager, chaine Destination)
{
Passagers pass;

pass =(Passagers)malloc(sizeof(Passager));
if(pass==NULL)
    {
printf("ERREUR d'allocation passager!'");
exit (-1);
}
pass->IdPas=IDPassager;
strcpy((pass->destination),Destination);
pass->passagerSuivant=NULL;

return pass;
}


int SiListeVide(Passagers ListePassager)
{
if(ListePassager == NULL)
    {
return 1;
}
return 0;
}


int TailleListe(Passagers ListePassager)
{
  int t=0;
  while(!SiListeVide(ListePassager))
    {
  ListePassager=ListePassager->passagerSuivant;
  t++;
}
return t;
 }


Passagers AvoirDernierElementList(Passagers ListePassager)
{
if (SiListeVide(ListePassager)==1)
    {
        return ListePassager;
}

Passagers ParcourPassager=ListePassager;
while (ParcourPassager->passagerSuivant!=NULL)
    {
        ParcourPassager=ParcourPassager->passagerSuivant;
    }

return ParcourPassager;


}


Passagers ReservationPlace(Passagers ListePassagers, Train * Trains, int NumTrain, chaine Destination){
//nous supposons que la destination n'existe pas
int i,SiDestinationTrouvee=0;

    printf("Liste vide ListePassagers ?%d\n",SiListeVide(ListePassagers));

//V�rifier si la destination est disponible
for(i=0;i<NumTrain;i++){

    if((SiDestinationTrouvee==0)&&(strcmp(Trains[i].destination,Destination)==0)){// la destination existe dans la gare
        //(!SiTrainRemplis(Trains[i]))&&// j'avais mis cette condition ensuite je me suis dis que c'est pas la peine puisque le passager va �tre mis dans la liste d'attente, si le train est maintenant remplis il ne le sera peut �tre pas lors de l'embarquement ... apr�s, si vous voulez modifier ...
        //(Trains[i].kilometreRestant<=0))// on check tout les trains, ceux qui sont en voyage et ceux qui sont dans le quai pour dire que la destination existe, maintenant pour la disponibilit� imm�diate ... c'est autre chose ...


       SiDestinationTrouvee=1;
       //Trains[i].PlacesPrises=Trains[i].PlacesPrises+1;// l'incr�mentation de cette variable se fera lors de l'embarquement ...
        }
}

if(SiDestinationTrouvee){// ajouter dans la liste des passagers en attente d'embarquement

    //Liste Vide, Cr�ation du premier �lement
    if(SiListeVide(ListePassagers)){
       ListePassagers=CreerPassager(0,Destination);
       return ListePassagers;
    }

    //Liste Non vide, aller au dernier element de la liste et ajouter un passager ou ajouter a la tete de la liste, votre choix !
    Passagers DernierElmnt=AvoirDernierElementList(ListePassagers);


    DernierElmnt->passagerSuivant=CreerPassager((DernierElmnt->IdPas)+1,Destination);

    printf("Dernier �lement : %d avec destination %s\n",DernierElmnt->IdPas,Destination);
}
else{ //destination non trouv�
    printf("La destination %s n'est pas disponible dans notre gare\n",Destination);
  }
return ListePassagers;
}


int ExistIdDansListe(int IDRecherche,Passagers ListePassager)
{
while(!SiListeVide)
    {
if(ListePassager->IdPas == IDRecherche)
{
return 1;
}
else
{
ListePassager=ListePassager->passagerSuivant;
}
}
return 0;
}


Passagers AnnulerReservation(Passagers ListePassagers,int IDAnulation)
{
  Passagers courant,partant;

  if((!ExistIdDansListe(IDAnulation,ListePassagers)) && (SiListeVide(ListePassagers)))
    {
  printf("Le passager n'a pas r�server");
  return NULL;
}
else
{
partant=ListePassagers;
courant=ListePassagers->passagerSuivant;

while((SiListeVide(courant)) && (courant->IdPas ==IDAnulation))
        {
partant=courant;
courant=courant->passagerSuivant;
}
}
partant->passagerSuivant=courant->passagerSuivant;
return ListePassagers;

 }


Passagers AjouterPassagerDansLaListe (Passager PassagerAAjouter, Passagers ListeDesPassagers)
{
Passager *nouv= &PassagerAAjouter;

if(!SiListeVide(ListeDesPassagers))
    {
nouv->passagerSuivant=ListeDesPassagers;
ListeDesPassagers=nouv;
}
else
    {
ListeDesPassagers=nouv;
}
return ListeDesPassagers;
}


void AfficherPassagers(Passagers ListePassagers)
{
Passagers ParcoursPassager=ListePassagers;

if (TailleListe(ParcoursPassager)==0)
    {
    printf("\n**Aucune reservation faite !\n");
    return;
}

printf("\nListe des r�servations \n");

while (ParcoursPassager!=NULL){
    printf("Le passager avec l'ID %d a reserv� la destination %s ! \n",ParcoursPassager->IdPas,ParcoursPassager->destination);
    ParcoursPassager=ParcoursPassager->passagerSuivant;
}

printf("\n");
}


Passager SupprimerPassagerListeAttenteEtLeRetourner(Passagers * ListePassagers,int iDPassager)
{
Passager PassagerARetourner;

    if ((*ListePassagers)->IdPas==iDPassager)
    {
        PassagerARetourner=**(ListePassagers);
        *ListePassagers=(*ListePassagers)->passagerSuivant;
        //printf("cas 0");
        return PassagerARetourner;

    }


    Passagers PassagerParent=*ListePassagers;
    Passagers PassagerCourant=(*ListePassagers)->passagerSuivant;

    while ((!SiListeVide(PassagerCourant))&&(PassagerCourant->IdPas!=iDPassager)){
        PassagerParent=PassagerCourant;
        PassagerCourant=PassagerParent->passagerSuivant;
    }

    if(SiListeVide(PassagerCourant)){
        printf("aucune suppression Faite !!! faite ! ");
        return;
    }

    //printf("suppression de passager %d",PassagerCourant->ID);
    PassagerParent->passagerSuivant=PassagerCourant->passagerSuivant;
    PassagerARetourner=*PassagerCourant;
    free(PassagerCourant);

//printf("je suis dans la suppression taille liste est : %d", TailleListe(*ListePassagers));
return PassagerARetourner;
}



//Trains


Train CreerTrain(int IDTrain, int PlacesSupportees, chaine Destination){
Train t;

t.IdTrain=IDTrain;
t.capaciteMax=PlacesSupportees;
strcpy(t.destination,Destination);
t.listeDePassager=NULL;
t.placesPrises=0;
t.kilometreRestant=-1;
t.vitesse=0;

return t;
}


Train ViderTrain(Train T)
{
T.listeDePassager=NULL;
T.placesPrises=0;
T.kilometreRestant=-1;

return T;
}


int AjouterTrain(Train * Trains, int Id, int Capacitee, chaine Destination)
{
Trains[Id]=CreerTrain(Id,Capacitee,Destination);
Id++;

return Id;
}


void AfficherTrains(Train * Trains, int nbrTrains)
{
int i;
printf("Il y'a %d trains dans la gare \n\n", nbrTrains);
for (i=0;i<nbrTrains;i++){

    // calcul du pourcentage de remplissage
    float Pourcentage=((float)Trains[i].placesPrises /(float)Trains[i].capaciteMax)*100;
    if (Trains[i].kilometreRestant==-1)
        printf("Train ID= %d est disponible pour %s \n",Trains[i].IdTrain, Trains[i].destination);
    else if (Trains[i].kilometreRestant==0)
        printf("Train ID= %d dans le quai, remplis a %.2f %%, en attente de d�part vers %s \n",Trains[i].IdTrain,Pourcentage, Trains[i].destination);
    else
       //printf("Le train avec ID= %d est en voyage vers %s, il lui reste %d Km pour rentrer. \n",Trains[i].identifiant,Trains[i].Destination, Trains[i].kilometreRestant);// premier affichage ... j'ai pas trop aim� :/
        printf("Train ID %d en Trajet passagers: %d, %.2f %%, ===== reste:%d Km ====> %s\n\n",Trains[i].IdTrain,Trains[i].placesPrises,Pourcentage,Trains[i].kilometreRestant,Trains[i].destination);

    }
}


int SiTrainRemplis(Train TrainCourant)
{
if(TrainCourant.capaciteMax >= TrainCourant.placesPrises)
    {
return 0;
}
return 1;
}


void MiseAJourTableauDesTrain(Train TrainPourDepart,Train * Trains,int NumTrain){
int i;
for (i=0;i<NumTrain;i++){
    if (TrainPourDepart.IdTrain==Trains[i].IdTrain){
        Trains[i]=TrainPourDepart;
        return;
    }
}
}


Passagers Embarquement (ParkingRail * Quaies, int NumQuaie, Passagers PassagerPretPourEmbarquement, chaine Destinations[MapSize][2], int NumDestination, Train * Trains, int NumTrain){
int i;
printf("Liste Des Prochains Departs\n");
    for (i=0;i<NumQuaie;i++){
        Train TrainPourDepart=Depiler(&Quaies[i]);
        if(TrainPourDepart.IdTrain==-1)
            printf("Le quai %s est vide \n",Quaies[i].IdQuai);
        else{
       printf("Prochain train,ID=%d, a destination de %s dans le quai %s\n",TrainPourDepart.IdTrain,TrainPourDepart.destination,Quaies[i].IdQuai);

            //R�cup�rerLaDistance
            for(i=0;i<(NumDestination+1);i++){
                if(strcmp(TrainPourDepart.destination,Destinations[i][0])==0){
                    TrainPourDepart.kilometreRestant=atoi(Destinations[i][1]);
                }
            }

            Passagers ParcourirPassager=PassagerPretPourEmbarquement;
            while(ParcourirPassager!=NULL){
                if((strcmp(ParcourirPassager->destination,TrainPourDepart.destination)==0)&&(!SiTrainRemplis(TrainPourDepart))){

                    //Enlever de la liste des passager en attente et le mettre dans la liste des passagers dans le train
                    Passager PassagerTmp=SupprimerPassagerListeAttenteEtLeRetourner(&PassagerPretPourEmbarquement,ParcourirPassager->IdPas);

                    //Le mettre dans le train
                    TrainPourDepart.listeDePassager=AjouterPassagerDansLaListe(PassagerTmp,TrainPourDepart.listeDePassager);
                    TrainPourDepart.placesPrises=TrainPourDepart.placesPrises+1;
                }
                ParcourirPassager=ParcourirPassager->passagerSuivant;
            }

            MiseAJourTableauDesTrain(TrainPourDepart,Trains,NumTrain);
        }
    }
    printf("\n");
return PassagerPretPourEmbarquement;
}


void TrainEnMarche(ParkingRail * Quaies,int NumQuai,  Train * Trains, int NumTrain){
int i;
// Vitesse constante pour tout les trains de 5 ! votre job est de la rendre dynamique en utilisant a la plce la variable Train[i].vitesse
for (i=0;i<NumTrain;i++){

    if(Trains[i].kilometreRestant==5){
        Trains[i].kilometreRestant=Trains[i].kilometreRestant-5;
        int ChoixAleatoireQuai=rand()%(NumQuai);
        Trains[i]=ViderTrain(Trains[i]);

        if(Empiler(Trains[i],&Quaies[ChoixAleatoireQuai]))
            printf("Train Id=%d revient de %s rentre dans le Quai %s\n",Trains[i].IdTrain,Trains[i].destination,Quaies[ChoixAleatoireQuai].IdQuai);
        else
        {
            printf("\ntout les quaies sont remplis\n Train ID=%d en attente ",Trains[i].IdTrain);
            Trains[i].kilometreRestant=-1;
        }
        }
    else if(Trains[i].kilometreRestant>5)
        Trains[i].kilometreRestant=Trains[i].kilometreRestant-5;
    }
}


//Fonctions associ� aux Destinations //

int InitialiserLesDestinationsDisponibles(chaine Destinations[MapSize][2])
{
strcpy(Destinations[0][0],"Tokyo");
strcpy(Destinations[0][1],"100");
strcpy(Destinations[1][0],"Ouergla");
strcpy(Destinations[1][1],"15");
strcpy(Destinations[2][0],"Berlin");
strcpy(Destinations[2][1],"20");
strcpy(Destinations[3][0],"Rio");
strcpy(Destinations[3][1],"50");
strcpy(Destinations[4][0],"Helsinki");
strcpy(Destinations[4][1],"40");
strcpy(Destinations[5][0],"Nairobi");
strcpy(Destinations[5][1],"20");
strcpy(Destinations[6][0],"Denver");
strcpy(Destinations[6][1],"45");
return 6; //nombres de destinations en comptant le 0
}


int main(int argc, char *argv[]) {

//D�claration des structures de donn�es
    Train Trains[MaxTrain];// tableau de train
    ParkingRail Quais[MaxParkingRails]; // tableau de quais
    int NumTrain=0;//Nombre de train qu'il y'a dans la gare
    int NumQuai=0;// nombre de quais / Parking rail qu'il y'a dans la gare
int i;


    chaine Destinations[MapSize][2]; // matrice des destinations

    int NumDestinations= InitialiserLesDestinationsDisponibles(Destinations);

    // Ajout des trains
    NumTrain=AjouterTrain(Trains,NumTrain,15,"Tokyo");
    NumTrain=AjouterTrain(Trains,NumTrain,10,"Helsinki");
    NumTrain=AjouterTrain(Trains,NumTrain,10,"Helsinki");
    NumTrain=AjouterTrain(Trains,NumTrain,10,"Tokyo");
    NumTrain=AjouterTrain(Trains,NumTrain,10,"Berlin");
    NumTrain=AjouterTrain(Trains,NumTrain,8,"Nairobi");
    NumTrain=AjouterTrain(Trains,NumTrain,10,"Denver");
    NumTrain=AjouterTrain(Trains,NumTrain,10,"Nairobi");
    NumTrain=AjouterTrain(Trains,NumTrain,10,"Berlin");
    NumTrain=AjouterTrain(Trains,NumTrain,10,"Ouergla");




    // Ajouter les Quais

    NumQuai=AjouterQuais(Quais,NumQuai,"Q1",2,Trains, NumTrain);
    NumQuai=AjouterQuais(Quais,NumQuai,"El Moudjahid",1,Trains, NumTrain);
    NumQuai=AjouterQuais(Quais,NumQuai,"Roberto Carlos",1,Trains,NumTrain);

    Passagers ListeDesPassagerEnAttente=NULL; // d�clarer la liste des passagers en attente



    //Commencer la simulation
    int NbrHeur=0;
    while(1){// nous pouvons remplacer le 1 par un nombre d�it�ration bien pr�cis !
        AfficherParkingRail(Quais,NumQuai); // afficher l��tat des quais pour voir ou se trouve les train.
        NbrHeur++;
        printf("************Heure %d***********\n\n",NbrHeur);
        srand(time(NULL));// appeler la fonction random pour g�n�rer des nombres al�atoire de r�servations et d�annulations

        int NombreAleatoireDeReservations=rand()%10+5;
        int NombreAleatoireDAnulations=rand()%5;
// nous devons nous assurer que le nombres de reservations soit strictement superieurs aux nombre d�annulations
        printf("Nombre de reservations : %d\n",NombreAleatoireDeReservations);
        printf("Nombre d'annulations : %d\n",NombreAleatoireDAnulations);

        for (i=0;i<NombreAleatoireDeReservations;i++){
            int ChoisirUneDestinationAleatoire=rand()%(NumDestinations+1);

            ListeDesPassagerEnAttente=ReservationPlace(ListeDesPassagerEnAttente, Trains,NumTrain,Destinations[ChoisirUneDestinationAleatoire][0]);


}
// r�server des places et ajouter des passagers dans la liste d�attente, a ce stade, aucun passager n�est dans le train, rien que la variable � place prises � est incr�menter pour dire que les places sont reserv�es


        for (i=0;i<NombreAleatoireDAnulations;i++){
            int ChoisirUnIDPourAnulationAleatoire=rand()% TailleListe(ListeDesPassagerEnAttente);
            ListeDesPassagerEnAttente=AnnulerReservation(ListeDesPassagerEnAttente,ChoisirUnIDPourAnulationAleatoire);
// briser la liste chain�e � ListeDesPassagersEnAttente � et enlever les passagers qui souhaites annuler leurs reservations.
        }

        printf("\n Nombre de passagers en attente %d\n",TailleListe(ListeDesPassagerEnAttente));
        AfficherPassagers(ListeDesPassagerEnAttente);
// affichier l��tat des passagers en attente avant embarquement et apr�s que les r�servations et annulations soient faites
        ListeDesPassagerEnAttente=Embarquement(Quais, NumQuai, ListeDesPassagerEnAttente, Destinations,NumDestinations, Trains,NumTrain );
// Embarquer les passager !
        AfficherTrains(Trains,NumTrain);
//afficher l��tat des trains pour voir si ils ont pris des passagers avec eux.

        TrainEnMarche(Quais,NumQuai, Trains, NumTrain);
// lancer les trains qui sont les premiers dans les quais
        printf("\n Nombre de passagers en attente apr�s embarquement %d\n",TailleListe(ListeDesPassagerEnAttente));

        AfficherPassagers(ListeDesPassagerEnAttente);

// afficher l��tat des passagers en attente apr�s embarquement, dans le cas ou votre programme marche correctement, il ne devrai y avoir aucun passager qui demande une destination qui vient d��tre propos� par un train sur le d�part sauf si le train est remplis a 100%.
        UpdateQuais( Quais, NumQuai, Trains, NumTrain );
//Mettre a jour les quais en r�cup�rant les train en attente et en avan�ant les tarins dans la pile pour proposer de nouvelle destinations.
        system("pause");// arr�ter le programme pour avoir le temps de lire les affichages
// vous pouvez ajouter un � clearscreen � ici mais ceci vous emp�chera d�avoir une vue sur l�historique


    }

    return 0;
}

