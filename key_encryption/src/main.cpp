#include "argparse/argparse.hpp"
#include "CaesarCryptography.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");

	argparse::ArgumentParser prog("key_encryption", "1.0");

	prog.add_argument("-m", "--modulus")
		.scan<'i', int>()
		.help("set value of modulus being used for encryption(decryption)")
		.default_value(int(256));
	prog.add_argument("-d", "--decrypt")
		.help("perform decryption instead of encryption")
		.default_value(false)
		.implicit_value(true);
	prog.add_argument("key")
		.help("key being used for encryption");
	prog.add_argument("input_file")
		.help("path to input file that will be encrypted");
	prog.add_argument("output_file")
		.help("path to output encrypted file");

	try
	{
		prog.parse_args(argc, argv);
	}
	catch (const std::exception& err)
	{
		std::cout << err.what() << std::endl;
		std::cout << prog;
		return 1;
	}

	std::string inFilePath = prog.get<std::string>("input_file");
	std::string outFilePath = prog.get<std::string>("output_file");
	int mod = prog.get<int>("-m");
	std::string key = prog.get<std::string>("key");

	std::cout << "Mod = " << mod << "; Key = " << key << std::endl;

	try
	{
		FileInputStream input(inFilePath);
		FileOutputStream output(outFilePath);

		CaesarCryptography cryptography(mod, key);

		if (prog["-d"] == true)
		{
			std::cout << "Decrypting file " << inFilePath << " into " << outFilePath << " ..." << std::endl;
			cryptography.Encrypt(input, output, true);
		}
		else
		{
			std::cout << "Encrypting file " << inFilePath << " into " << outFilePath << " ..." << std::endl;
			cryptography.Encrypt(input, output);
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	std::cout << "Done." << std::endl;

	return 0;
}
