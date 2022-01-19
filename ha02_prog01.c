#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
/** 
 * Defining a structure(node) for each term in a polynomial 
 **/ 
  
typedef struct Node { 
    int coeff; 
    int expon; 
    struct Node* next; 
}Node_t; 
 
/**
 * creating (linked list) and instering nodes 
 **/
Node_t* insert(Node_t* poly, int coeff, int expon) { 
  Node_t* term = NULL; 
  Node_t* temp = NULL; 
 
  term = malloc(sizeof(Node_t));         //allocating memory for the node
  term->coeff = coeff; 
  term->expon = expon; 
  
  // if polynomial is empty
  
  if (poly==NULL) {
    poly = term; 
    return poly; 
  } 
  // if polynomial is not empty Add to end and link them
  temp = poly; 
  while (temp->next != NULL) { 
    temp = temp->next; 
  } 
  temp->next = term; 
  return poly;
} 

/**
 * traverse function is used to display the resultant polynomial considering 
 * the sign of the polynomial
 **/
 void traverse(Node_t* poly) { 
  char sign;     
  if (poly != NULL) { 
    printf("%dx**%d", poly->coeff, poly->expon); 
    poly = poly->next; 
  } 
  while (poly != NULL) { 
    if (poly->coeff > 0) { // if coefficient is greater than 0
      sign ='+';
      if (poly->expon == 0) {
        printf(" %c %d ", sign, poly->coeff); 
      }
      else if (poly->expon == 1) {
        printf(" %c %dx ", sign, poly->coeff); 
      }
      else {
        printf(" %c %dx**%d ", sign, poly->coeff, poly->expon);   
      }
    } 
    else {  // if coefficient is less than 0
      sign = '-';
      poly->coeff *= -1;
      if (poly->expon == 0) {
        printf(" %c %d ", sign, poly->coeff); 
      }
      else if (poly->expon == 1) {
        printf(" %c %dx ", sign, poly->coeff); 
      }
      else {
        printf(" %c %dx**%d", sign, poly->coeff, poly->expon);   
      }
    } 
    poly = poly->next; 
    }
} 
 
/**
 * adding the polynomials and also linking the each node/term after every
 * node gets added
 **/
 
Node_t* padd(Node_t* p1, Node_t* p2) { 
  Node_t* sum  = NULL; 
     
  while ((p1!=NULL) && (p2!=NULL)) { 
    if (p1->expon > p2->expon) { 
      sum = insert(sum, p1->coeff, p1->expon); 
        p1 = p1->next; 
    } 
    else if (p1->expon == p2->expon) { 
      int scoeff = p1->coeff + p2->coeff; 
      if (scoeff != 0) { 
        sum = insert(sum, scoeff, p1->expon); 
      } 
      p1 = p1->next; 
      p2 = p2->next; 
    } 
    else { 
      sum = insert(sum, p2->coeff, p2->expon); 
        p2 = p2->next; 
    } 
  } 
  while (p2 != NULL) { 
    sum = insert(sum, p2->coeff, p2->expon); 
    p2=p2->next; 
  } 
  while (p1 != NULL) { 
    sum = insert(sum, p1->coeff, p1->expon); 
    p1 = p1->next; 
  } 
  return sum; 
} 
 
//----------------------------- 
 
int main() { 
     
  int coeff; 
  int expon; 
  //number of polynomials to be added 
  int numpoly = 3; 
  scanf("%d", &numpoly); 
  if (numpoly >= 1 && numpoly <= 10) { 
    int pterms[numpoly]; 
    Node_t* p[numpoly];           //array of pointers
    Node_t* sum = NULL; 
 
    //reading number of terms in each polynomials 
    for (size_t i=0; i<numpoly; i++) { 
      scanf("%d", &pterms[i]); 
    } 
    
    //reading the coefficient and exponent of each polynomials 
    for (size_t i=0; i<numpoly; i++) { 
      p[i] = NULL; 
      for (size_t j=0; j<pterms[i]; j++) { 
        scanf("%d %d", &coeff, &expon); 
        p[i] = insert(p[i], coeff, expon);  
      } 
    } 
    
    //calling add function till each polynomial gets added
    for (size_t i=0; i<numpoly; i++) { 
      sum = padd(sum, p[i]); 
    }
    traverse(sum); //printing the resultant polynomial by calling traverse function
  }
  else {
    exit(0);
  }
}

