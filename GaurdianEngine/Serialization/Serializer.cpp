#include "Serializer.h"
#include <fstream>
#include <iostream>
#include <rapidjson/filereadstream.h>

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
	delete writer;
}

void Serializer::SerializeJson(ISerializeable* serializeable)
{
	sBuffer.Clear(); //clear buffer from any previous json creation
	if (writer != nullptr)
	{
		delete writer;
	}
	writer = new PrettyWriter<StringBuffer>(sBuffer); //makes a new writer
	writer->StartObject(); //creates the root json object
	serializeable->Serialize(writer);
	writer->EndObject();
}

void Serializer::WriteJsonToFile(std::string filePath)
{
	std::ofstream file(filePath);
	if (file.is_open())
	{
		file << sBuffer.GetString(); //writes the json to a file
	}
	else
	{
		std::cout << "Unable to open file: " << filePath << std::endl;
	}
}

Deserializer::Deserializer()
{
	
}

Deserializer::~Deserializer()
{
	
}

void Deserializer::DeserializeJson(const char* filePath, IDeserializeable* serializeable)
{
	std::ifstream file;
	char ch;
	std::string json;
	json.resize(100000); //sets the json string to 100000 characters
	unsigned int count = 0;
	file.open(filePath, std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		while (file.get(ch)) //reads the json in character by character (might look for a better way to handle this)
		{
			if (count < 100000)
			{
				json[count] = ch;
				++count;
			}
			else //if the count > 100000 it starts expanding the string to make room
			{
				json += ch;
			}
		}
	}
	file.close();

	document.Parse(json.c_str());
	if (!document.HasParseError())
	{
		serializeable->Deserialize(document);
	}
	else
	{
		std::cout << "Oh no parse error: " << document.GetParseError() << "!" << std::endl;
	}
}