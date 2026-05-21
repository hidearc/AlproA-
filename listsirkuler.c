/* File : listsirkuler.h */
/* ADT List Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */
/* Representasi berkait dengan Address adalah pointer */
/* ElType adalah integer */
#include "boolean.h"
#include <stdlib.h>  // Add for malloc and free
#include <stdio.h>
#include "listsirkuler.h"
/*
typedef int ElType;
typedef struct node *Address;
typedef struct node { 
	ElType info;
	Address next;
} ElmtList;
typedef struct {
	Address first;
} List;
*/
/* Definisi list : */
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address P dapat diacu INFO(P), NEXT(P) */
/* Elemen terakhir list: jika Addressnya Last, maka NEXT(Last)=FIRST(l) */

/* Selektor */
#define INFO(P) (P)->info
#define NEXT(P) (P)->next
#define FIRST(l) ((l).first)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
  return l.first == NULL;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. l sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
  l->first = NULL;
}

/****************** Manajemen Memori ******************/
Address allocate(ElType val)
/* Mengirimkan Address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka Address tidak NULL, dan misalnya */
/* menghasilkan P, maka INFO(P)=val, NEXT(P)=NULL */
/* Jika alokasi gagal, mengirimkan NULL */
{
  Address newnode = (Address)malloc(sizeof(ElmtList));
  if(newnode != NULL){
    newnode->info = val;      // Fixed: use -> not .
    newnode->next = NULL;
    return newnode;
  }
  return NULL;
}

void deallocate(Address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian Address P */
{
  free(P);
  // P = NULL;  // This doesn't affect the caller's pointer
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil */
{
  Address newNode = allocate(val);
  if(newNode != NULL){
    if(isEmpty(*l)) {
      // If list is empty, new node points to itself
      newNode->next = newNode;
      l->first = newNode;
    } else {
      // Find the last node
      Address last = l->first;
      while(last->next != l->first) {
        last = last->next;
      }
      // Insert at beginning
      newNode->next = l->first;
      last->next = newNode;
      l->first = newNode;
    }
  }
}

void insertLast(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
  Address newNode = allocate(val);
  if(newNode != NULL) {
    if(isEmpty(*l)) {
      // If list is empty, new node points to itself
      newNode->next = newNode;
      l->first = newNode;
    } else {
      // Find the last node
      Address last = l->first;
      while(last->next != l->first) {
        last = last->next;
      }
      // Insert at end
      newNode->next = l->first;
      last->next = newNode;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. val adalah elemen pertama list l sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      First element yg baru adalah suksesor elemen pertama yang lama */
/*      Alamat elemen terakhir di-dealokasi */
{
  if(!isEmpty(*l)) {
    Address firstNode = l->first;
    *val = firstNode->info;
    
    if(firstNode->next == l->first) {
      // Only one node in the list
      deallocate(firstNode);
      l->first = NULL;
    } else {
      // Find the last node
      Address last = l->first;
      while(last->next != l->first) {
        last = last->next;
      }
      // Update last node's next to point to the new first
      l->first = firstNode->next;
      last->next = l->first;
      deallocate(firstNode);
    }
  }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
  printf("[");
  if(!isEmpty(l)) {
    Address current = l.first;
    do {
      printf("%d", current->info);
      current = current->next;
      if(current != l.first) {
        printf(",");
      }
    } while(current != l.first);
  }
  printf("]");
}

#endif
