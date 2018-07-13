#include <iostream>
#include <string>
#include "Headers/Question.h"
#include "Headers/FileUtils.h"
#include "Headers/HuffmanTree.h"
#include "Headers/HuffmanNode.h"
#include "Headers/Huffman.h"
#include "Headers/LZ77.h"
#include "Headers/LZ78.h"
#include "Headers/LZW.h"


using namespace std;

/// Variaveis utilizadas em toda a main(), afim de concentrar em uma só estrutura
struct Variables
{
    /// Vectors com os dados importados dos arquivos
    vector<Question> questionVector;

    string path;
    string questionPath;

    /// Usados para a leitura do arquivo de Entrada
    vector<int> Ns;
    unsigned long N;

    /// Usados na escolha dos menus
    short entry;

    void entryPath(string _path)
    {
        path = _path;
        if (path[path.size() - 1] != '\\' && path[path.size() - 1] != '/' && !path.empty())
            path.push_back('/');
        if (!path.empty())
        {
            cout << "Path informado: " << path << endl;
            cout << "---------------------------------------------------------------------------------\n\n";
        }
        else
        {
            cout << "Como nao foi informado a path, consideraremos o diretorio do executavel como path\n";
            cout << "---------------------------------------------------------------------------------\n\n";
        }
        questionPath = path + "pythonquestions/Questions.csv";

    }
};

void openMenu(Variables &vars);
void codeHuffman(Variables &vars);
void decodeHuffman(Variables &vars);
void codeLZ77(Variables &vars);
void decodeLZ77(Variables &vars);
void codeLZ78(Variables &vars);
void decodeLZ78(Variables &vars);
void codeLZW(Variables &vars);
void decodeLZW(Variables &vars);
void tests();



int main(int argc, char **argv)
{
	string text = "bookkeeper";
	//HuffmanTree* tree = new HuffmanTree(text);

	LZW lz;
	vector<Question> q;
	FileUtils::readFileQuestion("C:/Users/Luis/Desktop/Trabalho_ED2/Questions.csv", q);
    lz.compressQuestions(q);

	Huffman hf;

	string teste = hf.encode("bananabanabofana");

	cout << hf.decode(teste);

	hf.compressQuestions(q);


	//system("PAUSE");
	return 0;


	///////////////////// main, entre outros
    FileUtils::showTop();

    if (argc != 2 && argc != 1) {
        cout << "Erro na chamada do programa. Informe corretamente o path (caminho) padrao inicial." << endl;
        cout << "Ou deixe em branco, caso queira considerar o diretorio do executavel como path" << endl;
        cout << R"(Certifique-se de no path estar o arquivo "entrada.txt" e a pasta "pythonquestions".)" << endl;
        cout
                << R"(Eh necessario que os arquivos "Answers.csv", "Questions.csv" e "Tags.csv" estejam no diretorio "pythonquestions".)"
                << endl;
        cout << "Formato a inserir na linha de comando para execucao do algoritmo:" << endl;
        cout << "<./executavel> <pathDoDiretorioInicial>" << endl;
        FileUtils::endProgram();
        return 0;
    }

    Variables vars;
    /// Se o quandtidade de argumentos é 1, nao foi informado o caminho, entao passa uma string vazia
    /// Do contrário, passa o caminho passado por parametro
    vars.entryPath(argc == 1 ? "" : argv[1]);

    /**
 * Limpa os arquivos de saida, para nao conter lixos de outra execução
 * Caso queira salvar os resultados da saída, eh necessário copiar os arquivos
 */
    //FileUtils::clearFileContent("saidaInsercao.txt");
    //FileUtils::clearFileContent("saidaBusca.txt");
    //FileUtils::clearFileContent("saidaRemocao.txt");

    /**a
     * Leitura dos arquivos de questões e de respostas.
     * O arquivo de Tags nao eh usado nessa parte do trabalho
     */
    if (vars.questionVector.empty())
        FileUtils::readFileQuestion(vars.questionPath, vars.questionVector);

    openMenu(vars);

    return 0;
}

