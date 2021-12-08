#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <sstream>
#include <algorithm>

int main()
{
	std::ifstream file("slowka.txt");
	if (!file.is_open())
	{
		std::cout << "Nie ma pliku z tlumaczeniami" << std::endl;
		return 1;
	}
	std::map < std::string, std::string > dictionary;
	//std::unordered_map < std::string, std::string > dictionary;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string key;
		std::string value;
		ss >> key >> value;
		dictionary[key] = value;
	}

	std::for_each(dictionary.begin(), dictionary.end(), [](const std::pair<std::string,std::string>& el) {
		std::cout << el.first << "-" << el.second << std::endl;
		});

	std::vector<std::string> toTranslate;

	std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), std::back_inserter(toTranslate));

	std::vector<std::string> translated;

	std::copy_if(toTranslate.begin(), toTranslate.end(), std::back_inserter(translated), [&dictionary,&toTranslate,&translated](const std::string x) {
		if (dictionary.count(x)>0)
		{
			translated.push_back(dictionary[x]);
			return false;
		}
		return true;
		});


	std::copy(translated.rbegin(), translated.rend(), std::ostream_iterator<std::string>(std::cout, "\n"));
	std::ofstream file2("przetlumaczone.txt");
	std::copy(translated.begin(), translated.end(), std::ostream_iterator<std::string>(file2, "\n"));
	return 0;
}
