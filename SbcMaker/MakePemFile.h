#ifndef MAKE_PEM_FILE_H
#define MAKE_PEM_FILE_H

#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h>
#include <openssl/objects.h>
#include <openssl/ssl.h>
#include <QString>

class CPemMaker
{
    FILE *fp;
    EVP_PKEY *pkey = nullptr;
    X509 *cert = nullptr;
    STACK_OF(X509) *ca = nullptr;
    PKCS12 *p12 = nullptr;

public:
    CPemMaker();
    ~CPemMaker();
    int makePemFile(QString *p12Path, QString *passwd, QString *number);
};

#endif // MAKE_PEM_FILE_H
