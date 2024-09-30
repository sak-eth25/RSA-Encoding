#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll modular_inv(ll n, ll mod) {
    ll t = 0, new_t = 1;
    ll r = mod, new_r = n;
    while (new_r != 0) {
        ll quotient = r / new_r;
        tie(t, new_t) = make_tuple(new_t, t - quotient * new_t);
        tie(r, new_r) = make_tuple(new_r, r - quotient * new_r);
    }
    if (r > 1) return -1; // Inverse doesn't exist
    if (t < 0) t += mod;
    return t;
}

ll modular_power(ll n, ll p, ll mod) {
    ll result = 1;
    n = n % mod; // Update n if it is more than or equal to mod
    while (p > 0) {
        if (p % 2 == 1) // If p is odd, multiply n with result
            result = (result * n) % mod;
        p = p >> 1; // p = p/2
        n = (n * n) % mod; // Change n to n^2
    }
    return result;
}

void encrypt(string str, ll e, ll n, ofstream &fp) {
    string newstring = "";
    for (int i = 0; i < str.length(); ++i) {
        int asc = str[i];
        // Encrypt the value asc
        ll encrypted = modular_power(asc, e, n);
        fp << encrypted;
        if (i < str.length() - 1) fp << '.';
    }
    fp << ' ';
}

int main() {
    const ll lim = 5e8;
    ll p, q;
    // Set p & q to be two large primes
    srand(time(NULL));
    p = rand() % lim;
    while (!isPrime(p)) p++;
    q = rand() % lim;
    while (!isPrime(q)) q++;

    // Fill in the variables, n & phi_n
    ll n = p * q;
    ll phi_n = (p - 1) * (q - 1);
    ll e = 65537; // Common choice for e
    ll d = modular_inv(e, phi_n); // Find out decryption key

    // Storing the private key 'd'
    ofstream priv("private.txt", ios::out);
    priv << d << endl;
    priv.close();
    
    // Input and output files
    ifstream fp("inputfile.txt", ios::in);
    ofstream fp2("outputfile.txt", ios::out);
    string str = "";
    fp2 << n << ' ' << e << endl; // Public keys: n & e
    while (fp >> str) {
        encrypt(str, e, n, fp2);
    }
    fp.close();
    fp2.close();
    return 0;
}
