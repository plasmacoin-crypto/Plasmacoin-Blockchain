//
// FILENAME: rsautil.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for rsautil.hpp
// CREATED: 2022-03-29 @ 3:01 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "rsautil.hpp"

// Generate public and private RSA keys for signing transactions
std::tuple<CryptoPP::InvertibleRSAFunction, RSA::PublicKey, RSA::PrivateKey> rsautil::generateKeys() noexcept(false) {
	CryptoPP::AutoSeededRandomPool rng; // Random number generator
	CryptoPP::InvertibleRSAFunction params;

	params.GenerateRandomWithKeySize(rng, 3072);

	// Generate an RSA public-private key pair
	RSA::PrivateKey privateKey(params);
	RSA::PublicKey publicKey(params);

	// Validate the private key
	if (!privateKey.Validate(rng, 3)) {
		throw std::runtime_error("Private key validation failed. Aborting.");
	}

	// Validate the private key
	if (!publicKey.Validate(rng, 3)) {
		throw std::runtime_error("Public key validation failed. Aborting.");
	}

	return std::make_tuple(params, publicKey, privateKey);
}

// Sign a transaction with the sender's private key
void rsautil::sign(Transaction& transaction, const RSA::PublicKey& publicKey, const RSA::PrivateKey& privateKey) noexcept(false) {
	CryptoPP::AutoSeededRandomPool rng;
	string message = transaction.m_Content;

	CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

	size_t length = signer.MaxSignatureLength();
	CryptoPP::SecByteBlock signature(length);

	length = signer.SignMessage(rng, (const byte*)message.c_str(), message.size(), signature);
	signature.resize(length);

	transaction.m_Signature = Signature {signature, publicKey, length};
	transaction.m_SignTime = utility::getUnixEpoch();
}

// Sign a transaction receipt with the sender's private key.
void rsautil::sign(Receipt& receipt, const RSA::PublicKey& publicKey, const RSA::PrivateKey& privateKey) noexcept(false) {
	CryptoPP::AutoSeededRandomPool rng;
	string message = receipt.m_Hash;

	CryptoPP::RSASSA_PKCS1v15_SHA_Signer signer(privateKey);

	size_t length = signer.MaxSignatureLength();
	CryptoPP::SecByteBlock signature(length);

	length = signer.SignMessage(rng, (const byte*)message.c_str(), message.size(), signature);
	signature.resize(length);

	receipt.m_Signature = Signature {signature, publicKey, length};
	receipt.m_SignTime = utility::getUnixEpoch();
}

// Verify a transaction using the sender's public key. Returns true if verification succeded,
// false otherwise.
bool rsautil::verify(const Transaction& transaction, const CryptoPP::SecByteBlock& signature, const RSA::PublicKey& publicKey) {
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction params;
	string message = transaction.m_Content;

	CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);

	bool result = verifier.VerifyMessage((const byte*)message.c_str(), message.size(), signature, signature.size());
	return result;
}

// Verify a receipt using the sender's public key. Returns true if verification succeded,
// false otherwise.
bool rsautil::verify(const Receipt& receipt, const CryptoPP::SecByteBlock& signature, const RSA::PublicKey& publicKey) {
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction params;
	string message = receipt.m_Hash;

	CryptoPP::RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);

	bool result = verifier.VerifyMessage((const byte*)message.c_str(), message.length(), signature, signature.size());
	return result;
}