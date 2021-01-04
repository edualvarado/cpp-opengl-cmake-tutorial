#include "files.hpp"

#include "vcl/base/base.hpp"

#include <fstream>

namespace vcl
{
    bool check_file_exist(const std::string filename)
    {
        // Open file
        std::ifstream stream(filename);
        if( !stream.is_open() )
            return false;
        else
        {
            stream.close();
            return true;
        }
    }

    void assert_file_exist(const std::string& filename)
    {
        // Open file
        std::ifstream stream(filename);

        // Abort program if the file cannot be opened
        if( !stream.is_open() ) {

            std::string msg =
                    "Error cannot access the following file path \n    \""+filename+"\"\n\n"
                    "    => If the file exists, you may need to adapt the path from which you run the program \n"
                    "       Reminder: The program is exprected to run form the root directory\n"
                    "       (In QtCreator: set projects/Run directory)\n"
                    "       (In Command Line: change the directory such that you can access the file)\n"
                    "       (In Visual Studio: you need to copy the directory containing this data at the same place than your executable)";

            error_vcl(msg);
        }

        stream.close();
    }
}