#include "keys.h"

#include <cryptopp/integer.h>

using namespace CryptoPP;

CPrivateKey::CPrivateKey()
{
    GenerateKey();
}

CPrivateKey::CPrivateKey(const std::vector<uint8_t>& privKeyBytes)
{
    LoadKey(privKeyBytes);
}

void CPrivateKey::GenerateKey()
{
    CryptoPP::AutoSeededRandomPool rng;
    mPrivKey.Initialize(
        rng,
        ASN1::secp256k1()
    );
}

void CPrivateKey::LoadKey(const std::vector<uint8_t>& privKeyBytes)
{
    Integer x(privKeyBytes.data(), privKeyBytes.size());

    mPrivKey.Initialize(
        ASN1::secp256k1(),
        x
    );
}

std::vector<uint8_t> CPrivateKey::GetPrivateKeyBytes() const
{
    const Integer& x = mPrivKey.GetPrivateExponent();

    std::vector<uint8_t> out(32);
    x.Encode(out.data(), out.size());

    return out;
}

std::vector<uint8_t> CPrivateKey::GetPublicKeyBytes(bool compressed) const
{
    ECDSA<ECP, SHA256>::PublicKey pubKey;
    mPrivKey.MakePublicKey(pubKey);

    const ECP::Point& Q = pubKey.GetPublicElement();

    std::vector<uint8_t> out;

    if (compressed)
    {
        out.resize(33);
        out[0] = Q.y.IsOdd() ? 0x03 : 0x02;
        Q.x.Encode(out.data() + 1, 32);
    }
    else
    {
        out.resize(65);
        out[0] = 0x04;
        Q.x.Encode(out.data() + 1, 32);
        Q.y.Encode(out.data() + 33, 32);
    }

    return out;
}
