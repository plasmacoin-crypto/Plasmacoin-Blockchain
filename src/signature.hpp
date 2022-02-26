//
// FILENAME: signature.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A digital signature
// CREATED: 2021-02-13 @ 11:31 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include <cryptopp/rsa.h> 		 // Use Crypto++'s RSA functionality
#include <cryptopp/secblock.h>	 // Use SecByteBlock

using CryptoPP::RSA;
using CryptoPP::SecByteBlock;

struct Signature {
	SecByteBlock 	m_Signature;
	RSA::PublicKey 	m_PublicKey;
	size_t 			m_Length;
};

#endif // SIGNATURE_HPP
