//
// FILENAME: firebase-auth.tcc | Plasmacoin Cryptocurrency
// DESCRIPTION: Template definitions for firebase-auth.h
// CREATED: 2021-07-14 @ 12:48 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef FIREBASE_AUTH_TCC
#define FIREBASE_AUTH_TCC

// Encrypt a user's password. This is done by combining a cryptographic salt with the
// password, then using SHA-256 to hash the resulting string. Here, all the work is done
// using PBKDF2 rather than each step being perfomred separately.
template<std::size_t N> std::string Auth::EncryptPassword(const char (&_password)[N]) {
	// ----------------------------------

	// Use Crypto++ to generate a random number. On Linux-based systems, /dev/random or /dev/urandom
	// is used to generate the number. On Windows, CryptGenRandom is used.
	CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
	std::string randomNum;

	CryptoPP::OS_GenerateRandomBlock(false, key, key.size()); // Pass `false` as the first argument to use /dev/random on Linux/macOS

	// Encode convert the number to hex, then store it as a std::string
	HexEncoder hex(new StringSink(randomNum));
	hex.Put(key, key.size());
	hex.MessageEnd();

	// ----------------------------------

	// Copy the user's password into a CryptoPP::byte array, then get its length
	size_t size = std::strlen(_password);
	byte password[size];
	std::copy(std::begin(_password), std::end(_password), password);
	size_t plen = std::strlen(reinterpret_cast<const char*>(password));

	// Copy the salt into a CryptoPP::byte array, then get it's length
	byte salt[randomNum.size()];
	std::copy(std::begin(randomNum), std::end(randomNum), salt);
	size_t slen = std::strlen(reinterpret_cast<const char*>(salt));

	byte derived[SHA256::DIGESTSIZE];

	CryptoPP::PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
	byte unused = 0;

	// Encrypt the password with the salt and SHA-256
	pbkdf.DeriveKey(derived, sizeof(derived), unused, password, plen, salt, slen, 1024, 0.0f);

	std::string result;
	HexEncoder encoder(new StringSink(result));

	encoder.Put(derived, sizeof(derived));
	encoder.MessageEnd();

	return result;
}

#endif // FIREBASE_AUTH_TCC