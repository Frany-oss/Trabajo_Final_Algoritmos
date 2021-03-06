#ifndef BST_H
#define BST_H

#include <functional>

template<typename T, typename Comparable = T, T NONE = 0>
class AVLTree {
	struct Node {
		T     elem;
		int   h;
		int   n;
		Node* left;
		Node* right;

		Node(T elem)
			: elem(elem), left(nullptr), right(nullptr), h(0), n(1) {}
	};

	Node* root;
	Node * root2;
	vector <T> V;

	std::function<Comparable(T)>  key;

	void destroy(Node* node) {
		if (node != nullptr) {
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}
	Node* add(Node* node, T elem) {
		if (node == nullptr) {
			node = new Node(elem);
		}
		else {
			if (key(elem) > key(node->elem)) {
				node->right = add(node->right, elem);
			}
			else {
				node->left = add(node->left, elem);
			}
			node = balance(node);
		}
		return node;
	}
	void inorder(Node* node, std::function<void(T)> proc) {
		if (node != nullptr) {
			inorder(node->left, proc);
			proc(node->elem);
			inorder(node->right, proc);
		}
	}

	T find(Node* node, Comparable val) {
		if (node == nullptr) {
			return NONE;
		}
		if (val == key(node->elem)) {
			return node->elem;
		}
		else if (val < key(node->elem)) {
			return find(node->left, val);
		}
		else {
			return find(node->right, val);
		}
	}


	Node * findDad(Node* node, Comparable val) {
		if (node == nullptr) {
			return nullptr;
		}
		if (node == root && val == key(root->elem)) {
			return nullptr;
		}

		if (node->left != nullptr) {
			if (val == key(node->left->elem)) {

				return node;
			}

		}

		if (node->right != nullptr) {
			if (val == key(node->right->elem)) {

				return node;
			}

		}

		if (val < key(node->elem)) {
			return findDad(node->left, val);
		}
		else {
			return findDad(node->right, val);
		}
	}

	Node* findNode(Node* node, Comparable val) {
		if (node == nullptr) {
			return nullptr;
		}
		if (val == key(node->elem)) {
			return node;
		}
		else if (val < key(node->elem)) {
			return findNode(node->left, val);
		}
		else {
			return findNode(node->right, val);
		}
	}

	Node* finMenProx(Node* node, Comparable val) {
		Node * n = findDad(key(node->elem));


		if (node == nullptr) {
			return nullptr;
		}
		if (val > key(node->elem) && (node->right == nullptr)) {

			return node;
		}
		if (val > key(node->elem) && val < key(node->right->elem) && val < key(node->right->left->elem))
		{

			return node;
		}



		if (val < key(node->elem)) {
			return finMenProx(node->left, val);
		}
		else {
			return finMenProx(node->right, val);
		}
	}

	Node* finMayProx(Node* node, Comparable val) {
		Node * n = findDad(key(node->elem));

		if (node == nullptr) {
			return nullptr;
		}
		if (val < key(node->elem) && (node->left == nullptr)) {
			return node;
		}

		if (val < key(node->elem) && key(node->left->elem) < val  && key(node->left->right->elem) < val  )
		{
			return node;
		}



		if (val < key(node->elem)) {
			return finMayProx(node->left, val);
		}
		else {
			return finMayProx(node->right, val);
		}
	}


	/* BALANCEO */
	int height(Node* node) {
		return node == nullptr ? -1 : node->h;
	}
	int length(Node* node) {
		return node == nullptr ? 0 : node->n;
	}
	void updateHeight(Node* node) {
		int hl = height(node->left);
		int hr = height(node->right);
		node->h = 1 + (hl > hr ? hl : hr);
	}
	Node* rotRight(Node* node) {
		Node* aux = node->left;
		node->left = aux->right;
		aux->right = node;
		updateHeight(aux->right);
		updateHeight(aux);
		return aux;
	}
	Node* rotLeft(Node* node) {
		Node* aux = node->right;
		node->right = aux->left;
		aux->left = node;
		updateHeight(aux->left);
		updateHeight(aux);
		return aux;
	}
	Node* balance(Node* node) {
		int hl = height(node->left);
		int hr = height(node->right);
		if (hl - hr < -1) {
			if (height(node->right->left) > height(node->right->right)) {
				node->right = rotRight(node->right);
			}
			node = rotLeft(node);
		}
		else if (hl - hr > 1) {
			if (height(node->left->right) > height(node->left->left)) {
				node->left = rotLeft(node->left);
			}
			node = rotRight(node);
		}
		else {
			updateHeight(node);
		}
		return node;
	}



	vector <T> filtradomayor(Comparable n){
		root2 = findNode(n);
		if (root2 == nullptr){
			root2 = finMayProx(n);
			V.push_back(root2->elem);
		}
		Node * root3 = root2;
		Node * papi = findDad(key(root2->elem));//right
		Node * hijo = root2;
		while (root2->right != nullptr){
			root2 = root2->right;
			root3 = root2;
			V.push_back(root2->elem);
			while (root3->left != nullptr){
				root3 = root3->left;
				V.push_back(root3->elem);
			}
		}
		if (papi != nullptr){
			if (key(papi->elem) > key(hijo->elem)){
				V.push_back(papi->elem);
				filtradomayor(key(papi->elem));
			}
			else if (key(hijo->elem) < key(root->elem)){
				V.push_back(root->elem);
				filtradomayor(key(root->elem));
			}
		}
		return V;
	}

	vector <T> filtradomenor(Comparable n)
	{

		root2 = findNode(n);

		if (root2 == nullptr)
		{
			root2 = finMenProx(n);
			V.push_back(root2->elem);
		}



		Node * root3 = root2;
		Node * papi = findDad(key(root2->elem));//left
		Node * hijo = root2;


		while (root2->left != nullptr)
		{
			root2 = root2->left;
			root3 = root2;
			V.push_back(root2->elem);

			while (root3->right != nullptr)
			{
				root3 = root3->right;
				V.push_back(root3->elem);
			}
		}

		if (papi != nullptr)
		{
			if (key(papi->elem) < key(hijo->elem))
			{
				V.push_back(papi->elem);
				filtradomenor(key(papi->elem));
			}
			else if (key(hijo->elem) > key(root->elem))
			{
				V.push_back(root->elem);
				filtradomenor(key(root->elem));
			}

		}

		return V;
	}




	vector <T> filtradoequal(Comparable n)
	{

		root2 = findNode(n);

		if (root2 == nullptr)
		{
			cout << "Elemento no existe";

		}


		Node * root3 = root2;
		Node * root4;

		if (root2 != nullptr)
		{
			if (key(root2->elem) == n)
			{
				V.push_back(root2->elem);
			}
		}


		while (root2->right != nullptr)
		{

			root2 = root2->right;
			root3 = root2;

			if (key(root2->elem) == n)
			{
				V.push_back(root2->elem);
			}

			while (root3->left != nullptr)
			{
				root3 = root3->left;
				root4 = root3;

				if (key(root3->elem) == n)
				{
					V.push_back(root3->elem);
				}

				while (root4->right != nullptr)
				{
					root4 = root3->right;

					if (key(root4->elem) == n)
					{
						V.push_back(root4->elem);
					}

				}
			}

		}

		while (root2->left != nullptr)
		{

			root2 = root2->left;
			root3 = root2;

			if (key(root2->elem) == n)
			{
				V.push_back(root2->elem);
			}

			while (root3->right != nullptr)
			{
				root3 = root3->right;
				root4 = root3;

				if (key(root3->elem) == n)
				{
					V.push_back(root3->elem);
				}

				while (root4->left != nullptr)
				{
					root4 = root3->left;

					if (key(root4->elem) == n)
					{
						V.push_back(root4->elem);
					}

				}
			}
		}

		return V;
	}

	vector <T> filtradoempiezacon(string n, vector<Archivo*> vec) {
		//vector<T> nuevo;
		int len_n = n.length();
		int tamano = vec.size();

		cout << n.length() << endl;
		cout << vec.size() << endl;

		string A;
		string B;

		for (int i = 0; i < tamano; i++) {

			A.clear();
			B.clear();

			for (int j = 0; j < len_n; j++) {
				if (vec.at(i)->getnombre().length() >= len_n) {
					char aux = vec.at(i)->getnombre().at(j);
					char aux2 = n.at(j);
					A.push_back(aux);
					B.push_back(aux2);
				}
				else { A.push_back('Z'); }
			}
			if (A == B) V.push_back(vec[i]);
		}
		return V;
	}

	vector <T> filtradoterminacon(string n, vector<Archivo*> vec) {

		cout << n.length() << endl;
		cout << vec.size() << endl;

		reverse(n.begin(), n.end());

		int len_n = n.length();
		int tamano = vec.size();


		cout << n.length() << endl;
		cout << vec.size() << endl;

		string A;
		string B;

		for (int i = 0; i < tamano; i++) {

			A.clear();
			B.clear();

			for (int j = 0; j < len_n; j++) {
				if (vec.at(i)->getnombre().length() >= len_n) {
					int longitud = vec.at(i)->getnombre().length() - 1;
					char aux = vec.at(i)->getnombre().at(longitud - j);
					char aux2 = n.at(j);
					A.push_back(aux);
					B.push_back(aux2);
				}
				else { A.push_back('Z'); }
			}
			if (A == B) V.push_back(vec[i]);
		}
		return V;
	}

	vector <T> filtradocontiene(string n, vector<Archivo*> vec) {

		int len_n = n.length();
		int tamano = vec.size();

		string A;

		for (int i = 0; i < tamano; i++) {

			A.clear();

			for (int j = 0; j < vec.at(i)->getnombre().length() - 1; j++) {
				if (vec.at(i)->getnombre().length() >= len_n) {
					A = vec.at(i)->getnombre().substr(j, len_n);
					if (A == n) {
						V.push_back(vec[i]);
						j = vec.at(i)->getnombre().length() - 1;
					}
				}
			}
		}
		return V;
	}

public:
	AVLTree(std::function<Comparable(T)>  key = [](T a) {return a; })
		: key(key), root(nullptr) {}
	~AVLTree() {
		destroy(root);
	}
	int height() {
		return height(root);
	}
	int length() {
		return length(root);
	}
	void add(T elem) {
		root = add(root, elem);
	}
	bool remove(Comparable val) {
		Node* aux = root;
		Node* parent;
		bool left;
		while (aux != nullptr) {
			if (val == key(aux->elem)) {
				break;
			}
			else {
				parent = aux;
				if (val < key(aux->elem)) {
					left = true;
					aux = aux->left;
				}
				else {
					left = false;
					aux = aux->right;
				}
			}
		}
		if (aux == nullptr) return false;
		if (aux->left == nullptr) {
			if (aux == root)  root = aux->right;
			else if (left)    parent->left = aux->right;
			else              parent->right = aux->right;
			delete aux;
		}
		else {
			Node* aux2 = aux->left;
			while (aux2->right != nullptr) {
				parent = aux2;
				aux2 = aux2->right;
			}
			if (aux2 == aux->left) {
				aux->left = aux2->left;
			}
			else {
				parent->right = aux2->left;
			}
			aux->elem = aux2->elem;
			delete aux2;
		}
		return true;
	}

	T find(Comparable val) {
		return find(root, val);
	}

	Node * findNode(Comparable val) {
		return findNode(root, val);
	}

	Node * findDad(Comparable val) {
		return findDad(root, val);
	}

	Node* finMayProx(Comparable val) {
		return finMayProx(root, val);
	}

	Node* finMenProx(Comparable val) {
		return finMenProx(root, val);
	}
	//list<T> findAll(Comparable val) {
	//	return nullptr; // TODO!!
	//}*/

	void inorder(std::function<void(T)> proc) {
		inorder(root, proc);
	}

	vector <T> inorderV() {
		vector <T> V;
		std::function<void(T)> proc = [&](T a) { V.push_back(a); };
		inorder(root, proc);
		return V;
	}

	vector <T> antiinorderV() {
		vector <T> V;
		std::function<void(T)> proc = [&](T a) { V.push_back(a); };
		inorder(root, proc);

		for (int i = 0; i < V.size() / 2; i++)
		{
			T aux = V[i];
			V[i] = V[V.size() - 1 - i];
			V[V.size() - 1 - i] = aux;
		}

		return V;
	}

	vector <T> FiltradoMayor(Comparable n)
	{
		V.clear();
		V = filtradomayor(n);
		return V;
	}

	vector <T> FiltradoMenor(Comparable n)
	{
		V.clear();
		V = filtradomenor(n);
		return V;
	}

	vector <T> FiltradoEqual(Comparable n)
	{
		V.clear();
		V = filtradoequal(n);
		return V;
	}

	vector <T> FiltradoEmpiezaCon(string n, vector<Archivo*> aux) {
		V.clear();
		V = filtradoempiezacon(n, aux);
		return V;
	}

	vector <T> FiltradoTerminaCon(string n, vector<Archivo*> aux) {
		V.clear();
		V = filtradoterminacon(n, aux);
		return V;
	}

	vector <T> FiltradoContiene(string n, vector<Archivo*> aux) {
		V.clear();
		V = filtradocontiene(n, aux);
		return V;
	}

};

#endif
