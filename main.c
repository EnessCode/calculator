#include <stdio.h>
#include <string.h>
#include <stdlib.h> //Sayýsal dönüþümler için
#include <math.h> //Standart Matematik Kütüphanesi
#include <time.h> // Tarih-Saat eklemek için

//Açýklama eklendi
//Kütüphane eklendi
//Geçmiþ iþlemler eklendi
//Tarih saat eklendi

int main() {
    int choice;
    double num1, num2, result;
    FILE *file; // Geçmiþ iþlemleri kaydedeceðimiz dosya pointer'ý
	time_t now; // Þu anki zamaný (timestamp olarak) tutmak için deðiþken.
	char *timestamp; // time_t türündeki zaman bilgisini okunabilir string formata çevirmek için kullanýlacak karakter dizisi.

    while (1) { // Sonsuz döngü - kullanýcý çýkmak isteyene kadar çalýþýr
        // Menü
        printf("\n--- Simple Calculator ---\n");
        printf("1. Addition (+)\n");
        printf("2. Subtraction (-)\n");
        printf("3. Multiplication (*)\n");
        printf("4. Division (/)\n");
        printf("5. Exit\n");
        printf("6. Show History\n");
        printf("7. Clear History\n"); 
        printf("Choose an operation (1-6): ");

        // Kullanýcýnýn geçerli bir seçim yapýp yapmadýðýný kontrol ediyoruz
        if (scanf("%d", &choice) != 1) {
		printf("Choose an operation (1-7): ");
            while (getchar() != '\n');
            continue;
        }

		// Çýkýþ
        if (choice == 5) {
            printf("Exiting the calculator. Goodbye!\n");
            break;
        }

		// Geçmiþ iþlemleri göster
        if (choice == 6) {
            file = fopen("history.txt", "r"); //read mode
            if (file == NULL) {
                printf("No history found.\n");
            } else {
                printf("\n--- Calculation History ---\n");
                char ch;
                while ((ch = fgetc(file)) != EOF) {
                    putchar(ch); // Dosyadaki her karakteri ekrana yaz
                }
                fclose(file);
            }
            continue;
        }
        
        //Geçmiþi temizle
        if (choice == 7) {
            file = fopen("history.txt", "w"); //write mode
            if (file != NULL) {
                fclose(file);
                printf("History cleared successfully.\n");
            } else {
                printf("Failed to clear history.\n");
            }
            continue;
        }
        
        // Kullanýcýdan iki sayý alýnýr, geçerli girip girmediði kontrol edilir
        printf("Enter first number: ");
        if (scanf("%lf", &num1) != 1) {
            printf("Invalid number input.\n");
            while (getchar() != '\n');
            continue;
        }

        printf("Enter second number: ");
        if (scanf("%lf", &num2) != 1) {
            printf("Invalid number input.\n");
            while (getchar() != '\n');
            continue;
        }

        // Dosyaya ekleme modunda açýlýr, her iþlem burada saklanýr
        file = fopen("history.txt", "a"); //append mode
        
        //Ýþlem zamaný alýnýyor
        now = time(NULL);
        timestamp = ctime(&now);
        if (file && timestamp) {
            timestamp[strcspn(timestamp, "\n")] = 0; // Satýr sonunu sil
        }
        
        // Kullanýcýnýn seçimine göre iþlem yapýlýr
        switch (choice) {
            case 1:
                result = num1 + num2;
                printf("Result: %.2lf + %.2lf = %.2lf\n", num1, num2, result);
                if (file) fprintf(file, "[%s] %.2lf + %.2lf = %.2lf\n", timestamp, num1, num2, result);
                break;
            case 2:
                result = num1 - num2;
                printf("Result: %.2lf - %.2lf = %.2lf\n", num1, num2, result);
                if (file) fprintf(file, "[%s] %.2lf - %.2lf = %.2lf\n", timestamp, num1, num2, result);
                break;
            case 3:
                result = num1 * num2;
                printf("Result: %.2lf * %.2lf = %.2lf\n", num1, num2, result);
                if (file) fprintf(file, "[%s] %.2lf * %.2lf = %.2lf\n", timestamp, num1, num2, result);
                break;
            case 4:
                if (num2 == 0) { // Sýfýra bölme kontrolü
                    printf("Error: Division by zero is not allowed.\n");
                    if (file) fprintf(file, "[%s] %.2lf / %.2lf = Error (division by zero)\n", timestamp, num1, num2);
                } else {
                    result = num1 / num2;
                    printf("Result: %.2lf / %.2lf = %.2lf\n", num1, num2, result);
                    if (file) fprintf(file, "[%s] %.2lf / %.2lf = %.2lf\n", timestamp, num1, num2, result);
                }
                break;
            default:
                printf("Invalid choice. Please choose a number between 1 and 6.\n");
        }

        if (file) fclose(file); // Her iþlem sonrasý dosya kapatýlýr
    }

    return 0;
}

