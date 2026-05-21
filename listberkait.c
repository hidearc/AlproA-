/* File : listberkait.h */
/* ADT list berkait dengan representasi fisik pointer */
/* Representasi address dengan pointer */
/* ElType adalah integer */
#include <stdlib.h>
#include <stdio.h>
#include "listberkait.h"
#include "boolean.h"

#define IDX_UNDEF (-1)
#define ELMT_UNDEF (-999)

#define INFO(p) (p)->info
#define NEXT(p) (p)->next

/****************** DEFINISI LIST ******************/
/* List kosong : FIRST(l) = NULL */
/* Setiap elemen dengan Address p dapat diacu INFO(p), NEXT(p) */
/* Elemen terakhir list: jika addressnya Last, maka NEXT(Last)=NULL */

/* 
 * PENJELASAN TIPE STRUKTUR DATA:
 * 1. Node adalah representasi elemen yang menyimpan data (info) dan tali (next).
 * 2. Address adalah alamat memori dari Node tersebut (pointer ke Node).
 * 3. List adalah nama lain untuk sebuah Address yang menunjuk ke Node pertama (Head).
 *    Oleh karena itu, secara teknis Address adalah List. Namun agar tidak salah paham,
 *    pada praktikum ini List mengacu pada Address pertama pada suatu stuktur list berkait.
 */
typedef Address List;

#define FIRST(l) (l)

/****************** MANAJEMEN MEMORI ******************/
Address newNode(ElType val)
/* Mengembalikan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NULL, dan misalnya */
/* menghasilkan p, maka INFO(p)=val, NEXT(p)=NULL */
/* Jika alokasi gagal, mengirimkan NULL (alokasi gagal jika malloc mengembalikan null) */
/* Catatan: Praktikan WAJIB mengimplementasikan fungsi ini. */
{
  Address new = malloc(sizeof(Node));
  if(new != NULL){
    new->info = val;
    new->next = NULL;
    //printf("Alokasi berhasil! Node sudah dibuat!\n");
    return new;
  }
  //printf("Alokasi gagal!\n");
  return NULL;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
  *l = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l)
/* Mengembalikan true jika list kosong */
{
  return l == NULL;
}

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
{
  if(0 <= idx && idx < length(l)){
    Address p = l;
    for(int i = 0; i < idx; i++){
      p=p->next;
    }
    return p->info;
  }else{
    //printf("Indeks tidak valid!\n");
    return ELMT_UNDEF;
  }
}

void setElmt(List *l, int idx, ElType val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
  if(0 <= idx && idx < length(*l)){
    Address temp = *l;
    for(int i = 0; i < idx; i++){
      temp = temp->next;
    }
    temp->info = val;
  }else{
    //printf("Indeks tidak valid!\n");
  }
}

int indexOf(List l, ElType val)
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
{
  int i;
  Address p = l;
  for(i = 0; p!=NULL && p->info != val; i++){
    p = p->next;
  }
  if(p == NULL)  return IDX_UNDEF;
  return i;
}
/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val)
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val. */
{
  Address new = newNode(val);
  if(new!= NULL){
    new->next = *l;
    *l = new;
  }
}

void insertLast(List *l, ElType val){
  Address new = newNode(val);
  if(new == NULL)  return;
  if(*l == NULL){
    *l = new;
  }else{
    Address temp = *l;
    while(temp->next != NULL){
      temp = temp->next;
    }
    temp->next = new;
  }
}
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val. */

void insertAt(List *l, ElType val, int idx){
  if(idx < 0 || idx > length(*l)) return;
  
  Address new = newNode(val);
  if(new == NULL) return;
  
  if(idx == 0){
    new->next = *l;
    *l = new;
  } else {
    Address temp = *l;
    for(int i = 0; i < idx - 1; i++){
      temp = temp->next;
    }
    new->next = temp->next;
    temp->next = new;
  }
}
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val. */

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val)
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen pertama di-dealokasi */
{
  if(*l == NULL) return;
  
  Address temp = *l;
  *val = temp->info;   
  *l = temp->next;     
  free(temp);          
}

void deleteLast(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen terakhir di-dealokasi */
{
  if(*l == NULL) return;
  
  Address temp = *l;
  if(temp->next == NULL){  // hanya 1 elemen
    *val = temp->info;
    free(temp);
    *l = NULL;
  } else {
    while(temp->next->next != NULL){
      temp = temp->next;
    }
    Address last = temp->next;
    *val = last->info;
    temp->next = NULL;
    free(last);
  }
}

void deleteAt(List *l, int idx, ElType *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
  if(idx < 0 || idx >= length(*l)) return;
  
  if(idx == 0){
    deleteFirst(l, val);
  } else {
    Address temp = *l;
    for(int i = 0; i < idx - 1; i++){
      temp = temp->next;
    }
    Address del = temp->next;
    *val = del->info;
    temp->next = del->next;
    free(del);
  }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
  printf("[");
  while(l != NULL){
    printf("%d", l->info);
    l = l->next;
    if(l != NULL){
      printf(",");
    }
  }
  printf("]");
}

int length(List l)
/* Mengembalikan banyaknya elemen list; mengembalikan 0 jika list kosong */
{
  int i;
  Address p = l;
  for(i = 0; p != NULL; i++){
    p = p->next;
  } 
  return i;
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2)
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
{
  List l3;
  CreateList(&l3);
  int val;
  for(int i = 0; i < length(l1);i++){
    val = getElmt(l1, i);
    insertLast(&l3, val);
  }
  for(int i = 0; i < length(l2);i++){
    val = getElmt(l2, i);
    insertLast(&l3, val);
  }
  return l3;
}
