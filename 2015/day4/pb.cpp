#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <sstream>
#include <string>

std::string md5(const std::string& input) {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    const EVP_MD* algo = EVP_md5();

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len = 0;

    EVP_DigestInit_ex(ctx, algo, nullptr);
    EVP_DigestUpdate(ctx, input.data(), input.size());
    EVP_DigestFinal_ex(ctx, hash, &len);
    EVP_MD_CTX_free(ctx);

    std::ostringstream out;
    for (unsigned int i = 0; i < len; ++i) {
        out << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return out.str();
}

int main() {
    std::string mess = "bgvyzdsv";
    auto f = [](const std::string& s) {
        if (s.size() < 6) return false;
        for (int i = 0; i < 6; i++) {
            if (s[i] != '0') return false;
        }
        return true;
    };

    int answer = 1;
    while (true) {
        std::string input = mess + std::to_string(answer);
        std::string hash = md5(input);

        if (f(hash)) {
            break;
        }

        answer++;
    }

    std::cout << answer << std::endl;

    return 0;
}

