/* File: main.c */
/* Program untuk menguji ADT List Berkait */

#include <stdio.h>
#include "listberkait.h"
#include "boolean.h"

int main() {
    List myList;
    ElType val;
    int choice, idx, position;
    
    // Create list kosong
    CreateList(&myList);
    
    printf("========================================\n");
    printf("  PROGRAM UJI ADT LIST BERKAIT\n");
    printf("========================================\n\n");
    
    // Menu interaktif
    do {
        printf("\n========== MENU ==========\n");
        printf("1. Insert First\n");
        printf("2. Insert Last\n");
        printf("3. Insert At\n");
        printf("4. Delete First\n");
        printf("5. Delete Last\n");
        printf("6. Delete At\n");
        printf("7. Display List\n");
        printf("8. Get Element at Index\n");
        printf("9. Set Element at Index\n");
        printf("10. Find Index of Value\n");
        printf("11. Get List Length\n");
        printf("12. Check if Empty\n");
        printf("13. Clear List (Delete All)\n");
        printf("0. Exit\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: // Insert First
                printf("Masukkan nilai: ");
                scanf("%d", &val);
                insertFirst(&myList, val);
                printf("Nilai %d berhasil ditambahkan di awal!\n", val);
                break;
                
            case 2: // Insert Last
                printf("Masukkan nilai: ");
                scanf("%d", &val);
                insertLast(&myList, val);
                printf("Nilai %d berhasil ditambahkan di akhir!\n", val);
                break;
                
            case 3: // Insert At
                printf("Masukkan nilai: ");
                scanf("%d", &val);
                printf("Masukkan posisi indeks: ");
                scanf("%d", &idx);
                insertAt(&myList, val, idx);
                printf("Nilai %d berhasil ditambahkan di indeks %d!\n", val, idx);
                break;
                
            case 4: // Delete First
                if(!isEmpty(myList)) {
                    deleteFirst(&myList, &val);
                    printf("Nilai %d berhasil dihapus dari awal!\n", val);
                } else {
                    printf("List kosong! Tidak ada yang bisa dihapus!\n");
                }
                break;
                
            case 5: // Delete Last
                if(!isEmpty(myList)) {
                    deleteLast(&myList, &val);
                    printf("Nilai %d berhasil dihapus dari akhir!\n", val);
                } else {
                    printf("List kosong! Tidak ada yang bisa dihapus!\n");
                }
                break;
                
            case 6: // Delete At
                if(!isEmpty(myList)) {
                    printf("Masukkan posisi indeks yang akan dihapus: ");
                    scanf("%d", &idx);
                    if(idx >= 0 && idx < length(myList)) {
                        deleteAt(&myList, idx, &val);
                        printf("Nilai %d berhasil dihapus dari indeks %d!\n", val, idx);
                    } else {
                        printf("Indeks tidak valid!\n");
                    }
                } else {
                    printf("List kosong! Tidak ada yang bisa dihapus!\n");
                }
                break;
                
            case 7: // Display List
                printf("Isi List: ");
                displayList(myList);
                break;
                
            case 8: // Get Element at Index
                if(!isEmpty(myList)) {
                    printf("Masukkan indeks yang ingin dilihat: ");
                    scanf("%d", &idx);
                    if(idx >= 0 && idx < length(myList)) {
                        val = getElmt(myList, idx);
                        printf("Nilai pada indeks %d adalah: %d\n", idx, val);
                    } else {
                        printf("Indeks tidak valid!\n");
                    }
                } else {
                    printf("List kosong!\n");
                }
                break;
                
            case 9: // Set Element at Index
                if(!isEmpty(myList)) {
                    printf("Masukkan indeks yang akan diubah: ");
                    scanf("%d", &idx);
                    if(idx >= 0 && idx < length(myList)) {
                        printf("Masukkan nilai baru: ");
                        scanf("%d", &val);
                        setElmt(&myList, idx, val);
                        printf("Indeks %d berhasil diubah menjadi %d!\n", idx, val);
                    } else {
                        printf("Indeks tidak valid!\n");
                    }
                } else {
                    printf("List kosong!\n");
                }
                break;
                
            case 10: // Find Index of Value
                if(!isEmpty(myList)) {
                    printf("Masukkan nilai yang dicari: ");
                    scanf("%d", &val);
                    position = indexOf(myList, val);
                    if(position != IDX_UNDEF) {
                        printf("Nilai %d ditemukan pada indeks: %d\n", val, position);
                    } else {
                        printf("Nilai %d tidak ditemukan dalam list!\n", val);
                    }
                } else {
                    printf("List kosong!\n");
                }
                break;
                
            case 11: // Get List Length
                printf("Panjang list: %d\n", length(myList));
                break;
                
            case 12: // Check if Empty
                if(isEmpty(myList)) {
                    printf("List kosong!\n");
                } else {
                    printf("List tidak kosong!\n");
                }
                break;
                
            case 13: // Clear List
                while(!isEmpty(myList)) {
                    deleteFirst(&myList, &val);
                }
                printf("List berhasil dikosongkan!\n");
                break;
                
            case 0: // Exit
                printf("Terima kasih! Program selesai.\n");
                // Bersihkan memory sebelum keluar
                while(!isEmpty(myList)) {
                    deleteFirst(&myList, &val);
                }
                break;
                
            default:
                printf("Pilihan tidak valid!\n");
                break;
        }
    } while(choice != 0);
    
    return 0;
}
