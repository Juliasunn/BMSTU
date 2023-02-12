#ifndef JWT_ENCRYPT_ALG_H
#define JWT_ENCRYPT_ALG_H
#include <openssl/x509.h>
#include <openssl/hmac.h>
//#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
extern "C" {
#include <openssl/sha.h>
}
std::string base64_decode(const std::string & in);
std::string base64_encode(const std::string & in);
void
hmac_sha256(
    const unsigned char *text,      /* pointer to data stream        */
    int                 text_len,   /* length of data stream         */
    const unsigned char *key,       /* pointer to authentication key */
    int                 key_len,    /* length of authentication key  */
    unsigned char                *digest)    /* caller digest to be filled in */;




#endif // JWT_ENCRYPT_ALG_H
