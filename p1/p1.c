#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to calculate modular exponentiation
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to find modular multiplicative inverse
int mod_inverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1) {
            return d;
        }
    }
    return -1; // No modular inverse found
}

int main() {
    // Step 1: Key generation
    int p = 61, q = 53; // Example primes
    int N = p * q;
    int phi = (p - 1) * (q - 1);

    // Choose e
    int e = 17; // e must be coprime to phi and 1 < e < phi
    while (gcd(e, phi) != 1) {
        e++;
    }

    // Calculate d (modular multiplicative inverse of e mod phi)
    int d = mod_inverse(e, phi);
    if (d == -1) {
        printf("Error: No modular inverse found.\n");
        return 1;
    }

    printf("Public Key: (e=%d, N=%d)\n", e, N);
    printf("Private Key: (d=%d, N=%d)\n", d, N);

    // Step 2: Encryption
    int m = 42; // Example message (must be less than N and coprime to N)
    int c = mod_exp(m, e, N);
    printf("Original Message: %d\n", m);
    printf("Encrypted Message: %d\n", c);

    // Step 3: Decryption
    int decrypted = mod_exp(c, d, N);
    printf("Decrypted Message: %d\n", decrypted);

    // Step 4: Breaking the encryption (Factorization)
    int guessed_p, guessed_q;
    for (guessed_p = 2; guessed_p < sqrt(N) + 1; guessed_p++) {
        if (N % guessed_p == 0) {
            guessed_q = N / guessed_p;
            break;
        }
    }

    printf("Factorization: p=%d, q=%d\n", guessed_p, guessed_q);

    // Step 5: Compare times
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    c = mod_exp(m, e, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Encryption Time: %f seconds\n", cpu_time_used);

    start = clock();
    decrypted = mod_exp(c, d, N);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Decryption Time: %f seconds\n", cpu_time_used);

    start = clock();
    for (guessed_p = 2; guessed_p < sqrt(N) + 1; guessed_p++) {
        if (N % guessed_p == 0) {
            guessed_q = N / guessed_p;
            break;
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Breaking Encryption Time: %f seconds\n", cpu_time_used);

    return 0;
}
