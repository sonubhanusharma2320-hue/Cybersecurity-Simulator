
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX 256
#define LOG_SIZE 50

char logs[LOG_SIZE][MAX];
int logCount = 0;

// Colors for terminal
#define RESET "\033[0m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"

void readInput(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void addLog(const char *message) {
    if (logCount < LOG_SIZE) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        snprintf(logs[logCount], MAX,
                 "%02d:%02d:%02d - %s",
                 t->tm_hour, t->tm_min, t->tm_sec, message);
        logCount++;
    }
}

void header() {
    printf(CYAN);
    printf("\n");
    printf("========================================\n");
    printf("          CYBERSHIELD v1.0\n");
    printf("       CYBERSECURITY TERMINAL\n");
    printf("========================================\n");
    printf(RESET);
}

void passwordChecker() {
    char password[MAX];
    int upper = 0, lower = 0;
    int digit = 0, special = 0;

    printf("\nEnter password to check: ");
    readInput(password, MAX);

    int len = strlen(password);

    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper((unsigned char)password[i]))
            upper = 1;
        else if (islower((unsigned char)password[i]))
            lower = 1;
        else if (isdigit((unsigned char)password[i]))
            digit = 1;
        else
            special = 1;
    }

    int score = 0;

    if (len >= 8) score++;
    if (len >= 12) score++;
    if (upper) score++;
    if (lower) score++;
    if (digit) score++;
    if (special) score++;

    printf("\nPassword Analysis:\n");
    printf("Length: %d characters\n", len);
    printf("Uppercase: %s\n", upper ? "YES" : "NO");
    printf("Lowercase: %s\n", lower ? "YES" : "NO");
    printf("Numbers: %s\n", digit ? "YES" : "NO");
    printf("Special characters: %s\n", special ? "YES" : "NO");

    printf("\nStrength: ");

    if (len < 8 || score <= 2)
        printf(RED "WEAK\n" RESET);
    else if (score <= 4)
        printf(YELLOW "MEDIUM\n" RESET);
    else
        printf(GREEN "STRONG\n" RESET);

    addLog("Password strength checked.");
}

void loginSimulator() {
    char username[MAX];
    char password[MAX];

    int attempts = 0;
    int success = 0;

    printf("\n========== LOGIN SECURITY ==========\n");
    printf("Demo username: admin\n");
    printf("Demo password: Cyber@123\n");
    printf("Maximum attempts: 3\n");

    while (attempts < 3) {
        printf("\nUsername: ");
        readInput(username, MAX);

        printf("Password: ");
        readInput(password, MAX);

        if (strcmp(username, "admin") == 0 &&
            strcmp(password, "Cyber@123") == 0) {

            printf(GREEN "\nACCESS GRANTED!\n" RESET);
            success = 1;
            addLog("Successful demo login.");
            break;

        } else {
            attempts++;
            printf(RED "\nACCESS DENIED!\n" RESET);
            printf("Attempts remaining: %d\n", 3 - attempts);
            addLog("Failed demo login attempt.");
        }
    }

    if (!success) {
        printf(RED "\nACCOUNT LOCKED!\n" RESET);
        addLog("Demo account locked after 3 failed attempts.");
    }
}

void caesarCipher() {
    char text[MAX];
    int shift, choice;

    printf("\n========== CAESAR CIPHER ==========\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Choose: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (choice != 1 && choice != 2) {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter text: ");
    readInput(text, MAX);

    printf("Enter shift value (0-25): ");
    if (scanf("%d", &shift) != 1) {
        printf("Invalid shift.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    shift = ((shift % 26) + 26) % 26;

    if (choice == 2)
        shift = (26 - shift) % 26;

    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = 'A' + (text[i] - 'A' + shift) % 26;

        else if (text[i] >= 'a' && text[i] <= 'z')
            text[i] = 'a' + (text[i] - 'a' + shift) % 26;
    }

    printf(GREEN "\nResult: %s\n" RESET, text);
    addLog(choice == 1 ? "Text encrypted." : "Text decrypted.");
}

unsigned int calculateHash(const char *text) {
    unsigned int hash = 2166136261u;

    while (*text) {
        hash ^= (unsigned char)*text++;
        hash *= 16777619u;
    }

    return hash;
}

void integrityChecker() {
    char text[MAX];

    printf("\n========== TEXT INTEGRITY CHECKER ==========\n");
    printf("Enter text to generate its fingerprint: ");
    readInput(text, MAX);

    unsigned int hash = calculateHash(text);

    printf(GREEN "\nText fingerprint: %08X\n" RESET, hash);
    printf("Save this fingerprint and compare it later.\n");

    addLog("Text integrity fingerprint generated.");
}

void showLogs() {
    printf("\n========== SECURITY ACTIVITY LOGS ==========\n");

    if (logCount == 0) {
        printf("No activity recorded yet.\n");
        return;
    }

    for (int i = 0; i < logCount; i++) {
        printf("%d. %s\n", i + 1, logs[i]);
    }
}

void menu() {
    int choice;

    while (1) {
        header();

        printf(GREEN);
        printf("\n[1] Password Strength Checker\n");
        printf("[2] Login Security Simulator\n");
        printf("[3] Caesar Cipher Encryption\n");
        printf("[4] Text Integrity Checker\n");
        printf("[5] Security Activity Logs\n");
        printf("[0] Exit\n");
        printf(RESET);

        printf("\nSelect an option: ");

        if (scanf("%d", &choice) != 1) {
            printf(RED "\nInvalid input! Enter a number.\n" RESET);
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (choice) {
            case 1:
                passwordChecker();
                break;

            case 2:
                loginSimulator();
                break;

            case 3:
                caesarCipher();
                break;

            case 4:
                integrityChecker();
                break;

            case 5:
                showLogs();
                break;

            case 0:
                printf(GREEN "\nThank you for using CyberShield!\n" RESET);
                printf("Stay safe. Stay secure.\n");
                return;

            default:
                printf(RED "\nInvalid option! Try again.\n" RESET);
        }

        printf("\nPress Enter to continue...");
        getchar();
    }
}

int main() {
    menu();
    return 0;
}
