#include <iostream>
#include <sstream>
#include "Filesystem.h"

const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 13;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
	"quit",
	"pwd",
	"ls",
	"format",
	"mkdir",
	"cd",
	"create",
	"cat",
	"rm",
	"copy",
	"createImage",
	"restoreImage",
	"help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
std::string help();

int main(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FileSystem fs;

	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@DV1460";    // Change this if you want another user to be displayed
	std::string currentDir = "/";    // current directory, used for output

    bool bRun = true;

    do {
        std::cout << user << ":" << currentDir << "$ ";
        getline(std::cin, userCommand);

        int nrOfCommands = parseCommandString(userCommand, commandArr);
        if (nrOfCommands > 0) {

            int cIndex = findCommand(commandArr[0]);
            switch(cIndex) {

            case 0: // quit
                bRun = false;
                std::cout << "Exiting\n";
                break;

			case 1:  // pwd
				std::cout << fs.pwd() << endl;
				break;

			case 2:  // ls           [katalognamn]
				if (nrOfCommands == 1)
				{
					std::cout << fs.ls(".") << std::endl;
				}
				else if (nrOfCommands == 2)
				{
					std::cout << fs.ls(commandArr[1]) << std::endl;
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

			case 3:  // format
				fs.format();
				std::cout << "Disk formaterad." << endl;
				break;

			case 4:  // mkdir        <katalognamn>
				if (nrOfCommands == 2)
				{
					if (fs.mkdir(commandArr[1]))
					{
						std::cout << "Directory made." << std::endl;
					}
					else
					{
						std::cout << "Failed to create directory." << std::endl;
					}
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

			case 5:  // cd           <katalognamn>
				if (nrOfCommands == 2)
				{
					if (fs.cd(commandArr[1]))
					{
						currentDir = fs.pwd();
					}
					else
					{
						std::cout << "Failed to find directory." << std::endl;
					}
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

			case 6:  // create       <filnamn>
				if (nrOfCommands == 2)
				{
					string content;
					getline(cin, content);
					if (fs.create(commandArr[1], content))
					{
						std::cout << "File created." << endl;
					}
					else
					{
						std::cout << "Failed to create file." << endl;
					}
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

			case 7:  // cat          <filnamn>
				if (nrOfCommands == 2)
				{
					std::cout << fs.cat(commandArr[1]) << std::endl;
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

			case 8:  // rm           <filnamn>
				if (nrOfCommands == 2)
				{
					if (fs.rm(commandArr[1]))
					{
						std::cout << "Target removed." << endl;
					}
					else
					{
						std::cout << "Failed to remove target." << endl;
					}
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

			case 9:  // copy         <fil1> <fil2>
				if (nrOfCommands == 3)
				{
					if (fs.copy(commandArr[1], commandArr[2]))
					{
						std::cout << "File copied." << endl;
					}
					else
					{
						std::cout << "Failed to copy file." << endl;
					}
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

			case 10: // createImage  <filnamn>
				if (nrOfCommands == 2)
				{
					fs.createImage(commandArr[1]);
					std::cout << "Image created." << endl;
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

			case 11: // restoreImage <filnamn>
				if (nrOfCommands == 2)
				{
					if (fs.restoreImage(commandArr[1]))
					{
						std::cout << "Image restored." << endl;
					}
					else
					{
						std::cout << "Failed to restore image." << endl;
					}
				}
				else
				{
					std::cout << "Invalid number of arguments" << std::endl;
				}
				break;

            case 12: // help
                std::cout << help() << std::endl;
                break;

            default:
                std::cout << "Unknown command: " << commandArr[0] << std::endl;
            }
        }
    } while (bRun == true);

    return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
    std::stringstream ssin(userCommand);
    int counter = 0;
    while (ssin.good() && counter < MAXCOMMANDS) {
        ssin >> strArr[counter];
        counter++;
    }
    if (strArr[0] == "") {
        counter = 0;
    }
    return counter;
}
int findCommand(std::string &command) {
    int index = -1;
    for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
        if (command == availableCommands[i]) {
            index = i;
        }
    }
    return index;
}

std::string help() {
    std::string helpStr;
	helpStr += " _____________________________________________________________________________________________________________________\n";
	helpStr += "/   Kommando <krav> [valfri] - Sammanfattning                                                                         \\\n";
	helpStr += "| quit                       : lämnar körningen <Redan gjord i filsystemet>                                           |\n";
	helpStr += "| pwd                        : skriver ut den fullständiga sökvägen ändå från roten till filnamnet.                   |\n";
	helpStr += "| ls           [katalognamn] : listar innehållet i aktuellt katalog (filer och undermappar).                          |\n";
	helpStr += "| format                     : bygger upp ett tomt filsystem, dvs. formatterar disken.                                |\n";
	helpStr += "| mkdir        <katalognamn> : skapar en ny tom katalog på den simulerande disken.                                    |\n";
	helpStr += "| cd           <katalognamn> : ändrar aktuell katalog till den angivna katalogen på den simulerade disken.            |\n";
	helpStr += "| create       <filnamn>     : skapar en fil på den simulerande disken (datainnehållet skrivs in på en extra tom rad) |\n";
	helpStr += "| cat          <filnamn>     : skriver ut innehållet i filen filnamn på skärmen.                                      |\n";
	helpStr += "| rm           <filnamn>     : tar bort angiven fil från den simulerade disken.                                       |\n";
	helpStr += "| copy         <fil1> <fil2> : skapar en ny fil fil2 som är en kopia av den existerande fil fil1.                     |\n";
	helpStr += "| createImage  <filnamn>     : sparar det simulerade systemet på en fil på datorns hårddisk så att                    |\n";
	helpStr += "|                              den går att återskapa vid ett senare tillfälle.                                        |\n";
	helpStr += "| restoreImage <filnamn>     : återstället systemet från en fil på datorns hårddisk.                                  |\n";
	helpStr += "| help                       : visa denna hjälptext                                                                   |\n";
	helpStr += "\\_____________________________________________________________________________________________________________________/\n";
	return helpStr;
}
