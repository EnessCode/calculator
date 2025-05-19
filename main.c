#include <stdio.h>
#include <string.h>
#include <stdlib.h> //Say�sal d�n���mler i�in
#include <math.h> //Standart Matematik K�t�phanesi
#include <time.h> // Tarih-Saat eklemek i�in

//A��klama eklendi
//K�t�phane eklendi
//Ge�mi� i�lemler eklendi
//Tarih saat eklendi

int main() {
    int choice;
    double num1, num2, result;
    FILE *file; // Ge�mi� i�lemleri kaydedece�imiz dosya pointer'�
	time_t now; // �u anki zaman� (timestamp olarak) tutmak i�in de�i�ken.
	char *timestamp; // time_t t�r�ndeki zaman bilgisini okunabilir string formata �evirmek i�in kullan�lacak karakter dizisi.

    while (1) { // Sonsuz d�ng� - kullan�c� ��kmak isteyene kadar �al���r
        // Men�
        printf("\n--- Simple Calculator ---\n");
        printf("1. Addition (+)\n");
        printf("2. Subtraction (-)\n");
        printf("3. Multiplication (*)\n");
        printf("4. Division (/)\n");
        printf("5. Exit\n");
        printf("6. Show History\n");
        printf("7. Clear History\n"); 
        printf("Choose an operation (1-6): ");

        // Kullan�c�n�n ge�erli bir se�im yap�p yapmad���n� kontrol ediyoruz
        if (scanf("%d", &choice) != 1) {
		printf("Choose an operation (1-7): ");
            while (getchar() != '\n');
            continue;
        }

		// ��k��
        if (choice == 5) {
            printf("Exiting the calculator. Goodbye!\n");
            break;
        }

		// Ge�mi� i�lemleri g�ster
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
        
        //Ge�mi�i temizle
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
        
        // Kullan�c�dan iki say� al�n�r, ge�erli girip girmedi�i kontrol edilir
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

        // Dosyaya ekleme modunda a��l�r, her i�lem burada saklan�r
        file = fopen("history.txt", "a"); //append mode
        
        //��lem zaman� al�n�yor
        now = time(NULL);
        timestamp = ctime(&now);
        if (file && timestamp) {
            timestamp[strcspn(timestamp, "\n")] = 0; // Sat�r sonunu sil
        }
        
        // Kullan�c�n�n se�imine g�re i�lem yap�l�r
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
                if (num2 == 0) { // S�f�ra b�lme kontrol�
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

        if (file) fclose(file); // Her i�lem sonras� dosya kapat�l�r
    }

    return 0;
}

