#include <queue>
#include "../Headers/HuffmanTree.h"
#include "../Headers/HuffmanNode.h"

using namespace std;

HuffmanTree::HuffmanTree(char key)
{
	root = new HuffmanNode();
	HuffmanNode* node = new HuffmanNode(key, "1");
	root->setRight(node);
	ScapeNodeFather = root;

	this->dictionary = set<CharPathPair>();
	dictionary.emplace(key, "1");
}

void HuffmanTree::insert(char key)
{
	HuffmanNode* insertedNode;
	set<CharPathPair>::iterator it = dictionary.find(key);

	if (it != dictionary.end()) // Chave existe na árvore
	{
		CharPathPair pair = (*it);
		insertedNode = search(pair.getPath());
		restructureTree(insertedNode);
	}
	else
	{
		HuffmanNode* newFather = new HuffmanNode();
		newFather->setPath(ScapeNodeFather->getPath() + '0');
		string nodePath = newFather->getPath() + '1';
		newFather->setRight(new HuffmanNode(key, nodePath));
		newFather->setFather(ScapeNodeFather);
		ScapeNodeFather->setLeft(newFather);
		ScapeNodeFather = newFather;

		HuffmanNode* p = ScapeNodeFather->getFather();
		while (p != nullptr)
		{
			p->incrementFrequency();
			p = p->getFather();
		}
		dictionary.emplace(key, nodePath);
	}
}

HuffmanNode* HuffmanTree::search(string path)
{
	HuffmanNode* p = root;
	for (int i = 0; i < (int)path.size(); i++)
	{
		if (path[i] == '1')
			p = p->getRight();
		else
			p = p->getLeft();
	}
	return p;
}

void HuffmanTree::restructureTree(HuffmanNode* insertedNode)
{
	vector<HuffmanNode*> queue = fillQueue();
	HuffmanNode* p = insertedNode;

	vector<HuffmanNode*>::iterator it;
	while ((*it)->getKey() != insertedNode->getKey())
		it++;

	HuffmanNode* nextNode = *(it++); // next node in the queue
	while (nextNode->getFrequency() == insertedNode->getFrequency())
		nextNode = *(it++);

	HuffmanNode* aux = nextNode;
	nextNode = insertedNode;
	insertedNode = aux;
	insertedNode->incrementFrequency();
	restructureTree(insertedNode->getFather()); // Necessário testar se isso funciona
}

vector<HuffmanNode*> HuffmanTree::fillQueue()
{
	queue<HuffmanNode*> cq; // control queue
	vector<HuffmanNode*> rq; // result queue
	HuffmanNode* p = root;

	cq.push(p);
	while (!cq.empty())
	{
		if (p->getKey() != '\0')
			rq.push_back(p);

		cq.pop();

		if (p->getRight() != nullptr)
		{
			//p->setPath(p->getPath() + '1');
			cq.push(p->getRight());
		}
		if (p->getLeft() != nullptr)
		{
			//p->setPath(p->getPath() + '0');
			cq.push(p->getLeft());
		}

		p = cq.front();
	}

	return rq;
}