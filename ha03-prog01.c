#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUCKET_SIZE 2

//defining structuer
typedef struct {
  unsigned long int bucket[BUCKET_SIZE];
}node_t;

//declaring all the functions which are used to avoid warnings
int hash_fn(unsigned long int key, size_t HASH_SIZE);
size_t hash_size_modifier(size_t HASH_SIZE);
int linear_probe(node_t* hash, int hash_val, unsigned long int key, size_t HASH_SIZE);
node_t* insert(node_t* hash, unsigned long int key, int hash_val);
node_t* rehash(node_t* hash, size_t HASH_SIZE);

//--------------------------------------------------------------------------------------------
int hash_fn(unsigned long int key, size_t HASH_SIZE) {//this function returns index of the hash table where the
  return (key%HASH_SIZE);                             //number is to be inserted
}
//--------------------------------------------------------------------------------------------
size_t hash_size_modifier(size_t HASH_SIZE) {//this function doubles the hash size value and returns it
    return HASH_SIZE*2;
}
//--------------------------------------------------------------------------------------------
int linear_probe(node_t* hash, int hash_val, unsigned long int key, size_t HASH_SIZE) {
  int temp = hash_val;
  temp = (temp + 1) % HASH_SIZE;
  while(temp != hash_val) {
    if(hash[temp].bucket[0] == key || hash[temp].bucket[1] == key){
      return -2;//if the key is already present then return -2
    }
    if(hash[temp].bucket[0]==0 || hash[temp].bucket[1]==0){
      return temp;//if empty slot is found then return the index of the empty slot
    }
    temp = (temp + 1) % HASH_SIZE;//incrimenting temp value
  }
  return -1;//return -1 is no empty slot is found
}
//--------------------------------------------------------------------------------------------
node_t* insert(node_t* hash, unsigned long int key, int hash_val) {
  for(size_t i=0; i<2; i++) {//to check if the number is already present or not
    if(hash[hash_val].bucket[i] != 0) {
      if(hash[hash_val].bucket[i] == key){
        return NULL;// if present return NULL
      }
      continue;//else check for next
    }
    hash[hash_val].bucket[i] = key;//if not insert the number to that index
    break;
  }
  return hash;
}
//--------------------------------------------------------------------------------------------
node_t* rehash(node_t* hash, size_t HASH_SIZE){
  node_t* temp = calloc(HASH_SIZE, sizeof(node_t));//keeping a temp hash table to copy previously available data
  int hash_val;
  for(size_t i=0; i<(HASH_SIZE/2); i++){
    for(size_t j=0; j<2; j++){
      hash_val = hash_fn(hash[i].bucket[j], HASH_SIZE);//rehashing numbers here
      temp = insert(temp, hash[i].bucket[j], hash_val);//copying all the data to temp
    }
  }
  hash = temp;
  return hash;
}
//--------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  FILE *fp;
  node_t* hash = NULL;
  node_t* node = NULL;
  size_t HASH_SIZE = 10;
  unsigned long int key;
  int hash_val;
  int num, lp_val;

  if (argc < 2) {
    printf("Usage: %s <filename>", argv[1]);
    exit(1);
  }

  if ((fp = fopen(argv[1], "r")) == NULL){
    printf("Error in opening file %s\n", argv[1]);
    exit(1);
  }

  //1st line of file contains total number of phone numbers
  fscanf(fp, "%d", &num);
  hash = calloc(HASH_SIZE, sizeof(node_t));

  //start to read phone numbers in while loop till end of file
  while(fscanf(fp, "%lu", &key) != EOF) {
    hash_val = hash_fn(key, HASH_SIZE);              //calling hash function to calculate hash value
    node = insert(hash, key, hash_val);              //inserting the phone number to hash table

    if(node == NULL){//if insert function returns NULL it means the key is already present in the hash table
      continue;      //phone numbers are to be repreated so we skip that repreated number
    }
    else {
      hash = node;
      if((hash[hash_val].bucket[0]!=key)&&(hash[hash_val].bucket[1]!=key)) {//if the key is not present in that hash value location then
        lp_val = linear_probe(hash, hash_val, key,HASH_SIZE);               //we do linear probe to find next location to insert the number
        if(lp_val != -1 && lp_val != -2) {//if linear probe function returns except -1 and -2 it means we found an empty spot to insert
          hash = insert(hash, key, lp_val);
        }
        else if(lp_val == -1){                                     //if linear probe function returns -1 it means hash table is full and
          HASH_SIZE = hash_size_modifier(HASH_SIZE);               // we have to double the hash size and double the modulo value
          hash = rehash(hash, HASH_SIZE);                          //then rehash all the numbers again with new modulo value
          hash = insert(hash, key , hash_fn(key,HASH_SIZE));       //then insert
        }
      }
    }
  }

  //printing hash entries
  for (size_t i=0; i<HASH_SIZE; i++) {
    printf("%zu  -  ", i);
    for(size_t j=0; j<2; j++){
      if(hash[i].bucket[j] == 0) {
        continue;
      }
      printf("%lu\t",hash[i].bucket[j]);
    }
    printf("\n");
  }//end for loop for printing the hash entries

  free(hash);        //releasing the dinamically allocated memory for hash table
  return 0;
}//end of main function




