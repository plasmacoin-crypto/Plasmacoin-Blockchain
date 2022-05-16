//
// FILENAME: transmitter.tpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Template definitions for the Transmitter class
// CREATED: 2022-04-18 @ 6:37 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

template<typename T> vector<string> Transmitter::Format(const BlockchainData<T*>& bcdata) {
	vector<string> returnVec {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::BLOCKCHAIN_DATA)),
		std::to_string(bcdata.m_DataType),
	};

	// Copy over the blockchain data being transferred
	for (auto ds: bcdata.m_Data) {
		vector<string> contents = Format(ds);

		for (auto c: contents) {
			std::cout << c << std::endl;
		}

		std::copy(returnVec.begin(), returnVec.end(), std::back_inserter(contents));
	}

	return returnVec;
}