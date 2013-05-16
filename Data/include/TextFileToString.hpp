#ifndef TEXTFILETOSTRING_H
#define TEXTFILETOSTRING_H

#include <string>

class TextFileToString
{
	public:
		TextFileToString();
		virtual ~TextFileToString();
		static std::vector<std::string> fileToString(std::string path);

	protected:
	private:
};

#endif // TEXTFILETOSTRING_H
