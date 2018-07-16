#include <iostream>
#include <string>
#include "Headers/Question.h"
#include "Headers/FileUtils.h"
#include "Headers/Huffman.h"
#include "Headers/LZ77.h"
#include "Headers/LZ78.h"
#include "Headers/LZW.h"

#define RANDOM_SEED std::chrono::system_clock::now().time_since_epoch().count()
#define ENCODE 0
#define DECODE 1

using namespace std;

/// Variaveis utilizadas em toda a main(), afim de concentrar em uma só estrutura
struct Variables
{
    /// Vectors com os dados importados dos arquivos
    vector<Question> questionVector;

    /// Caminho dos arquivos de entrada Questions.csv e entrada.txt
    string path;
    string questionPath;

    string strComprimida;

    /// Usados para a leitura do arquivo de Entrada
    vector<int> Ns;
    unsigned long N;

    /// Usados na escolha dos menus
    short entry, entryCodeDecode;

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

vector<Question> getVetQuestionsRand(vector<Question> &vetQuestions, const int &n);
string getBodyNQuestions(vector<Question> &questionList);
string getBodyNQuestions(vector<Question> &questionList, int qtd);
void openMenu(Variables &vars);
void codeDecodeHuffman(Variables &vars);
void codeDecodeLZ77(Variables &vars);
void codeDecodeLZ78(Variables &vars);
void codeDecodeLZW(Variables &vars);
void tests();



int main(int argc, char **argv) {
	Variables vars;
    FileUtils::showTop();

    if (argc != 2 && argc != 1) {
        cout << "Erro na chamada do programa. Informe corretamente o path (caminho) padrao inicial." << endl;
        cout << "Ou deixe em branco, caso queira considerar o diretorio do executavel como path." << endl;
        cout << R"(Certifique-se de no path estar o arquivo "entrada.txt" e a pasta "pythonquestions".)" << endl;
        cout << R"(Eh necessario que o arquivo "Questions.csv" esteja no diretorio "pythonquestions".)" << endl;
        cout << "Formato a inserir na linha de comando para execucao do algoritmo:" << endl;
        cout << "<./executavel> <pathDoDiretorioInicial>" << endl;
        FileUtils::endProgram();
        return 0;
    }

    // Se o quandtidade de argumentos é 1, nao foi informado o caminho, entao passa uma string vazia
    // Do contrário, passa o caminho passado por parametro
    vars.entryPath(argc == 1 ? "" : argv[1]);

    /*
	 * Limpa os arquivos de saida, para nao conter lixos de outra execução
	 * Caso queira salvar os resultados da saída, eh necessário copiar os arquivos
	 */
    //FileUtils::clearFileContent("saidaInsercao.txt");
    //FileUtils::clearFileContent("saidaBusca.txt");
    //FileUtils::clearFileContent("saidaRemocao.txt");
    //FileUtils::clearFileContent("saida.txt");

    /*
     * Leitura dos arquivos de questões e de respostas.
     * O arquivo de Tags nao eh usado nessa parte do trabalho
     */
    if (vars.questionVector.empty())
        FileUtils::readFileQuestion(vars.questionPath, vars.questionVector);

    if(vars.Ns.empty())
    {
        vars.Ns = FileUtils::readInputFile("entrada.txt");
        vars.N = vars.Ns.size();
    }

    openMenu(vars);

    return 0;
}

/**
 * Menu de opções inicial
 * @param vars: estrutura com todas as variáveis necessárias para a execução do programa
 */
void openMenu(Variables &vars) {
    cout << "------------------------------------------------------------------------" << endl;
    cout << "||         TRABALHO DE ESTRUTURA DE DADOS 2 - MENU DE OPCOES          ||" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "||                 INSIRA O CODIGO DA OPCAO ESCOLHIDA                 ||" << endl;
    cout << "||       Opcao 0: Sair e encerrar a execucao                          ||" << endl;
    cout << "||       Opcao 1: Codificacao e Decodificacao por Huffman             ||" << endl;
    cout << "||       Opcao 2: Codificacao e Decodificacao por LZ77                ||" << endl;
    cout << "||       Opcao 3: Codificacao e Decodificacao por LZ78                ||" << endl;
    cout << "||       Opcao 4: Codificacao e Decodificacao por LZW                 ||" << endl;
    cout << "||       Opcao 5: Testes                                              ||" << endl;
    cout << "||--------------------------------------------------------------------||" << endl;
    cout << "||       Opcao: ";
    cin >> vars.entry;
    cout << "||--------------------------------------------------------------------||" << endl;
    switch (vars.entry) {
        case 0:
            FileUtils::endProgram();
        case 1:
            codeDecodeHuffman(vars);
            break;
        case 2:
            codeDecodeLZ77(vars);
            break;
        case 3:
            codeDecodeLZ78(vars);
            break;
        case 4:
            codeDecodeLZW(vars);
            break;
        case 5:
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
    while (executarNovamente != 'N' && executarNovamente != 'S' && 
		   executarNovamente != 'n' && executarNovamente != 's') 
	{
        cout << "Entrada invalida! Tente novamente: ";
        cin >> executarNovamente;
    }
    executarNovamente == 'S' || executarNovamente == 's' ? openMenu(vars) : FileUtils::endProgram();
}

void codeDecodeHuffman(Variables &vars)
{
	cout << "Codificacao por Huffman" << endl;
	for (auto &itNs : vars.Ns)
	{
		Huffman h;
		cout << "Codificacao de " << itNs << " questoes." << endl;
		vector<Question> tempVecQuestion = getVetQuestionsRand(vars.questionVector, itNs);
		string str1 = getBodyNQuestions(tempVecQuestion);
		tempVecQuestion.clear();
		FileUtils::writeToOutputFile("Huffman_NaoCodificado_N_" + to_string(itNs) + ".txt", str1, false);

		string str2 = h.encode(str1);
		str1.clear();
		FileUtils::writeToOutputFile("Huffman_Codificado_N_" + to_string(itNs) + ".txt", str2, false);

		str1 = h.decode(str2);
		str2.clear();
		FileUtils::writeToOutputFile("Huffman_Decodificado_N_" + to_string(itNs) + ".txt", str1, false);
		str1.clear();
	}
}

void codeDecodeLZ77(Variables &vars)
{
    unsigned int bufferWindow, dictionaryWindow;
    //vector<Triple> triplas;
    //vector<Question> tempVecQuestion;
    //string tempStr;

    cout << "Codificacao por LZ77" << endl;
    cout << "Infome o tamanho do dicionario: ";
    cin >> dictionaryWindow;
    cout << "Informe o tamanho do buffer: ";
    cin >> bufferWindow;
    LZ77 lz77(dictionaryWindow, bufferWindow);
    for (auto &itNs : vars.Ns)
    {
        cout << "Codificacao de " << itNs << " questoes." << endl;
		vector<Question> tempVecQuestion = getVetQuestionsRand(vars.questionVector, itNs);
		string tempStr = getBodyNQuestions(tempVecQuestion);
		tempVecQuestion.clear();
        FileUtils::writeToOutputFile("LZ77_NaoCodificado_N_" + to_string(itNs) + ".txt", tempStr, false);
        vector<Triple> triplas = lz77.compress(tempStr);
        lz77.saveFile(triplas, "LZ77_Codificado_N_" + to_string(itNs) + ".txt");
        FileUtils::writeToOutputFile("LZ77_Decodificado_N_" + to_string(itNs) + ".txt", lz77.decompressText(triplas), false);
		triplas.clear();
    }
}

void codeDecodeLZ78(Variables &vars)
{
	cout << "Codificacao por LZ78" << endl;
	LZ78 lz;
	for (auto &itNs : vars.Ns)
	{
		cout << "Codificacao de " << itNs << " questoes." << endl;
		vector<Question> tempVecQuestion = getVetQuestionsRand(vars.questionVector, itNs);
		string str1 = getBodyNQuestions(tempVecQuestion);
		tempVecQuestion.clear();
		FileUtils::writeToOutputFile("LZ78_NaoCodificado_N_" + to_string(itNs) + ".txt", str1, false);

		string str2 = lz.compress(str1);
		str1.clear();
		FileUtils::writeToOutputFile("LZ78_Codificado_N_" + to_string(itNs) + ".txt", str2, false);

		str1 = lz.decompress(str2);
		str2.clear();
		FileUtils::writeToOutputFile("LZ78_Decodificado_N_" + to_string(itNs) + ".txt", str1, false);
		str1.clear();
	}
}

void codeDecodeLZW(Variables &vars)
{
	cout << "Codificacao por LZW" << endl;
	for (auto &itNs : vars.Ns)
	{
		LZW lz;
		cout << "Codificacao de " << itNs << " questoes." << endl;
		vector<Question> tempVecQuestion = getVetQuestionsRand(vars.questionVector, itNs);
		string str1 = getBodyNQuestions(tempVecQuestion);
		tempVecQuestion.clear();
		FileUtils::writeToOutputFile("LZW_NaoCodificado_N_" + to_string(itNs) + ".txt", str1, false);

		string str2 = lz.compressText(str1);
		str1.clear();
		FileUtils::writeToOutputFile("LZW_Codificado_N_" + to_string(itNs) + ".txt", str2, false);
	}
}

void tests()
{
    //String original para ser usada nos testes
    string str = "bananabofanaoanabafanabananananana";

    ///Testes Huffman
    Huffman huffman;
    string comprimidoHuffman = huffman.encode(str);
    string descomprimidoHuffman = huffman.decode(comprimidoHuffman);

    cout << "Testes Huffman:" << endl;
    cout << "Original: " << str << endl;
    cout << "Comprimido: " << comprimidoHuffman << endl;
    cout << "Descomprimido: " << descomprimidoHuffman<< endl;

    ///Testes LZ77
    LZ77 lz77(6, 10);
    vector<Triple> saidaLz77 = lz77.compress(str);
    string comprimido = lz77.saveFile(saidaLz77, "testeCompressaoLZ77.txt");
    string descomprimeTriple = lz77.decompressText(saidaLz77);
    string descomprimeString = lz77.decompressText(comprimido);

    cout << "Testes LZ77:" << endl;
    cout << "Original: " << str << endl;
    cout << "Comprimido: " << comprimido<< endl;
    cout << "Descomprimido por Triple: " << descomprimeTriple << endl;
    cout << "Descomprimido por String: " << descomprimeString << endl;


    ///Testes LZ78
    LZ78 lz78;


    ///Testes LZW
    LZW lzw;
    comprimido = lzw.compressText(str);
    cout << "Testes LZW:" << endl;
    cout << "Original: " << str << endl;
    cout << "Comprimido: " << comprimido << endl;

}

string getBodyNQuestions(vector<Question> &questionList)
{
    string out;
    for (auto &itVecQuestion  : questionList)
    {
        out += itVecQuestion.getBody();
    }
    return out;
}

string getBodyNQuestions(vector<Question> &questionList, int qtd)
{
	string out;
	for (int i = 0; i < qtd; i++)
	{
		out += questionList[i].getBody();
	}
	return out;
}

vector<Question> getVetQuestionsRand(vector<Question> &vetQuestions, const int &n) {
    /**
     * ifdef utilizando #define para RANDOM_SEED feito no inicio do arquivo da main.cpp
     * para escolher o metodo de geracao de seed que melhor se enquadr para Windows ou Linux
     */
    long seed = RANDOM_SEED;
    std::mt19937 eng(seed); // seed the generator
    uniform_int_distribution<unsigned long> distAleatoria(0, vetQuestions.size() - 1);///distribuicao uniforme aleatoria

    vector<int> questionsIds; ///Usado para nao ter registro com id repetido
    questionsIds.reserve((vetQuestions.size()));
    for (auto &it : vetQuestions)
        questionsIds.push_back(it.getQuestionId());

    vector<Question> vetQuestionsAleatorio; /// Vector de questions gerados aleatoriamente
    vetQuestionsAleatorio.reserve(n);

    for (int i = 0; i < n; i++) {
        unsigned int indice;
        do {
            indice = distAleatoria(eng);
        } while (questionsIds[indice] == -1);
        vetQuestionsAleatorio.push_back(vetQuestions[indice]);
        questionsIds[indice] = -1;
    }
    return vetQuestionsAleatorio;
}