#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <ctime>
#include "colors.hpp"

using namespace Color;
using namespace std;

static const char alphaNum[] = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789!@#$%*-_+";
int size = sizeof(alphaNum) - 1;

class ArgParse{

    public:
        ArgParse( uint8_t argc, char **argv ){
            if ( argc != 1 ){
                this->argc = argc;
                this->argv = argv;

                _Init();
            }
            else {
                HelpPanel();
            }
        }

        void _Init(){
            try {
                if ( strcmp(this->argv[1], "-g") == 0 || strcmp(this->argv[1], "--gen") == 0 ){
                    this->Gen = true;
                } else {
                    throw("Parámetro Inválido.");
                }
		        for (uint8_t i = 2; i < this->argc; i++){
		            if ( strcmp(this->argv[i], "medium") == 0 ){
		                 this->Length = 12;
		            }
		            else if ( strcmp(this->argv[i], "large") == 0 ){
		                 this->Length = 16;
		            }
		            else if ( atoi(this->argv[i]) > 1 ){
		                if ( atoi(this->argv[i]) <= 8 ){
		                    this->Val = atoi(this->argv[i]);
		                } else {
                            throw("Número mayor a 8.");
		                }
		            }
		            else if ( strcmp(this->argv[i], "-o") == 0 || strcmp(this->argv[i], "--output") == 0 ){
		                 if ( this->argc > i+1 && atoi(this->argv[i+1]) == 0 ){
		                    this->Output = true;
		                    this->NameFile = this->argv[i+1];
		                    break;
		                 }
		                 else {
		                    throw("Falta argumentos..");
		                 }
		           }
		           else {
		                 throw("Parámetro Inválido.");
		           }
		       }
            } catch(const char *Err){
                cerr << LIGHTRED_EX << "[!]Hubo un error" << RESET << ": "<< Err << endl;
                exit(1);

            }
            GenPasswd();
        }

        void GenPasswd(){
            srand(time(0));
            this->PasswordVector.resize(this->Val);
            for ( uint8_t j = 0; j < this->Val;j++ ){
                for ( uint8_t i = 0; i < this->Length;i++ ){
                    char ch = alphaNum[rand() % ::size];
                    this->PasswordVector[j].push_back(ch);
                }
            }

            if ( this->Output ){
            	SavePasswd();
            	string decs;
            	cout << "¿Desea ver los datos del fichero( " << this->NameFile << " )?(y/n): ";
                cin >> decs;
            	cout << "\n";

            	if ( decs == "y" ){
            	    cout << "[------ File: " << LIGHTGREEN_EX << this->NameFile << RESET << " ------]" << endl;
                    PrintFile();
            	} else {
                    cout << LIGHTGREEN_EX << "Saliendo..." << RESET << endl;
                }
			} else {
            	PrintPassword();
            }
        }

        void Flags(){
                cout << LIGHTYELLOW_EX << "Output" << RESET << ": " << this->Output << endl;
                cout << LIGHTYELLOW_EX << "NameFile" << RESET << ": " << this->NameFile << endl << endl;
            }

        void PrintPassword(){
            Flags();
            for ( uint8_t i = 0; i < this->Val; i++){
                cout << LIGHTRED_EX << i+1 << LIGHTYELLOW_EX << " Password" << RESET << ": " << this->PasswordVector[i] << endl;
            }
        }

        void SavePasswd(){
            fstream File( this->NameFile, ios::trunc | ios::out );

            if ( File.fail() ){
                cerr << "Error al abrir el fichero..." << endl;
            } else {

                File << "Contraseñas:\n";
                for ( uint8_t j = 0; j < this->PasswordVector.size(); j++ ){
                    File << j << "Password: " << PasswordVector[j] << endl;
                }
            }
            File.close();
        }

        void PrintFile(){
            fstream File2( this->NameFile.c_str(), ios::in );
            char linea[300];
            long contador = 0L;

            if ( File2.fail() ){
                cerr << "Error al abrir el fichero..." << endl;
            } else {
                while ( !File2.eof() ){
                    File2.getline(linea, sizeof(linea));
                    cout << linea << endl;
                    if (( ++contador % 24 ) == 0 ){
                        cout << "Continuar...";
                        cin.get();
                    }
                }
                File2.close();
                cout << LIGHTGREEN_EX << "Saliendo..." << RESET << endl;
            }
        }

        void Usage(){
            cout << LIGHTGREEN_EX << "Example: ./GenPasswd --gen large 5 --output fichero.txt" << RESET << endl;
        }

        void HelpPanel(){
            system("figlet GenPasswd");
            cout << LIGHTYELLOW_EX << "\n\t\tGenPasswd " << LIGHTBLUE_EX << "v0.1" << RESET << " by justgr0w.\n";
            cout << LIGHTGREEN_EX << "\tPequeño script básico para generar contraseñas\n" << endl;
            cout << LIGHTYELLOW_EX << "[-g][--gen]" << RESET << "\tGENERAR\t\tCuantas password's a generar." << endl;
            cout << LIGHTRED_EX << "\t\t\t[WARN]" << RESET << " El máximo de passwords son 8." << endl;
            cout << LIGHTYELLOW_EX << "[medium][large]" << RESET << "\tLONGITUD\tMedium(12 char) y Large (16 char)." << endl;
            cout << LIGHTYELLOW_EX << "[-o][--output]" << RESET << "\tOUTPUT\t\tDonde se alojarán las password's generadas." << endl;
            cout << "\t"; Usage();
        }

        ~ArgParse(){
        }

    private:

        uint8_t Val = 1;
        uint8_t Length = 8;
        uint8_t argc;
        vector<string>PasswordVector;
        string NameFile = "?";
        char **argv;
        bool Output = false, Gen = false;
};
