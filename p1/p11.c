#include <stdio.h>
#include <math.h>
#include <time.h> // Für Zeitmessung

// Funktion zur Berechnung des GCD (Größter gemeinsamer Teiler)
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Funktion zur modularen Exponentiation
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

// Hauptprogramm
int main() {
    clock_t start, end; // Variablen für Zeitmessung
    double cpu_time_used;

    // Schritt 1: Schlüsselerzeugung
    start = clock();
    int p = 61, q = 53; // Zwei Primzahlen
    int N = p * q;      // Produkt der Primzahlen
    int phi = (p - 1) * (q - 1); // Totient von N

    int e = 17; // Öffentlicher Exponent
    while (gcd(e, phi) != 1) {
        e++;
    }

    int d = 1;
    while ((e * d) % phi != 1) {
        d++;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Schlüsselerzeugung abgeschlossen in %f Sekunden.\n", cpu_time_used);

    printf("Öffentlicher Schlüssel: (e=%d, N=%d)\n", e, N);
    printf("Privater Schlüssel: (d=%d, N=%d)\n", d, N);

    // Schritt 2: Verschlüsselung
    start = clock();
    int m = 42; // Geheime Nachricht
    int c = mod_exp(m, e, N); // Verschlüsseln
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Originale Nachricht: %d\n", m);
    printf("Verschlüsselte Nachricht: %d\n", c);
    printf("Verschlüsselung abgeschlossen in %f Sekunden.\n", cpu_time_used);

    // Schritt 3: Entschlüsselung
    start = clock();
    int decrypted = mod_exp(c, d, N); // Entschlüsseln
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Entschlüsselte Nachricht: %d\n", decrypted);
    printf("Entschlüsselung abgeschlossen in %f Sekunden.\n", cpu_time_used);

    return 0;
}

