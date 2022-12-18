// Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ctime>

/// <summary>
/// encrypt or decrypt a source string using the provided key
/// </summary>
/// <param name="source">input string to process</param>
/// <param name="key">key to use in encryption / decryption</param>
/// <returns>transformed string</returns>
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
	// get lengths now instead of calling the function every time.
	// this would have most likely been inlined by the compiler, but design for perfomance.
	const auto key_length = key.length();
	const auto source_length = source.length();

	// assert that our input data is good
	assert(key_length > 0);
	assert(source_length > 0);

	std::string output = source;

	// loop through the source string char by char
	for (size_t i = 0; i < source_length; ++i)
	{
		// transform each character based on an xor of the key modded constrained to key length using a mod
		output[i] = source[i] ^ key[i % key_length];
	}

	// our output length must equal our source length
	assert(output.length() == source_length);

	// return the transformed string
	return output;
}

/// <summary>
/// Check if file contents are in the expected format
/// </summary>
/// <param name="content"></param>
void check_content_format(const std::string& content)
{
	int new_line_count = 0;
	for (size_t i = 0; i < content.length(); i++)
	{
		if (content[i] == '\n') {
			new_line_count++;
		}
	}

	if (new_line_count < 3) {
		std::string error = "Incorrect file format";
		error += "\nExpected Format:";
		error += "\nLine 1: <students name>";
		error += "\nLine 2: <Lorem Ipsum Generator website used> https ://pirateipsum.me/ (could be https://www.lipsum.com/ or one of https://www.shopify.com/partners/blog/79940998-15-funny-lorem-ipsum-generators-to-shake-up-your-design-mockups)";
		error += "\nLines 3+: <lorem ipsum generated with 3 paragraphs> ";

		throw error;
	};
}

/// <summary>
/// Read contents of the specified file
/// </summary>
/// <param name="filename"></param>
/// <returns>Contents of the file</returns>
std::string read_file(const std::string& filename)
{
	// Declare local variables
	std::fstream file;
	std::string file_text;
	char ch;

	// Open file for reading
	file.open(filename, std::ios::in);

	// Check and throw exception if file does not exist
	if (!file) {
		throw "File with filename: " + filename + " does not exist!";
	}

	// Notifiy on progress
	std::cout << "File: " + filename + " loaded." << std::endl;

	// Iterate over file contents reading character by character and append to file_text
	while (file.eof() == 0)
	{
		file.get(ch);
		file_text += ch;
	}

	// Check if file_text is in correct format
	check_content_format(file_text);

	// Close the file
	file.close();

	// Return contents of the file
	return file_text;
}

/// <summary>
/// Get student name from string content
/// </summary>
/// <param name="string_data"></param>
/// <returns>Name of the student</returns>
std::string get_student_name(const std::string& string_data)
{
	std::string student_name;

	// find the first newline
	size_t pos = string_data.find('\n');
	// did we find a newline
	if (pos != std::string::npos)
	{ // we did, so copy that substring as the student name
		student_name = string_data.substr(0, pos);
	}

	return student_name;
}

/// <summary>
/// Returns today's date in the format yyyy-mm-dd
/// </summary>
/// <returns>todays date</returns>
std::string get_date_formatted()
{
	// Declare and Initialize local variables
	std::tm local_time;
	std::time_t now = time(NULL);
	char* date = new char[12];

	localtime_s(&local_time, &now);

	// Format local time string to yyyy-mm-dd
	strftime(date, 12, "%F", &local_time);

	// Return the formatted date
	return date;
}

/// <summary>
/// Write content to file
/// </summary>
/// <param name="filename"></param>
/// <param name="student_name"></param>
/// <param name="key"></param>
/// <param name="data"></param>
void save_data_file(const std::string& filename, const std::string& student_name, const std::string& key, const std::string& data)
{
	// Declare variables
	std::fstream file;

	// Open file for writing
	file.open(filename, std::ios::out);

	// Throw exception if an error occurs while creating or opening the file for writing
	if (!file) {
		throw "An error occured while creating the file";
	}

	// Write to content to file using the format:
	//  Line 1: student name
	//  Line 2: timestamp (yyyy-mm-dd)
	//  Line 3: key used
	//  Line 4+: data
	file << student_name << std::endl;
	file << get_date_formatted() << std::endl;
	file << key << std::endl;
	file << data;

	// Close the file
	file.close();

	// Notify on progress
	std::cout << "File: " + filename + " created successfully!" << std::endl;
}

int main()
{
	try
	{
		std::cout << "Encyption Decryption Test!" << std::endl;

		// input file format
		// Line 1: <students name>
		// Line 2: <Lorem Ipsum Generator website used> https://pirateipsum.me/ (could be https://www.lipsum.com/ or one of https://www.shopify.com/partners/blog/79940998-15-funny-lorem-ipsum-generators-to-shake-up-your-design-mockups)
		// Lines 3+: <lorem ipsum generated with 3 paragraphs> 
		//Bucko ho Pirate Round dead men tell no tales chandler plunder wherry crimp fore warp. Spirits scallywag transom jib keel furl broadside capstan gangway clipper. Killick driver deadlights Privateer topgallant case shot booty hearties lookout transom.		
		//Topgallant mizzenmast lanyard furl overhaul tender hempen halter yardarm swing the lead long boat. Dance the hempen jig long boat boatswain keelhaul cable red ensign gangway landlubber or just lubber dead men tell no tales log. Stern black spot sheet tackle hardtack spike lugsail yo-ho-ho Jack Tar sutler.
		//Run a shot across the bow rum dance the hempen jig bucko bilged on her anchor knave Sail ho driver booty execution dock. Quarterdeck mizzenmast galleon dead men tell no tales scuppers Sink me me fluke driver gibbet. Nelsons folly draft cutlass gabion come about long boat man-of-war blow the man down fire in the hole Arr.
		const std::string file_name = "inputdatafile.txt";
		const std::string encrypted_file_name = "encrypteddatafile.txt";
		const std::string decrypted_file_name = "decrytpteddatafile.txt";
		const std::string source_string = read_file(file_name);
		const std::string key = "some-strong-key!";

		// get the student name from the data file
		const std::string student_name = get_student_name(source_string);

		// encrypt sourceString with key
		const std::string encrypted_string = encrypt_decrypt(source_string, key);

		// save encrypted_string to file
		save_data_file(encrypted_file_name, student_name, key, encrypted_string);

		// decrypt encryptedString with key
		const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

		// save decrypted_string to file
		save_data_file(decrypted_file_name, student_name, key, decrypted_string);

		// Notify on progress
		std::cout << "Read File: " << file_name << " - Encrypted To: " << encrypted_file_name << " - Decrypted To: " << decrypted_file_name << std::endl;
	}
	catch (const std::string& error_message)
	{
		std::cout << error_message << std::endl;
	}

	// students submit input file, encrypted file, decrypted file, source code file, and key used
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
