#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

int nr_saptamana_global = 1;

std::string formatDate(const std::tm& timeStruct, const std::string& hour)
{
    std::ostringstream oss;
    oss << std::put_time(&timeStruct, "%Y-%m-%d") << " " << hour;
    return oss.str();
}

void genereazaSaptamani(const std::string& dataStart, const std::string& dataEnd)
{
    std::tm start = {};
    std::tm end = {};

    std::istringstream ss1(dataStart);
    std::istringstream ss2(dataEnd);

    ss1 >> std::get_time(&start, "%Y-%m-%d");
    ss2 >> std::get_time(&end, "%Y-%m-%d");

    if (ss1.fail() || ss2.fail()) {
        std::cout << "Eroare: format invalid. Foloseste YYYY-MM-DD.\n";
        return;
    }

    time_t tstart = mktime(&start);
    time_t tend = mktime(&end);

    if (tstart > tend) {
        std::cout << "Eroare: data de start trebuie sa fie inainte de data de sfarsit.\n";
        return;
    }

    while (tstart <= tend) {
        std::tm inceput = *localtime(&tstart);

        time_t tsfarsit = tstart + 6 * 24 * 3600;
        std::tm sfarsit = *localtime(&tsfarsit);

        if (tsfarsit > tend) {
            sfarsit = *localtime(&tend);
        }

        std::string data_inceput = formatDate(inceput, "00:00:00");
        std::string data_sfarsit = formatDate(sfarsit, "23:59:59");

        std::cout << "INSERT INTO saptamani (nr_saptamana, data_inceput, data_sfarsit)\n";
        std::cout << "VALUES ("
            << nr_saptamana_global << ", '"
            << data_inceput << "', '"
            << data_sfarsit << "');\n\n";

        nr_saptamana_global++;

        tstart += 7 * 24 * 3600;
    }
}

int main()
{
    genereazaSaptamani("2025-09-29", "2025-12-19");
    genereazaSaptamani("2026-01-05", "2026-01-17");
    //genereazaSaptamani("2026-02-16", "2026-04-03");
    //genereazaSaptamani("2026-04-13", "2026-05-30");

    return 0;
}
