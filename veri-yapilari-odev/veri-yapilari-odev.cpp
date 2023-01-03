#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


#define MAX_BUSES 5
#define MAX_PASSENGERS_PER_BUS 5

// Yolcu bilgilerini tutan yapı
struct passenger {
    char name[20];
    char surname[20];
    int seat_number;
};

// Otobüs bilgilerini tutan yapı
struct bus {
    int bus_number;
    struct passenger passengers[MAX_PASSENGERS_PER_BUS];
    int passenger_count;
};

// Otobüsleri tutan dizi
struct bus buses[MAX_BUSES];

// Otobüslerdeki yolcu sayısını tutan değişken
int bus_count = 0;

// Otobüs ekleme fonksiyonu
void add_bus() {
    if (bus_count == MAX_BUSES) {
        printf("Tüm otobüsler dolu!\n");
        return;
    }
    int bus_number = bus_count + 1;
    struct bus new_bus = { bus_number, {}, 0 };
    buses[bus_count] = new_bus;
    bus_count++;
    printf("Otobüs %d eklendi.\n", bus_number);
}

// Yolcu ekleme fonksiyonu
void add_passenger(char* name, char* surname) {
    while (bus_count == 0 || buses[bus_count - 1].passenger_count == MAX_PASSENGERS_PER_BUS) {
        add_bus();
    }
    int last_bus_index = bus_count - 1;
    struct bus* last_bus = &buses[last_bus_index];
    int seat_number = last_bus->passenger_count + 1;
    struct passenger new_passenger = { 0 };
    strcpy(new_passenger.name, name);
    strcpy(new_passenger.surname, surname);
    new_passenger.seat_number = seat_number;
    last_bus->passengers[last_bus->passenger_count] = new_passenger;
    last_bus->passenger_count++;
    printf("Yolcu eklendi: %s %s, Koltuk: %d, Otobüs: %d\n", name, surname, seat_number, last_bus->bus_number);
}


// Otobüslerdeki yolcuları listeleme fonksiyonu
void list_passengers() {
    for (int i = 0; i < bus_count; i++) {
        struct bus* current_bus = &buses[i];
        printf("******************* Otobüs %d *******************\n", current_bus->bus_number);
        printf("Koltuk No \t Ad \t Soyad\n");
        for (int j = 0; j < current_bus->passenger_count; j++) {
            struct passenger* current_passenger = &current_bus->passengers[j];
            printf("%d \t\t %s\t %s \n", current_passenger->seat_number, current_passenger->name, current_passenger->surname);


        }
    }
}

int main() {

    setlocale(LC_ALL, "Turkish");

    int secim;
    int exit = 0;
    while (!exit) {
        printf("\n1 - Yolcu ekle\n");
        printf("2 - Listeyi yazdır\n");
        printf("3 - Çıkış\n");
        printf("Seçiminiz: ");
        scanf("%d", &secim);
        char name[20];
        char surname[20];
        switch (secim) {
        case 1:
            printf("Yolcu adı: ");
            scanf("%s", name);
            printf("Yolcu soyadı: ");
            scanf("%s", surname);
            add_passenger(name, surname);
            break;

        case 2:
            list_passengers();
            break;

        case 3:
            exit = 1;
            break;

        default:
            printf("Geçersiz seçim.\n");
        }
    }
    return 0;
}