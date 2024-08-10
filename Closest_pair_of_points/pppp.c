#include "pppp.h"

//
//  PPPP - Paire de Points les Plus Proches
//
//    Chacun des algorithmes, les fonction du type pppp_xxx(), doit
//    renvoyer le couple {i,j} d'indices des deux points les plus
//    proches.
//
// -> la structure "point" est définie dans "tools.h"
// -> la structure "couple" est définie dans "pppp.h"
//
//
// Extensions/optimisations à tester (une fois que vous avez bien
// avancé):
//
// Pour pppp_divide():
//
// . Pour la recherche du min dans Sy, au lieu de mettre "j <= i+7",
//   utilisez "Sy[j].y - Sy[i].y < delta", ce qui va générer moins de
//   tests. Optimisez encore le test avec "Sy[j].y < d" en posant d =
//   delta + Sy[i].y.
//
// . L'algorithme du cours suppose qu'il n'y a qu'un seul point
//   d'abscisse x*, l'abscisse du médian. Contournez ce problème pour
//   qu'il fonctionne sans cette hypothèse. Pour cela, il faut (1)
//   utiliser le même test de comparaison en x pour le tri de Vx[] et
//   le remplissage de Ay[] afin de garantir |Ax| = |Ay|; et (2) que
//   ce test de comparaison en x soit un ordre total, c'est-à-dire ne
//   donne 0 que si (x,y) = (x',y'), et pas seulement si x = x'.


couple pppp_naive(point* V,int n){
  couple result = {-1,-1};
  double dmin=dist(V[0],V[1]);
  int i,j;
  for(i=0;i<n-1;i++)
  {
    for( j=i;j<n;j++)
     if(dist(V[i],V[j])<dmin)
     {
      dmin=dist(V[i],V[j]);
      result.i=i;
      result.j=j;
     }
  }
 
  return result;
}


// Fonction de comparaison des ordonnées pour qsort():
// renvoie -1 si y(A)<y(B), +1 si y(A)>y(B) et 0 sinon.
int fcmp_y(const void *A, const void *B) {
  if(y(A)<y(B))
     return -1;
  else
   if(y(A)>y(B))
     return 1;
  return 0;
}


// Fonction de comparaison pour des abscisses qsort():
// renvoie -1 si x(A)<x(B), +1 si x(A)>x(B) et 0 sinon.
int fcmp_x(const void *A, const void *B) {
  if(x(A)<x(B))
     return -1;
  else
   if(x(A)>x(B))
     return 1;
  return 0;
}


// paire de points pour pppp_rec()
typedef struct{
  point P1,P2;
} ppoints;


// Cette fonction doit, comme dans l'algorithme du cours, renvoyer la
// paire de points les plus proche pris dans l'ensemble Vx[] (type
// "ppoints"), et non pas les indices des points les plus proches
// (type "couple"). La récurrence est plus simple ainsi. C'est
// pppp_divide() qui se chargera de retrouver les indices dans V[] des
// deux points en question.
//
// Point de vigilance. Le choix du médian, celui de rang ceil(n/2),
// est important pour que la séparation en A et B donne deux ensembles
// d'au moins 2 points. Il se trouve aussi que ceil(n/2) =
// floor((n+1)/2) = (int)(n+1)/2. Les points ayant des indices
// commençant à 0, il faut donc prendre le bon indice.
//
ppoints pppp_rec(point* Vx,point* Vy,int n){
  ppoints Q = {Vx[0],Vx[0]};
  if(n=2||n==3)
  {
    
  }
  else
  {
    int ind_median=(int)(n+1)/2;
    point p_median=Vx[ind_median];
    int x_star=X(p_median);//l'abs de point median

    //les ensembles A et B
    point A[ind_median],B[n-ind_median];
    int ind_A=0,ind_B=0;
    for(int i=0;i<n;i++)
    {
      if(X(Vx[i])<=x_star)
        {
          A[ind_A++]=Vx[i];
        }
      else
      {
        B[ind_B++]=Vx[i];
      }
        
    }
    //les ensembles Ax=A et Px
    //Bx= B et Px
    //Ay=A et Py
    //By=B et By
    point Ax[ind_median],Bx[ind_median],Ay[ind_median],By[ind_median];
    //on tri les arrays
    qsort(A,ind_median,sizeof(point),fcmp_x);
    qsort(B,n-ind_median,sizeof(point),fcmp_x);
    qsort(Vx,n,sizeof(point),fcmp_x);
    qsort(Vy,n,sizeof(point),fcmp_x);


    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        if(X(Vx[i]))
  }

  return Q;
}


couple pppp_divide(point* V,int n){

  // Vx[] = V[] trié selon x
  point *Vx = malloc(n*sizeof(*Vx));
  memcpy(Vx,V,n*sizeof(*V));
  qsort(Vx,n,sizeof(point),fcmp_x);

  // Vy[] = V[] trié selon y
  point *Vy = malloc(n*sizeof(*Vy));
  memcpy(Vy,V,n*sizeof(*V));
  qsort(Vy,n,sizeof(point),fcmp_y);

  // Q = {P1,P2} = paire de points les plus proches
  ppoints Q = pppp_rec(Vx,Vy,n);
  free(Vx);
  free(Vy);

  // cherche dans V[] les indices des deux points de Q
  couple result = {-1,-1};
  for(int i=0; i<n; i++){
    if( Q.P1.x == V[i].x && Q.P1.y == V[i].y ) result.i = i;
    if( Q.P2.x == V[i].x && Q.P2.y == V[i].y ) result.j = i;
  }
  
  return result;
}
