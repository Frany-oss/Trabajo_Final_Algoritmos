#pragma once

#include <string>

using namespace std;
using namespace System;

class Archivo
{
private:
	string	nombre		;
	string	extension	;
	int	tama�o		;
	int		fecha		;
public:

	Archivo(string nom, string ext, int tam, int fec)
	{
		nombre = nom;
		extension = ext;
		tama�o = tam;
		fecha = fec;
	}


	string	getnombre	 	() {return nombre		;}
	string	getextension  	() {return extension	;}
	int	gettama�o		() {return tama�o		;}
	int		getfecha		() {return fecha		;}

	void setnombre		(string	nombre		) { this->nombre		= nombre	;}	
	void setextension	(string	extension	) { this->extension	= extension	;}
	void settama�o		(int	tama�o		) { this->tama�o		= tama�o	;}
	void setfecha		(int	fecha		) { this->fecha		= fecha		;}

};