//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Racional.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 05/04/2012
// Description : Lista de exercícios 3
//=======================================================================

#include "Racional.h"
#include <iostream>
using namespace std;

Racional::Racional() {
}

Racional::Racional(int numerador,int denominador){
	int divisor = mdc(numerador, denominador);
	this->numerador = numerador/divisor;
	this->denominador = denominador/divisor;
}
Racional::Racional(int inteiro){
	this->numerador = inteiro;
	this->denominador = 1;
}
Racional::Racional(Racional& racional){
	this->numerador = racional.numerador;
	this->denominador = racional.denominador;
}

Racional Racional::Add(Racional n){
	return n;
}
Racional Racional::Sub(Racional n){
	return n;
}
Racional Racional::Mult(Racional n){
	this->numerador *= n.numerador;
	this->denominador *= n.denominador;
	Racional res(this->numerador,this->denominador);
	return res;
}
Racional Racional::Div(Racional n){
	return n;
}
bool Racional::Less(Racional n){
	return false;
}
void Racional::Imprime(){
	cout << "racional= " << this->numerador <<"/" <<this->denominador << endl;
}
void Racional::ImprimePtoFlutuante(){

}


int mdc(int x, int y){
        int dividendo, divisor, resto;

        dividendo = (x>y?x:y);
        divisor = (x>y?y:x);

        while(dividendo % divisor != 0){
                resto = dividendo % divisor;
                dividendo = divisor;
                divisor = resto;
        }
        return divisor;
}

Racional::~Racional() {
}