/**
 * Menu de opções inicial
 * @param vars: estrutura com todas as variáveis necessárias para a execução do programa
 */
void openMenu(Variables &vars) {
    cout << "------------------------------------------------------------------------" << endl;
    cout << "||        TRABALHO DE ESTRUTURA DE DADOS 2 - MENU DE ESCOLHAS         ||" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "||                 INSIRA O CODIGO DA OPCAO ESCOLHIDA                 ||" << endl;
    cout << "||       Opcao 0: Sair e encerrar a execucao                          ||" << endl;
    cout << "||       Opcao 1: Codificação por Huffman                             ||" << endl;
    cout << "||       Opcao 2: Decodificação por Huffman                           ||" << endl;
    cout << "||       Opcao 3: Codificação por LZ77                                ||" << endl;
    cout << "||       Opcao 4: Decodificação por LZ77                              ||" << endl;
    cout << "||       Opcao 5: Codificação por LZ7                                 ||" << endl;
    cout << "||       Opcao 6: Decodificação por LZ78                              ||" << endl;
    cout << "||       Opcao 7: Codificação por LZW                                 ||" << endl;
    cout << "||       Opcao 8: Decodificação por LZW                               ||" << endl;
    cout << "||       Opcao 9: Testes                                              ||" << endl;
    cout << "||--------------------------------------------------------------------||" << endl;
    cout << "||     Opcao: ";
    cin >> vars.entry;
    cout << "||--------------------------------------------------------------------||" << endl;
    switch (vars.entry) {
        case 0:
            FileUtils::endProgram();
        case 1:
            //cod por huffm
            break;
        case 2:
            //decod por hufman
            break;
        case 3:
            //cod por lz77
            break;
        case 4:
            //decod por lz77
            break;
        case 5:
            //cod por lz78
            break;
        case 6:
            //decod por lz78
            break;
        case 7:
            //decod por lzw
            break;
        case 8:
            //decod por lzw
            break;
        case 9:
            tests();
            break;
        default:
            cout << "Opcao invalida. Tente novamente:" << endl;
            openMenu(vars);
    }
    FileUtils::pauseScreen(true);
    char executarNovamente;
    cout << "Executar novamente? (S/N)" << endl;
    cin >> executarNovamente;
    while (executarNovamente != 'N' && executarNovamente != 'n' && executarNovamente != 'S' &&
           executarNovamente != 's') {
        cout << "Entrada invalida! Tente novamente: ";
        cin >> executarNovamente;
    }
    executarNovamente == 'S' || executarNovamente == 's' ? openMenu(vars) : FileUtils::endProgram();
}

void codeHuffman(Variables &vars)
{

}

void decodeHuffman(Variables &vars)
{

}

void codeLZ77(Variables &vars)
{

}

void decodeLZ77(Variables &vars)
{

}

void codeLZ78(Variables &vars)
{

}

void decodeLZ78(Variables &vars)
{

}

void codeLZW(Variables &vars)
{

}

void decodeLZW(Variables &vars)
{

}

void tests()
{
    //String original para ser usada nos testes
    string str = "bananabofanaoanabafanabananananana";

    ///Testes Huffman
    auto *huffman = new Huffman();


    ///Testes LZ77
    auto *lz77 = new LZ77(8, 4);
    vector<Triple> saida = lz77->compress(str);
    string comprimido = lz77->saveFile(saida, "testeCompressaoLZ77.txt");
    string descomprimeTriple = lz77->decompressText(saida);
    string descomprimeString = lz77->decompressText(comprimido);

    cout << "Original: " << str << endl;
    cout << "Comprimido: " << comprimido<< endl;
    cout << "Descomprimido por Triple: " << descomprimeTriple << endl;
    cout << "Descomprimido por String: " << descomprimeString << endl;


    ///Testes LZ78
    auto *lz78 = new LZ78();


    ///Testes LZW
    auto  * lzw = new LZW();
}