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
    EVP_PKEY *pkey = Q_NULLPTR;
    X509 *cert = Q_NULLPTR;
    STACK_OF(X509) *ca = Q_NULLPTR;
    PKCS12 *p12 = Q_NULLPTR;

public:
    CPemMaker();
    ~CPemMaker();
    int makePemFile(const QString p12Path, const QString passwd, QString *number);
};

#endif // MAKE_PEM_FILE_H
