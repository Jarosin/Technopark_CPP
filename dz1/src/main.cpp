#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <locale> 
std::string FindFilms(std::string file_name, std::string artist_name)
{
    std::ifstream myfile;
    myfile.open(file_name);
    if (!myfile)
        return "";

    std::string name;
    std::string temp;
    while (name.length() == 0 && !myfile.eof())
    {
        for (int i = 0; i < 2; i++)
        {
            std::getline(myfile, temp, '\t');
        }
        if (temp == artist_name)
        {
            name = temp;
            for (int i = 0; i < 3; i++)
            {
                std::getline(myfile, temp, '\t');
            }
            std::getline(myfile, temp, '\n');

        }
        else
            std::getline(myfile, temp);
    }
    myfile.close();
    return temp;
}
std::vector<std::string> ParseFilmIdString(std::string film_ids)
{
    std::string temp;
    std::stringstream buff(film_ids);
    std::vector<std::string> res;
    while (std::getline(buff, temp, ','))
    {
        res.push_back(temp);
    }
    return res;
}
void FindFilmNames(std::string file_name, std::vector<std::string> &films, std::vector<bool> &checked_films)
{
    std::ifstream myfile;
    myfile.open(file_name);
    if (!myfile.is_open())
        return;
    std::string name;
    std::string temp;
    while (name.length() == 0 && !myfile.eof())
    {
        std::getline(myfile, temp, '\t');
        for (auto it = films.begin(); it < films.end(); it++)
        {
            if ((*it) == temp)
            {      
                checked_films[it - films.begin()] = true;
                std::getline(myfile, temp, '\t');
                if (temp != "movie")
                {
                    *it = "";
                    break;
                }
                for (int i = 0; i < 2; i++)
                {
                    std::getline(myfile, temp, '\t');
                }
                *it = temp;
                std::getline(myfile, temp, '\t');
                if (temp == "1")
                    *it = "";
                break;
            }
        }
        std::getline(myfile, temp, '\n');  
    }
    myfile.close();
}
//1 - файл с актерами, 2 - файл с фильмами, 3 - имя актера
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        return 0;
    } 
    std::string nfile_name = argv[1];
    std::string ffile_name = argv[2];
    std::string artist_name = argv[3];
    std::string raw_films;
    std::vector<std::string> parsed_films;
    std::ifstream myfile; 
    raw_films = FindFilms(nfile_name, artist_name);
    parsed_films = ParseFilmIdString(raw_films);   
    std::vector<bool> checked_films(parsed_films.size(), false);
    FindFilmNames(ffile_name, parsed_films, checked_films);
    for (auto it = parsed_films.begin(); it < parsed_films.end(); it++)
    {
        if (checked_films[it - parsed_films.begin()])
            std::cout << (*it) << std::endl;    
    }
    return 0;
}
//todo: можно переорганизовать ввод под do-while
//todo: проверить, что выбранные записи - movies
//todo: посмотреть что с языком
//todo: с помощью getopt переделать прием аргументов через "опции"
//todo: разнести функции по файлам
//todo: проверить что в документах правильное количество столбцов(насчет названий не уверен)