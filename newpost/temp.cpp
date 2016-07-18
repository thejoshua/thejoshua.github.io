#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

void errorExit();

int main(int argc, char *argv[]) {

  // no arguments!
  if (argc == 1) {
    errorExit();
  }

  if (!std::strcmp(argv[1], "post") || !std::strcmp(argv[1], "page")) {
    std::string frontMatter;

    frontMatter += "---\nlayout: ";
    frontMatter += argv[1];
    frontMatter += "\n";

    if (argv[2]) {
      frontMatter = frontMatter + "title: " + argv[2] + "\n";
    }

    if (argc > 2) {
      frontMatter = frontMatter + "tags: ";
    }

    for (int i =3; i < argc; i++) {
      frontMatter = frontMatter + argv[i] + " ";
    }

    frontMatter = frontMatter + "\n---\n";
    std::cout << "YAML frontmatter generated..." << std::endl;

    std::string fileName;
    char fileNameChar[10];
    time_t timeSinceEpoch;
    struct tm * theDate;

    std::time(&timeSinceEpoch);
    theDate = std::localtime(&timeSinceEpoch);

    std::cout << "Got the date..." << std::endl;

    std::strftime(fileNameChar, 11, "%F",theDate);
    fileName = fileNameChar;
    fileName.append("-");
    fileName.append(argv[2]);
    fileName.append(".md");

    for(int i = 0; i < fileName.size(); i++) {
      if (!fileName.compare(i, 1, " ")) {
        fileName.at(i) = '-';
      }
    }
    std::cout << "Filename generated..." << std::endl;

    //got all the data, file time!
    std::ofstream theNewFile;
    theNewFile.open(fileName);
    theNewFile << frontMatter;
    theNewFile.close();

    std::cout << "File written...\n";
    std::cout << "and we\'re done. Bye." << std::endl;
    std::exit(0);
  }

  //Why does this return give me an "abort trap: 6"?
  //I put in std::exit()'s so it'll never get here.
  //Why fix it when you can work around it, right?
  return 0;
}

void errorExit () {
    //generic error exitor
    std::cout << "Usage: a.out post|page \"title\" tag tag ..." << std::endl;
    std::exit(1);
}
