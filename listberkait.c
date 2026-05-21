/* File : listberkait.h */
/* ADT list berkait dengan representasi fisik pointer */
/* Representasi address dengan pointer */
/* ElType adalah integer */
#include <stdlib.h>
#include <stdio.h>
#include "listberkait.h"
#include "boolean.h"

#define IDX_UNDEF (-1)

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
    new.info = val;
    new.next = NULL;
    printf("Alokasi berhasil! Node sudah dibuat!\n");
    return new;
  }
  printf("Alokasi gagal!\n");
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
      p=p.next;
    }
    return p.info;
  }else{
    printf("Indeks tidak valid!\n");
  }
}

void setElmt(List *l, int idx, ElType val)
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
{
  if(0 <= idx && idx < length(l)){
    for(int i = 0; i < idx; i++){
      l=l.next;
    }
    l.info = val;
  }else{
    printf("Indeks tidak valid!\n");
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
  for(i = 0; p != val; i++){
    p = p.next;
  } 
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
  if(l == NULL){
    *l = new;
  }else{
    new.next = l.next;
    *l = new;
  }
}

void insertLast(List *l, ElType val){
  int i;
  Address new = newNode(val);
  for(i = 0; l != NULL; i++){
    l = l.next;
  } 
  *l.next = new;
}
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val. */

void insertAt(List *l, ElType val, int idx){
  int i;
  Address new = newNode(val);
  for(i = 0; l != NULL && i < idx; i++){
    l = l.next;
  } 
  *l.next = new;
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
  if(!isEmpty(*l)){
    *l = l.next;
    *val = l.info;
    free(l.info);
    l.info = NULL;
  }
}

void deleteLast(List *l, ElType *val)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada val */
/*      dan alamat elemen terakhir di-dealokasi */
{
  Address p = *l;
  while(p.next != NULL){
    p = p.next;
  }
  free(p);
  p = NULL;
}

void deleteAt(List *l, int idx, ElType *val)
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
{
  Address p =*l;
  if(0 <= idx <= length(*l)){
    for(int i = 0; i < idx;i++){
      p = p.next;
    }
    p.info = *val;
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
    l = l.next;
    printf("%d,", l.info);
  }
  printf("]\n");
}

int length(List l)
/* Mengembalikan banyaknya elemen list; mengembalikan 0 jika list kosong */
{
  int i;
  Address p = l;
  for(i = 0; p != NULL; i++){
    p = p.next;
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
    deleteFirst(&l1, &val);
    insertLast(&l3, val);
  }
  for(int i = 0; i < length(l2);i++){
    deleteFirst(&l2, &val);
    insertLast(&l3, val);
  }
  return l3;
}
